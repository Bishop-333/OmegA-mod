.PHONY: release qvm clean clean_assets clean_gamecode clean_output distclean

COMPILE_PLATFORM=$(shell uname | sed -e 's/_.*//' | tr '[:upper:]' '[:lower:]' | sed -e 's/\//_/g')
COMPILE_ARCH=$(shell uname -m | sed -e 's/i.86/x86/' | sed -e 's/^arm.*/arm/')

#arm64 hack!
ifeq ($(shell uname -m), arm64)
  COMPILE_ARCH=arm64
endif
ifeq ($(shell uname -m), aarch64)
  COMPILE_ARCH=arm64
endif

ifeq ($(COMPILE_PLATFORM),sunos)
  # Solaris uname and GNU uname differ
  COMPILE_ARCH=$(shell uname -p | sed -e 's/i.86/x86/')
endif

GAMECODE_DIR := omega_gamecode
GAMECODE_QVM_DIR := $(GAMECODE_DIR)/build/release-$(COMPILE_PLATFORM)-$(COMPILE_ARCH)/omega/vm
ASSETS_DIR := omega_assets

OUTPUT_DIR := build
PK3_DIR := $(OUTPUT_DIR)/pk3

OMEGA_PK3 = z_omega-v3.3.7.pk3

TIMESTAMP = @$(shell cd $(GAMECODE_DIR) && git show -s --format=%ct)

release: qvm $(OUTPUT_DIR) 
	find . -name ".DS_Store" -print -delete
	rm -rf $(PK3_DIR)
	mkdir $(PK3_DIR)
	cp -r $(ASSETS_DIR)/assets/* $(PK3_DIR)/
	cp README.md $(PK3_DIR)/
	rm -rf $(PK3_DIR)/vm
	mkdir $(PK3_DIR)/vm
	cp $(GAMECODE_QVM_DIR)/*.qvm $(PK3_DIR)/vm/
	#cd $(PK3_DIR) && zip -r ../$(OMEGA_PK3) -- .
	cd $(PK3_DIR) && $(CURDIR)/caca_deterministic_zip.sh \
		$(TIMESTAMP) ../$(OMEGA_PK3) .

qvm:
	$(MAKE) -C $(GAMECODE_DIR) \
		BUILD_GAME_SO=0 BUILD_GAME_QVM=1

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean_assets:
	$(MAKE) -C $(ASSETS_DIR) clean

clean_gamecode:
	$(MAKE) -C $(GAMECODE_DIR) clean

clean_output:
	rm -rf $(OUTPUT_DIR)

clean: clean_assets clean_gamecode clean_output

distclean: clean_assets clean_output
	$(MAKE) -C $(GAMECODE_DIR) distclean
