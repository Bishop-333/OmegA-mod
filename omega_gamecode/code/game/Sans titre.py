import os
import re
import sys

# --- CONFIGURATION ---
SOURCE_DIR = "./"  # Dossier à analyser
EXTENSIONS = {".c", ".h"}

# Liste blanche de sécurité (Mots clés système / Callback moteur)
# Si un mot est ici, il ne sera jamais signalé comme inutilisé.
WHITELIST = {
    "vmMain", "DllMain", "main", "code", "software", "Foundation", 
    "Sys_GetGameAPI", "Sys_GetCGameAPI", "Sys_GetUIAPI", "Sys_GetBotLibAPI",
    "int", "float", "void", "char", "double", "struct", "union", "enum", "typedef",
    "if", "while", "for", "return", "switch", "case", "default", "break", "continue", 
    "static", "const", "extern", "volatile", "register", "unsigned", "signed",
    "qboolean", "qtrue", "qfalse", "NULL", "vec3_t", "vec_t"
}

# --- REGEX (Expressions Régulières) ---
# Ces motifs cherchent les définitions au début d'une ligne (Style Quake 3)

# 1. Defines: #define NOM ...
REGEX_DEFINE = re.compile(r'^\s*#define\s+([a-zA-Z_][a-zA-Z0-9_]*)', re.MULTILINE)

# 2. Fonctions: Type Nom(args) { ...
REGEX_FUNC = re.compile(r'^([a-zA-Z_][a-zA-Z0-9_\s\*]+)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^;]*\)\s*\{', re.MULTILINE)

# 3. Variables / Prototypes: Type Nom; ou Type Nom = ...;
# On cherche un type, un nom, et un point-virgule à la fin.
REGEX_VAR_PROTO = re.compile(r'^\s*(?:static\s+|const\s+|extern\s+)?(?:[a-zA-Z0-9_]+\s+(?:\*\s*)*)+([a-zA-Z_][a-zA-Z0-9_]*)\s*(?:\[[^;]*\])?(?:=.*?)?;', re.MULTILINE)

def get_files(directory):
    files = []
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
    """Enlève les commentaires C/C++ pour éviter de compter les mentions en commentaire comme des usages."""
    # Enlève /* ... */
    text = re.sub(r'/\*[\s\S]*?\*/', '', text)
    # Enlève // ...
    text = re.sub(r'//.*', '', text)
    return text

def find_candidates(content, filepath):
    """Trouve toutes les définitions potentielles dans un fichier."""
    candidates = []
    
    lines = content.splitlines()
    
    # Helper pour trouver le numéro de ligne à partir de l'index de caractère
    def get_line_num(char_index):
        return content[:char_index].count('\n') + 1

    # Defines
    for m in REGEX_DEFINE.finditer(content):
        name = m.group(1)
        if name not in WHITELIST:
            candidates.append({'name': name, 'type': 'DEFINE', 'file': filepath, 'line': get_line_num(m.start())})

    # Fonctions
    for m in REGEX_FUNC.finditer(content):
        name = m.group(2) # Groupe 2 est le nom de la fonction
        if name not in WHITELIST:
            candidates.append({'name': name, 'type': 'FONCTION', 'file': filepath, 'line': get_line_num(m.start())})

    # Variables & Prototypes
    for m in REGEX_VAR_PROTO.finditer(content):
        name = m.group(1) # Groupe 1 est le nom
        if name not in WHITELIST:
            # On note juste "VAR/PROTO", le script ne fait pas la distinction sémantique parfaite
            candidates.append({'name': name, 'type': 'VAR/PROTO', 'file': filepath, 'line': get_line_num(m.start())})

    return candidates

def main():
    print("--- 1. SCAN DES FICHIERS ---")
    files = get_files(SOURCE_DIR)
    print(f"{len(files)} fichiers sources trouvés.")

    # Chargement de tout le code "propre" (sans commentaires) en mémoire
    # C'est lourd, mais nécessaire pour une recherche textuelle globale fiable.
    full_code_clean = ""
    file_contents = {}
    
    for f in files:
        raw_content = read_file(f)
        clean = strip_comments(raw_content)
        file_contents[f] = raw_content # On garde le raw pour la recherche de ligne
        full_code_clean += clean + "\n"

    print("--- 2. IDENTIFICATION DES DÉFINITIONS ---")
    all_candidates = []
    for f in files:
        # On cherche les candidats dans le fichier RAW (pour avoir les bonnes lignes)
        # Mais on vérifiera l'usage dans le code CLEAN
        candidates = find_candidates(read_file(f), f)
        all_candidates.extend(candidates)
    
    print(f"{len(all_candidates)} définitions/déclarations trouvées (Fonctions, Vars, Defines).")

    print("--- 3. ANALYSE DES UTILISATIONS ---")
    # Compter combien de fois chaque nom apparaît dans TOUT le code (sans commentaires)
    # Algorithme :
    # 1. On regroupe les candidats par nom (ex: "InitGame" peut être déclaré dans g_local.h et défini dans g_main.c)
    # 2. On compte les occurrences du mot dans le texte global.
    # 3. Si (Occurrences Totales) <= (Nombre de déclarations/définitions connues), alors c'est probablement inutilisé.
    
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

        # Regex pour mot entier (\b)
        # On échappe le nom pour éviter que des caractères spéciaux ne cassent la regex
        pattern = r'\b' + re.escape(name) + r'\b'
        
        # On compte les correspondances dans TOUT le code
        matches = len(re.findall(pattern, full_code_clean))
        
        # Nombre de fois où le mot est "défini" ou "déclaré"
        definition_count = len(candidate_list)
        
        # Usage réel = Total - Définitions
        usage_count = matches - definition_count
        
        if usage_count <= 0:
            # C'est suspect !
            for c in candidate_list:
                unused_items.append(c)

    print("\n" + "="*60)
    print("RAPPORT : ÉLÉMENTS POTENTIELLEMENT INUTILISÉS")
    print("="*60)
    print(f"Format: [TYPE] Fichier:Ligne -> Nom")
    print("-" * 60)

    # Trier par fichier pour faciliter la lecture
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
    print("Vérifiez manuellement avant de supprimer.")

if __name__ == "__main__":
    main()