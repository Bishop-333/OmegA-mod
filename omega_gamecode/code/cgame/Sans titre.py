import os
import re

# Dossier racine de ton code source
SOURCE_DIR = "./"
# Extensions à analyser
EXTENSIONS = {".c", ".h"}

def get_all_files(directory):
    files_list = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if os.path.splitext(file)[1] in EXTENSIONS:
                files_list.append(os.path.join(root, file))
    return files_list

def get_file_content(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            return f.read()
    except Exception as e:
        print(f"Erreur lecture {filepath}: {e}")
        return ""

def find_functions_in_file(content):
    # Regex simplifiée pour trouver les définitions de fonctions C
    # Cherche: Type Nom(args) {
    # Exclut les commentaires et les macros complexes
    func_pattern = re.compile(r'^\s*[a-zA-Z_][a-zA-Z0-9_*\s]+\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^;]*\)\s*\{', re.MULTILINE)
    return set(func_pattern.findall(content))

def main():
    all_files = get_all_files(SOURCE_DIR)
    print(f"{len(all_files)} fichiers trouvés.")

    # 1. Charger tout le code en mémoire pour la recherche (approximatif mais rapide)
    full_codebase = ""
    file_contents = {}
    
    for f in all_files:
        content = get_file_content(f)
        file_contents[f] = content
        full_codebase += content + "\n"

    # 2. Trouver toutes les définitions de fonctions
    all_defined_funcs = {} # {nom_fonction: fichier_origine}
    
    for f, content in file_contents.items():
        funcs = find_functions_in_file(content)
        for func in funcs:
            if func not in all_defined_funcs:
                all_defined_funcs[func] = f

    print(f"{len(all_defined_funcs)} fonctions définies trouvées.")

    # 3. Vérifier l'utilisation
    # Une fonction est "utilisée" si son nom apparait plus de fois que sa propre définition/déclaration
    unused_functions = []

    for func, filepath in all_defined_funcs.items():
        # Compter les occurrences du nom de la fonction dans tout le code
        # On utilise une regex word boundary \b pour éviter les faux positifs (ex: "Init" dans "InitGame")
        count = len(re.findall(r'\b' + re.escape(func) + r'\b', full_codebase))
        
        # Si le compteur est bas (1 définition + 0 appel = 1, ou 1 def + 1 proto = 2), c'est suspect
        # Pour être sûr, on liste ce qui apparaît moins de 2 fois (juste la définition)
        if count < 2:
            # Filtre les fonctions standard ou callbacks système (vmMain, etc)
            if func not in ["vmMain", "main", "DllMain"]: 
                unused_functions.append((func, filepath, count))

    # 4. Rapport
    print("\n--- Fonctions potentiellement inutilisées ---")
    for func, f, count in unused_functions:
        print(f"[Count: {count}] {func} dans {f}")

if __name__ == "__main__":
    main()