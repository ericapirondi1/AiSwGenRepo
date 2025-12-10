import os
import re

def find_function_definition(path, func_name):
    """
    Cerca la definizione di una funzione C nei file .c
    dentro la cartella 'path' e nelle sue sottocartelle.
    """
    results = []
    pattern = re.compile(rf"\b{func_name}\s*\([^)]*\)", re.IGNORECASE)

    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(".c"):
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                        for i, line in enumerate(f, start=1):
                            if pattern.search(line):
                                results.append((file_path, i, line.strip()))
                except Exception as e:
                    print(f"Errore leggendo {file_path}: {e}")
    return results


def build_moduli(path):
    """
    Cerca tutte le cartelle che iniziano con TEST_XXXX e costruisce
    la struttura:

    moduli = [
        {
            "nome_modulo": "<nome_file.c>",
            "nome_funzione": "<XXXX>",
            "percorso": "<path/relativo/del/file/senza_nome>",
            "testFolder": "<path/relativo/cartella_unitTests>"
        },
        ...
    ]
    """
    moduli = []

    for root, dirs, files in os.walk(path):
        for d in dirs:
            if d.startswith("TEST_"):
                func_name = d.replace("TEST_", "")
                folder_path = os.path.join(root, d)

                # radice da cui cercare la funzione
                search_root = os.path.dirname(os.path.dirname(folder_path))

                matches = find_function_definition(search_root, func_name)

                if matches:
                    file_path, line_number, line_content = matches[0]

                    # percorso relativo del file .c rispetto a 'path'
                    file_rel = os.path.relpath(file_path, path)
                    nome_modulo = os.path.basename(file_rel)
                    percorso = os.path.dirname(file_rel).replace(os.sep, "/")
                else:
                    # se non troviamo il file che contiene la funzione
                    file_rel = None
                    nome_modulo = None
                    percorso = None

                # cartella unitTests relativa alla radice
                test_folder_rel = os.path.relpath(os.path.dirname(folder_path), path)
                test_folder_rel = test_folder_rel.replace(os.sep, "/")

                moduli.append({
                    "nome_modulo": nome_modulo,
                    "nome_funzione": func_name,
                    "percorso": percorso,
                    "testFolder": test_folder_rel,
                })

    return moduli


# Esempio d'uso
if __name__ == "__main__":
    base_path = os.path.dirname(os.path.abspath(__file__))  # cartella corrente
    moduli = build_moduli(base_path)

    # se vuoi vedere il contenuto della struttura:
    for m in moduli:
        print(m)
    # oppure, se preferisci proprio qualcosa tipo "moduli = [ ... ]":
    # print("moduli = [")
    # for m in moduli:
    #     print(f"    {m},")
    # print("]")
