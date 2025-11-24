#
# omega Makefile
#
# GNU Make required
#

COMPILE_PLATFORM=$(shell uname | sed -e 's/_.*//' | tr '[:upper:]' '[:lower:]' | sed -e 's/\//_/g')
COMPILE_ARCH=$(shell uname -m | sed -e 's/i.86/x86/' | sed -e 's/^arm.*/arm/')

ifeq ($(COMPILE_PLATFORM),mingw32)
  ifeq ($(COMPILE_ARCH),i386)
    COMPILE_ARCH=x86
  endif
endif

ifndef BUILD_GAME_SO
BUILD_GAME_SO = 0
endif
ifndef BUILD_GAME_QVM
BUILD_GAME_QVM = 1
endif

#############################################################################
#
# If you require a different configuration from the defaults below, create a
# new file named "Makefile.local" in the same directory as this file and define
# your parameters there. This allows you to change configuration without
# causing problems with keeping up to date with the repository.
#
#############################################################################
-include Makefile.local

ifndef MOD
MOD=omega
endif

ifeq ($(COMPILE_PLATFORM),cygwin)
  PLATFORM=mingw32
endif

ifndef PLATFORM
PLATFORM=$(COMPILE_PLATFORM)
endif
export PLATFORM

ifeq ($(PLATFORM),mingw32)
  MINGW=1
endif
ifeq ($(PLATFORM),mingw64)
  MINGW=1
endif

ifeq ($(COMPILE_ARCH),i86pc)
  COMPILE_ARCH=x86
endif

ifeq ($(COMPILE_ARCH),amd64)
  COMPILE_ARCH=x86_64
endif
ifeq ($(COMPILE_ARCH),x64)
  COMPILE_ARCH=x86_64
endif

ifndef ARCH
ARCH=$(COMPILE_ARCH)
endif
export ARCH

ifneq ($(PLATFORM),$(COMPILE_PLATFORM))
  CROSS_COMPILING=1
else
  CROSS_COMPILING=0

  ifneq ($(ARCH),$(COMPILE_ARCH))
    CROSS_COMPILING=1
  endif
endif
export CROSS_COMPILING

ifndef BUILD_DIR
BUILD_DIR=build
endif

ifndef TEMPDIR
TEMPDIR=/tmp
endif

ifndef MOUNT_DIR
MOUNT_DIR=code
endif

ifndef DEBUG_CFLAGS
DEBUG_CFLAGS=-g -O0
endif

#############################################################################

BD=$(BUILD_DIR)/debug-$(PLATFORM)-$(ARCH)
BR=$(BUILD_DIR)/release-$(PLATFORM)-$(ARCH)

QADIR=$(MOUNT_DIR)/game
CGDIR=$(MOUNT_DIR)/cgame
Q3UIDIR=$(MOUNT_DIR)/q3_ui
UIDIR=$(MOUNT_DIR)/ui
CMDIR=$(MOUNT_DIR)/qcommon
Q3ASMDIR=$(MOUNT_DIR)/tools/asm
LBURGDIR=$(MOUNT_DIR)/tools/lcc/lburg
Q3CPPDIR=$(MOUNT_DIR)/tools/lcc/cpp
Q3LCCETCDIR=$(MOUNT_DIR)/tools/lcc/etc
Q3LCCSRCDIR=$(MOUNT_DIR)/tools/lcc/src

bin_path=$(shell which $(1) 2> /dev/null)

#############################################################################
# SETUP AND BUILD -- LINUX
#############################################################################

## Defaults
LIB=lib

INSTALL=install
MKDIR=mkdir

ifeq ($(PLATFORM),linux)

  ifeq ($(ARCH),x86_64)
    LIB=lib64
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -pipe

  OPTIMIZE = -O2 -fvisibility=hidden -fomit-frame-pointer -ffast-math

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC -fvisibility=hidden
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  LIBS= -lm

  ifeq ($(ARCH),x86)
    BASE_CFLAGS += -m32
  endif

endif #Linux

ifdef MINGW

  ifeq ($(CROSS_COMPILING),1)
    # If CC is already set to something generic, we probably want to use
    # something more specific
    ifneq ($(findstring $(strip $(CC)),cc gcc),)
      CC=
    endif

    # We need to figure out the correct gcc and windres
    ifeq ($(ARCH),x86_64)
      MINGW_PREFIXES=x86_64-w64-mingw32 amd64-mingw32msvc
      STRIP=x86_64-w64-mingw32-strip
    endif
    ifeq ($(ARCH),x86)
      MINGW_PREFIXES=i686-w64-mingw32 i586-mingw32msvc i686-pc-mingw32
    endif

    ifndef CC
      CC=$(firstword $(strip $(foreach MINGW_PREFIX, $(MINGW_PREFIXES), \
         $(call bin_path, $(MINGW_PREFIX)-gcc))))
    endif

    ifndef WINDRES
      WINDRES=$(firstword $(strip $(foreach MINGW_PREFIX, $(MINGW_PREFIXES), \
         $(call bin_path, $(MINGW_PREFIX)-windres))))
    endif
  else
    # Some MinGW installations define CC to cc, but don't actually provide cc,
    # so check that CC points to a real binary and use gcc if it doesn't
    ifeq ($(call bin_path, $(CC)),)
      CC=gcc
    endif

  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -pipe

  OPTIMIZE = -O2 -fvisibility=hidden -fomit-frame-pointer -ffast-math

  SHLIBEXT=dll
  SHLIBCFLAGS=-fPIC -fvisibility=hidden
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  LIBS= -lm

  ifeq ($(ARCH),x86)
    BASE_CFLAGS += -m32
  endif

endif


#############################################################################
# SETUP AND BUILD -- LINUX
#############################################################################

ifeq ($(PLATFORM),darwin)

  BASE_CFLAGS = -Wall -Wimplicit -Wstrict-prototypes

  OPTIMIZE = -ffast-math

  SHLIBEXT=dylib
  SHLIBCFLAGS=-fPIC -fno-common
  SHLIBLDFLAGS=-dynamiclib $(LDFLAGS)

  NOTSHLIBCFLAGS=-mdynamic-no-pic

endif #darwin


TARGETS =

ifndef FULLBINEXT
  FULLBINEXT=.$(ARCH)$(BINEXT)
endif

ifndef SHLIBNAME
  SHLIBNAME=$(ARCH).$(SHLIBEXT)
endif

ifneq ($(BUILD_GAME_SO),0)
  TARGETS += \
    $(B)/$(MOD)/cgame$(SHLIBNAME) \
    $(B)/$(MOD)/qagame$(SHLIBNAME) \
    $(B)/$(MOD)/ui$(SHLIBNAME)
endif

ifneq ($(BUILD_GAME_QVM),0)
TARGETS += \
    $(B)/$(MOD)/vm/cgame.qvm \
    $(B)/$(MOD)/vm/qagame.qvm \
    $(B)/$(MOD)/vm/ui.qvm
endif

ifeq ("$(CC)", $(findstring "$(CC)", "clang" "clang++"))
  BASE_CFLAGS += -Qunused-arguments
endif

ifdef DEFAULT_BASEDIR
  BASE_CFLAGS += -DDEFAULT_BASEDIR=\\\"$(DEFAULT_BASEDIR)\\\"
endif

ifeq ($(NO_STRIP),1)
  STRIP_FLAG =
else
  STRIP_FLAG = -s
endif

BASE_CFLAGS += -Wformat=2 -Wno-format-zero-length -Wformat-security -Wno-format-nonliteral
BASE_CFLAGS += -Wstrict-aliasing=2 -Wmissing-format-attribute
BASE_CFLAGS += -Wdisabled-optimization
BASE_CFLAGS += -Werror-implicit-function-declaration

ifeq ($(V),1)
echo_cmd=@:
Q=
else
echo_cmd=@echo
Q=@
endif

define DO_CC
$(echo_cmd) "CC $<"
$(Q)$(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_SHLIB_CC
$(echo_cmd) "SHLIB_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_GAME_CC
$(echo_cmd) "GAME_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) -DQAGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_CGAME_CC
$(echo_cmd) "CGAME_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) -DCGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_UI_CC
$(echo_cmd) "UI_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) -DUI $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

#############################################################################
# MAIN TARGETS
#############################################################################

default: release
all: debug release

debug:
	@$(MAKE) targets B=$(BD) CFLAGS="$(CFLAGS) $(BASE_CFLAGS)" \
	  OPTIMIZE="$(DEBUG_CFLAGS)" V=$(V)

release:
	@$(MAKE) targets B=$(BR) CFLAGS="$(CFLAGS) $(BASE_CFLAGS)" \
	  OPTIMIZE="-DNDEBUG $(OPTIMIZE)" V=$(V)

# Create the build directories, check libraries and print out
# an informational message, then start building
targets: makedirs
	@echo ""
	@echo "Building $(CLIENTBIN) in $(B):"
	@echo "  PLATFORM: $(PLATFORM)"
	@echo "  ARCH: $(ARCH)"
	@echo "  COMPILE_PLATFORM: $(COMPILE_PLATFORM)"
	@echo "  COMPILE_ARCH: $(COMPILE_ARCH)"
	@echo "  CC: $(CC)"
	@echo ""
	@echo "  CFLAGS:"
	-@for i in $(CFLAGS); \
	do \
		echo "    $$i"; \
	done
	-@for i in $(OPTIMIZE); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  LDFLAGS:"
	-@for i in $(LDFLAGS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  LIBS:"
	-@for i in $(LIBS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  Output:"
	-@for i in $(TARGETS); \
	do \
		echo "    $$i"; \
	done
	@echo ""

ifneq ($(TARGETS),)
	@$(MAKE) $(TARGETS) V=$(V)
endif

makedirs:
	@if [ ! -d $(BUILD_DIR) ];then $(MKDIR) $(BUILD_DIR);fi
	@if [ ! -d $(B) ];then $(MKDIR) $(B);fi
	@if [ ! -d $(B)/$(MOD) ];then $(MKDIR) $(B)/$(MOD);fi
	@if [ ! -d $(B)/$(MOD)/cgame ];then $(MKDIR) $(B)/$(MOD)/cgame;fi
	@if [ ! -d $(B)/$(MOD)/game ];then $(MKDIR) $(B)/$(MOD)/game;fi
	@if [ ! -d $(B)/$(MOD)/ui ];then $(MKDIR) $(B)/$(MOD)/ui;fi
	@if [ ! -d $(B)/$(MOD)/qcommon ];then $(MKDIR) $(B)/$(MOD)/qcommon;fi
	@if [ ! -d $(B)/$(MOD)/vm ];then $(MKDIR) $(B)/$(MOD)/vm;fi
	@if [ ! -d $(B)/tools ];then $(MKDIR) $(B)/tools;fi
	@if [ ! -d $(B)/tools/asm ];then $(MKDIR) $(B)/tools/asm;fi
	@if [ ! -d $(B)/tools/etc ];then $(MKDIR) $(B)/tools/etc;fi
	@if [ ! -d $(B)/tools/rcc ];then $(MKDIR) $(B)/tools/rcc;fi
	@if [ ! -d $(B)/tools/cpp ];then $(MKDIR) $(B)/tools/cpp;fi
	@if [ ! -d $(B)/tools/lburg ];then $(MKDIR) $(B)/tools/lburg;fi

#############################################################################
# QVM BUILD TOOLS
#############################################################################

TOOLS_OPTIMIZE = -g -O2 -Wall -fno-strict-aliasing
TOOLS_CFLAGS = $(TOOLS_OPTIMIZE) \
               -DTEMPDIR=\"$(TEMPDIR)\" -DSYSTEM=\"\" \
               -I$(Q3LCCSRCDIR) \
               -I$(LBURGDIR)
TOOLS_LIBS =
TOOLS_LDFLAGS =

ifeq ($(GENERATE_DEPENDENCIES),1)
	TOOLS_CFLAGS += -MMD
endif

define DO_TOOLS_CC
$(echo_cmd) "TOOLS_CC $<"
$(Q)$(CC) $(TOOLS_CFLAGS) -o $@ -c $<
endef

define DO_TOOLS_CC_DAGCHECK
$(echo_cmd) "TOOLS_CC_DAGCHECK $<"
$(Q)$(CC) $(TOOLS_CFLAGS) -Wno-unused -o $@ -c $<
endef

LBURG       = $(B)/tools/lburg/lburg$(BINEXT)
DAGCHECK_C  = $(B)/tools/rcc/dagcheck.c
Q3RCC       = $(B)/tools/q3rcc$(BINEXT)
Q3CPP       = $(B)/tools/q3cpp$(BINEXT)
Q3LCC       = $(B)/tools/q3lcc$(BINEXT)
Q3ASM       = $(B)/tools/q3asm$(BINEXT)

LBURGOBJ= \
	$(B)/tools/lburg/lburg.o \
	$(B)/tools/lburg/gram.o

$(B)/tools/lburg/%.o: $(LBURGDIR)/%.c
	$(DO_TOOLS_CC)

$(LBURG): $(LBURGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3RCCOBJ = \
  $(B)/tools/rcc/alloc.o \
  $(B)/tools/rcc/bind.o \
  $(B)/tools/rcc/bytecode.o \
  $(B)/tools/rcc/dag.o \
  $(B)/tools/rcc/dagcheck.o \
  $(B)/tools/rcc/decl.o \
  $(B)/tools/rcc/enode.o \
  $(B)/tools/rcc/error.o \
  $(B)/tools/rcc/event.o \
  $(B)/tools/rcc/expr.o \
  $(B)/tools/rcc/gen.o \
  $(B)/tools/rcc/init.o \
  $(B)/tools/rcc/inits.o \
  $(B)/tools/rcc/input.o \
  $(B)/tools/rcc/lex.o \
  $(B)/tools/rcc/list.o \
  $(B)/tools/rcc/main.o \
  $(B)/tools/rcc/null.o \
  $(B)/tools/rcc/output.o \
  $(B)/tools/rcc/prof.o \
  $(B)/tools/rcc/profio.o \
  $(B)/tools/rcc/simp.o \
  $(B)/tools/rcc/stmt.o \
  $(B)/tools/rcc/string.o \
  $(B)/tools/rcc/sym.o \
  $(B)/tools/rcc/symbolic.o \
  $(B)/tools/rcc/trace.o \
  $(B)/tools/rcc/tree.o \
  $(B)/tools/rcc/types.o

$(DAGCHECK_C): $(LBURG) $(Q3LCCSRCDIR)/dagcheck.md
	$(echo_cmd) "LBURG $(Q3LCCSRCDIR)/dagcheck.md"
	$(Q)$(LBURG) $(Q3LCCSRCDIR)/dagcheck.md $@

$(B)/tools/rcc/dagcheck.o: $(DAGCHECK_C)
	$(DO_TOOLS_CC_DAGCHECK)

$(B)/tools/rcc/%.o: $(Q3LCCSRCDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3RCC): $(Q3RCCOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3CPPOBJ = \
	$(B)/tools/cpp/cpp.o \
	$(B)/tools/cpp/lex.o \
	$(B)/tools/cpp/nlist.o \
	$(B)/tools/cpp/tokens.o \
	$(B)/tools/cpp/macro.o \
	$(B)/tools/cpp/eval.o \
	$(B)/tools/cpp/include.o \
	$(B)/tools/cpp/hideset.o \
	$(B)/tools/cpp/getopt.o \
	$(B)/tools/cpp/unix.o

$(B)/tools/cpp/%.o: $(Q3CPPDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3CPP): $(Q3CPPOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

Q3LCCOBJ = \
	$(B)/tools/etc/lcc.o \
	$(B)/tools/etc/bytecode.o

$(B)/tools/etc/%.o: $(Q3LCCETCDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3LCC): $(Q3LCCOBJ) $(Q3RCC) $(Q3CPP)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $(Q3LCCOBJ) $(TOOLS_LIBS)

define DO_Q3LCC
$(echo_cmd) "Q3LCC $<"
$(Q)$(Q3LCC) -o $@ $<
endef

define DO_CGAME_Q3LCC
$(echo_cmd) "CGAME_Q3LCC $<"
$(Q)$(Q3LCC) -DCGAME -o $@ $<
endef

define DO_GAME_Q3LCC
$(echo_cmd) "GAME_Q3LCC $<"
$(Q)$(Q3LCC) -DQAGAME -o $@ $<
endef

define DO_UI_Q3LCC
$(echo_cmd) "UI_Q3LCC $<"
$(Q)$(Q3LCC) -DUI -o $@ $<
endef

Q3ASMOBJ = \
  $(B)/tools/asm/q3asm.o \
  $(B)/tools/asm/cmdlib.o

$(B)/tools/asm/%.o: $(Q3ASMDIR)/%.c
	$(DO_TOOLS_CC)

$(Q3ASM): $(Q3ASMOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(TOOLS_CFLAGS) $(TOOLS_LDFLAGS) -o $@ $^ $(TOOLS_LIBS)

#############################################################################
## OMEGA CGAME
#############################################################################

CGOBJ_ = \
  $(B)/$(MOD)/cgame/cg_main.o \
  $(B)/$(MOD)/cgame/bg_lib.o \
  $(B)/$(MOD)/cgame/bg_misc.o \
  $(B)/$(MOD)/cgame/bg_pmove.o \
  $(B)/$(MOD)/cgame/bg_slidemove.o \
  $(B)/$(MOD)/cgame/cg_challenges.o \
  $(B)/$(MOD)/cgame/cg_consolecmds.o \
  $(B)/$(MOD)/cgame/cg_draw.o \
  $(B)/$(MOD)/cgame/cg_drawtools.o \
  $(B)/$(MOD)/cgame/cg_effects.o \
  $(B)/$(MOD)/cgame/cg_ents.o \
  $(B)/$(MOD)/cgame/cg_event.o \
  $(B)/$(MOD)/cgame/cg_info.o \
  $(B)/$(MOD)/cgame/cg_localents.o \
  $(B)/$(MOD)/cgame/cg_marks.o \
  $(B)/$(MOD)/cgame/cg_players.o \
  $(B)/$(MOD)/cgame/cg_playerstate.o \
  $(B)/$(MOD)/cgame/cg_predict.o \
  $(B)/$(MOD)/cgame/cg_scoreboard.o \
  $(B)/$(MOD)/cgame/cg_servercmds.o \
  $(B)/$(MOD)/cgame/cg_snapshot.o \
  $(B)/$(MOD)/cgame/cg_unlagged.o \
  $(B)/$(MOD)/cgame/cg_view.o \
  $(B)/$(MOD)/cgame/cg_weapons.o \
  \
  $(B)/$(MOD)/qcommon/q_math.o \
  $(B)/$(MOD)/qcommon/q_shared.o

CGOBJ = $(CGOBJ_) $(B)/$(MOD)/cgame/cg_syscalls.o
CGVMOBJ = $(CGOBJ_:%.o=%.asm)

$(B)/$(MOD)/cgame$(SHLIBNAME): $(CGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(CGOBJ)

$(B)/$(MOD)/vm/cgame.qvm: $(CGVMOBJ) $(CGDIR)/cg_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(CGVMOBJ) $(CGDIR)/cg_syscalls.asm

#############################################################################
## OMEGA GAME
#############################################################################

QAOBJ_ = \
  $(B)/$(MOD)/game/g_main.o \
  $(B)/$(MOD)/game/ai_chat.o \
  $(B)/$(MOD)/game/ai_cmd.o \
  $(B)/$(MOD)/game/ai_dmnet.o \
  $(B)/$(MOD)/game/ai_dmq3.o \
  $(B)/$(MOD)/game/ai_main.o \
  $(B)/$(MOD)/game/ai_team.o \
  $(B)/$(MOD)/game/bg_alloc.o \
  $(B)/$(MOD)/game/bg_lib.o \
  $(B)/$(MOD)/game/bg_misc.o \
  $(B)/$(MOD)/game/bg_pmove.o \
  $(B)/$(MOD)/game/bg_slidemove.o \
  $(B)/$(MOD)/game/g_active.o \
  $(B)/$(MOD)/game/g_admin.o \
  $(B)/$(MOD)/game/g_arenas.o \
  $(B)/$(MOD)/game/g_bot.o \
  $(B)/$(MOD)/game/g_client.o \
  $(B)/$(MOD)/game/g_cmds.o \
  $(B)/$(MOD)/game/g_cmds_ext.o \
  $(B)/$(MOD)/game/g_combat.o \
  $(B)/$(MOD)/game/g_fileops.o \
  $(B)/$(MOD)/game/g_killspree.o \
  $(B)/$(MOD)/game/g_items.o \
  $(B)/$(MOD)/game/g_misc.o \
  $(B)/$(MOD)/game/g_missile.o \
  $(B)/$(MOD)/game/g_mover.o \
  $(B)/$(MOD)/game/g_playerstore.o \
  $(B)/$(MOD)/game/g_session.o \
  $(B)/$(MOD)/game/g_spawn.o \
  $(B)/$(MOD)/game/g_svcmds.o \
  $(B)/$(MOD)/game/g_svcmds_ext.o \
  $(B)/$(MOD)/game/g_target.o \
  $(B)/$(MOD)/game/g_team.o \
  $(B)/$(MOD)/game/g_trigger.o \
  $(B)/$(MOD)/game/g_utils.o \
  $(B)/$(MOD)/game/g_vote.o \
  $(B)/$(MOD)/game/g_unlagged.o \
  $(B)/$(MOD)/game/g_weapon.o \
  \
  $(B)/$(MOD)/qcommon/q_math.o \
  $(B)/$(MOD)/qcommon/q_shared.o

QAOBJ = $(QAOBJ_) $(B)/$(MOD)/game/g_syscalls.o
QAVMOBJ = $(QAOBJ_:%.o=%.asm)

$(B)/$(MOD)/qagame$(SHLIBNAME): $(QAOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(QAOBJ)

$(B)/$(MOD)/vm/qagame.qvm: $(QAVMOBJ) $(QADIR)/g_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(QAVMOBJ) $(QADIR)/g_syscalls.asm

#############################################################################
## OMEGA UI
#############################################################################

UIOBJ_ = \
  $(B)/$(MOD)/ui/ui_main.o \
  $(B)/$(MOD)/ui/bg_misc.o \
  $(B)/$(MOD)/ui/bg_lib.o \
  $(B)/$(MOD)/ui/ui_addbots.o \
  $(B)/$(MOD)/ui/ui_atoms.o \
  $(B)/$(MOD)/ui/ui_cdkey.o \
  $(B)/$(MOD)/ui/ui_challenges.o \
  $(B)/$(MOD)/ui/ui_cinematics.o \
  $(B)/$(MOD)/ui/ui_confirm.o \
  $(B)/$(MOD)/ui/ui_connect.o \
  $(B)/$(MOD)/ui/ui_controls2.o \
  $(B)/$(MOD)/ui/ui_demo2.o \
  $(B)/$(MOD)/ui/ui_display.o \
  $(B)/$(MOD)/ui/ui_dmflags.o \
  $(B)/$(MOD)/ui/ui_firstconnect.o \
  $(B)/$(MOD)/ui/ui_gameinfo.o \
  $(B)/$(MOD)/ui/ui_ingame.o \
  $(B)/$(MOD)/ui/ui_loadconfig.o \
  $(B)/$(MOD)/ui/ui_menu.o \
  $(B)/$(MOD)/ui/ui_mfield.o \
  $(B)/$(MOD)/ui/ui_mods.o \
  $(B)/$(MOD)/ui/ui_network.o \
  $(B)/$(MOD)/ui/ui_password.o \
  $(B)/$(MOD)/ui/ui_playermodel.o \
  $(B)/$(MOD)/ui/ui_players.o \
  $(B)/$(MOD)/ui/ui_playersettings.o \
  $(B)/$(MOD)/ui/ui_preferences.o \
  $(B)/$(MOD)/ui/ui_qmenu.o \
  $(B)/$(MOD)/ui/ui_removebots.o \
  $(B)/$(MOD)/ui/ui_saveconfig.o \
  $(B)/$(MOD)/ui/ui_serverinfo.o \
  $(B)/$(MOD)/ui/ui_servers2.o \
  $(B)/$(MOD)/ui/ui_setup.o \
  $(B)/$(MOD)/ui/ui_sound.o \
  $(B)/$(MOD)/ui/ui_sparena.o \
  $(B)/$(MOD)/ui/ui_specifyserver.o \
  $(B)/$(MOD)/ui/ui_splevel.o \
  $(B)/$(MOD)/ui/ui_sppostgame.o \
  $(B)/$(MOD)/ui/ui_spskill.o \
  $(B)/$(MOD)/ui/ui_startserver.o \
  $(B)/$(MOD)/ui/ui_team.o \
  $(B)/$(MOD)/ui/ui_teamorders.o \
  $(B)/$(MOD)/ui/ui_video.o \
  $(B)/$(MOD)/ui/ui_votemenu.o \
  $(B)/$(MOD)/ui/ui_votemenu_fraglimit.o \
  $(B)/$(MOD)/ui/ui_votemenu_timelimit.o \
  $(B)/$(MOD)/ui/ui_votemenu_gametype.o \
  $(B)/$(MOD)/ui/ui_votemenu_kick.o \
  $(B)/$(MOD)/ui/ui_votemenu_map.o \
  $(B)/$(MOD)/ui/ui_votemenu_custom.o \
  \
  $(B)/$(MOD)/qcommon/q_math.o \
  $(B)/$(MOD)/qcommon/q_shared.o

UIOBJ = $(UIOBJ_) $(B)/$(MOD)/ui/ui_syscalls.o
UIVMOBJ = $(UIOBJ_:%.o=%.asm)

$(B)/$(MOD)/ui$(SHLIBNAME): $(UIOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(UIOBJ)

$(B)/$(MOD)/vm/ui.qvm: $(UIVMOBJ) $(UIDIR)/ui_syscalls.asm $(Q3ASM)
	$(echo_cmd) "Q3ASM $@"
	$(Q)$(Q3ASM) -o $@ $(UIVMOBJ) $(UIDIR)/ui_syscalls.asm

#############################################################################
## GAME MODULE RULES
#############################################################################

$(B)/$(MOD)/cgame/bg_%.o: $(QADIR)/bg_%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/cgame/q_%.o: $(QADIR)/q_%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/cgame/%.o: $(CGDIR)/%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/cgame/bg_%.asm: $(QADIR)/bg_%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)

$(B)/$(MOD)/cgame/%.asm: $(CGDIR)/%.c $(Q3LCC)
	$(DO_CGAME_Q3LCC)

$(B)/$(MOD)/game/%.o: $(QADIR)/%.c
	$(DO_GAME_CC)

$(B)/$(MOD)/game/%.asm: $(QADIR)/%.c $(Q3LCC)
	$(DO_GAME_Q3LCC)

$(B)/$(MOD)/ui/bg_%.o: $(QADIR)/bg_%.c
	$(DO_UI_CC)

$(B)/$(MOD)/ui/%.o: $(Q3UIDIR)/%.c
	$(DO_UI_CC)

$(B)/$(MOD)/ui/ui_syscalls.o: $(UIDIR)/ui_syscalls.c
	$(DO_UI_CC)

$(B)/$(MOD)/ui/bg_%.asm: $(QADIR)/bg_%.c $(Q3LCC)
	$(DO_UI_Q3LCC)

$(B)/$(MOD)/ui/%.asm: $(Q3UIDIR)/%.c $(Q3LCC)
	$(DO_UI_Q3LCC)

$(B)/$(MOD)/qcommon/%.o: $(CMDIR)/%.c
	$(DO_SHLIB_CC)

$(B)/$(MOD)/qcommon/%.asm: $(CMDIR)/%.c $(Q3LCC)
	$(DO_Q3LCC)

#############################################################################
# MISC
#############################################################################

OBJ = $(QAOBJ) $(CGOBJ) $(UIOBJ) \
  $(QAVMOBJ) $(CGVMOBJ) $(UIVMOBJ)
TOOLSOBJ = $(LBURGOBJ) $(Q3CPPOBJ) $(Q3RCCOBJ) $(Q3LCCOBJ) $(Q3ASMOBJ)

clean: clean-debug clean-release

clean-debug:
	@$(MAKE) clean2 B=$(BD)

clean-release:
	@$(MAKE) clean2 B=$(BR)

clean2:
	@echo "CLEAN $(B)"
	@rm -f $(OBJ)
	@rm -f $(OBJ_D_FILES)
	@rm -f $(TARGETS)

toolsclean: toolsclean-debug toolsclean-release

toolsclean-debug:
	@$(MAKE) toolsclean2 B=$(BD)

toolsclean-release:
	@$(MAKE) toolsclean2 B=$(BR)

toolsclean2:
	@echo "TOOLS_CLEAN $(B)"
	@rm -f $(TOOLSOBJ)
	@rm -f $(TOOLSOBJ_D_FILES)
	@rm -f $(LBURG) $(DAGCHECK_C) $(Q3RCC) $(Q3CPP) $(Q3LCC) $(Q3ASM)

distclean: clean
	@rm -rf $(BUILD_DIR)

#############################################################################
# DEPENDENCIES
#############################################################################

OBJ_D_FILES=$(filter %.d,$(OBJ:%.o=%.d))
TOOLSOBJ_D_FILES=$(filter %.d,$(TOOLSOBJ:%.o=%.d))
-include $(OBJ_D_FILES) $(TOOLSOBJ_D_FILES)

.PHONY: all clean clean2 clean-debug clean-release \
	debug default distclean makedirs \
	release targets \
	toolsclean toolsclean2 toolsclean-debug toolsclean-release \
	$(OBJ_D_FILES) $(TOOLSOBJ_D_FILES)
