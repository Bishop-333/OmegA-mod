import os
import re
import sys

# --- CONFIGURATION ---
# Liste des dossiers spécifiques à analyser (chemins relatifs à la racine)
SCAN_DIRS = ["code/game", "code/cgame", "code/q3_ui"]
EXTENSIONS = {".c", ".h"}

# Liste des FICHIERS à ignorer (ne jamais signaler d'erreurs dedans)
FILE_WHITELIST = {
    "inv.h", 
    "match.h", 
    "syn.h", 
    "g_syscalls.c", 
    "chars.h.c", 
    "cg_syscalls.c"
}

# Liste des MOTS à ignorer (fonctions système, types de base...)
SYMBOL_WHITELIST = {
    "vmMain", "DllMain", "main", "Foundation", "software", "code",
    "Sys_GetGameAPI", "Sys_GetCGameAPI", "Sys_GetUIAPI", "Sys_GetBotLibAPI",
    "int", "float", "void", "char", "double", "struct", "union", "enum", "typedef",
    "if", "while", "for", "return", "switch", "case", "default", "break", "continue", 
    "static", "const", "extern", "volatile", "register", "unsigned", "signed",
    "qboolean", "qtrue", "qfalse", "NULL", "vec3_t", "vec_t", "cvar_t"
}

# --- REGEX ---
REGEX_DEFINE = re.compile(r'^\s*#define\s+([a-zA-Z_][a-zA-Z0-9_]*)', re.MULTILINE)
REGEX_FUNC = re.compile(r'^([a-zA-Z_][a-zA-Z0-9_\s\*]+)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^;]*\)\s*\{', re.MULTILINE)
REGEX_VAR_PROTO = re.compile(r'^\s*(?:static\s+|const\s+|extern\s+)?(?:[a-zA-Z0-9_]+\s+(?:\*\s*)*)+([a-zA-Z_][a-zA-Z0-9_]*)\s*(?:\[[^;]*\])?(?:=.*?)?;', re.MULTILINE)

def get_files(target_dirs):
    files = []
    for directory in target_dirs:
        # Vérification d'existence du dossier
        if not os.path.exists(directory):
            print(f"ATTENTION : Le dossier '{directory}' n'existe pas (vérifiez que vous êtes à la racine).")
            continue
            
        for root, _, filenames in os.walk(directory):
            for f in filenames:
                if os.path.splitext(f)[1] in EXTENSIONS:
                    files.append(os.path.join(root, f))
    return files

def read_file(path):
    try:
        with open(path, 'r', encoding='utf-8', errors='ignore') as f:
            return f.read()
    except Exception as e:
        print(f"Erreur lecture {path}: {e}")
        return ""

def strip_comments(text):
    text = re.sub(r'/\*[\s\S]*?\*/', '', text)
    text = re.sub(r'//.*', '', text)
    return text

def find_candidates(content, filepath):
    candidates = []
    lines = content.splitlines()
    
    def get_line_num(char_index):
        return content[:char_index].count('\n') + 1

    # Defines
    for m in REGEX_DEFINE.finditer(content):
        name = m.group(1)
        if name not in SYMBOL_WHITELIST:
            candidates.append({'name': name, 'type': 'DEFINE', 'file': filepath, 'line': get_line_num(m.start())})

    # Fonctions
    for m in REGEX_FUNC.finditer(content):
        name = m.group(2) 
        if name not in SYMBOL_WHITELIST:
            candidates.append({'name': name, 'type': 'FONCTION', 'file': filepath, 'line': get_line_num(m.start())})

    # Variables & Prototypes
    for m in REGEX_VAR_PROTO.finditer(content):
        name = m.group(1)
        if name not in SYMBOL_WHITELIST:
            candidates.append({'name': name, 'type': 'VAR/PROTO', 'file': filepath, 'line': get_line_num(m.start())})

    return candidates

def main():
    print(f"--- 1. SCAN DES DOSSIERS CIBLES : {', '.join(SCAN_DIRS)} ---")
    files = get_files(SCAN_DIRS)
    print(f"{len(files)} fichiers sources trouvés.")

    if len(files) == 0:
        print("Aucun fichier trouvé. Assurez-vous d'exécuter ce script à la racine du projet (là où se trouve le dossier 'code').")
        return

    full_code_clean = ""
    
    print("--- 2. IDENTIFICATION ET CHARGEMENT ---")
    all_candidates = []
    
    for f in files:
        raw_content = read_file(f)
        # On ajoute le contenu au bloc global pour la recherche d'usage
        full_code_clean += strip_comments(raw_content) + "\n"
        
        # Vérification Whitelist Fichier
        filename = os.path.basename(f)
        if filename in FILE_WHITELIST:
            continue
            
        # Sinon, on liste les définitions
        candidates = find_candidates(raw_content, f)
        all_candidates.extend(candidates)
    
    print(f"{len(all_candidates)} définitions analysables (hors whitelist fichiers).")

    print("--- 3. ANALYSE DES UTILISATIONS ---")
    candidates_by_name = {}
    for c in all_candidates:
        if c['name'] not in candidates_by_name:
            candidates_by_name[c['name']] = []
        candidates_by_name[c['name']].append(c)

    unused_items = []
    count_processed = 0
    total_unique_names = len(candidates_by_name)

    for name, candidate_list in candidates_by_name.items():
        count_processed += 1
        if count_processed % 500 == 0:
            print(f"Analyse... {count_processed}/{total_unique_names}")

        # Recherche du mot entier dans tout le code chargé
        pattern = r'\b' + re.escape(name) + r'\b'
        matches = len(re.findall(pattern, full_code_clean))
        definition_count = len(candidate_list)
        
        # Si le nombre total d'occurrences est égal (ou inférieur) au nombre de définitions/déclarations,
        # cela signifie que le mot n'est jamais "appelé" ou "utilisé" ailleurs.
        if (matches - definition_count) <= 0:
            for c in candidate_list:
                unused_items.append(c)

    print("\n" + "="*60)
    print("RAPPORT : ÉLÉMENTS POTENTIELLEMENT INUTILISÉS")
    print(f"Dossiers scannés : {', '.join(SCAN_DIRS)}")
    print(f"Fichiers ignorés : {', '.join(FILE_WHITELIST)}")
    print("="*60)
    print(f"Format: [TYPE] Fichier:Ligne -> Nom")
    print("-" * 60)

    # Tri par fichier et ligne pour lecture facile
    unused_items.sort(key=lambda x: (x['file'], x['line']))

    current_file = ""
    for item in unused_items:
        filename = os.path.basename(item['file'])
        if filename != current_file:
            print(f"\n--- {filename} ---")
            current_file = filename
        
        print(f"[{item['type']}] Ligne {item['line']:<4} : {item['name']}")

    print("\n" + "="*60)
    print(f"TOTAL: {len(unused_items)} éléments trouvés.")

if __name__ == "__main__":
    main()