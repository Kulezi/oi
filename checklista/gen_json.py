# Należy wywoływać z katalogu checklist.
# Generuje listę wszystkich zrobionych zadań w formacie JSON.
# Jeśli zadanie występuje wielokrotnie, wybierane są maksymalne punkty.

import os
import re
import json

oi = (
    'i ii iii iv v vi vii viii ix x '
    'xi xii xiii xiv xv xvi xvii xviii xix xx '
    'xxi xxii xxiii xxiv xxv xxvi xxvii xxviii xxix xxx '
    'xxxi xxxii '
).split()

def extract_points(filename: str):
    """
    Zasady:
    - dokładnie 3 litery (małe lub duże) + .cpp → 100 pkt
    - 3 litery (małe/duże) + liczba + .cpp → liczba
    - inne → None (plik ignorowany)
    """
    m = re.match(r'^([a-zA-Z]{3})(\d*)\.cpp$', filename)
    if not m:
        return None
    if m.group(2) == "":
        return 100
    return int(m.group(2))


tasks = {}

for oi_dir, edycja in [("../rozwiazania/" + edycja, i+1) for i, edycja in enumerate(oi)]:
    if not os.path.isdir(oi_dir):
        continue

    for etap in os.listdir(oi_dir):
        etap_path = os.path.join(oi_dir, etap)
        if not os.path.isdir(etap_path):
            continue

        # Sprawdzenie czy etap dzieli się na dni
        for dzien in os.listdir(etap_path):
            dzien_path = os.path.join(etap_path, dzien)
            if dzien in ("dzien1", "dzien2", "probne"):
                # etap z dniami
                for task_dir in os.listdir(dzien_path):
                    full_task_dir = os.path.join(dzien_path, task_dir)
                    if not os.path.isdir(full_task_dir):
                        continue

                    # maksujemy punkty w folderze
                    max_points = None
                    for f in os.listdir(full_task_dir):
                        if f.endswith(".cpp") and f.startswith(task_dir):
                            punkty = extract_points(f)
                            if punkty is None:
                                continue
                            if max_points is None or punkty > max_points:
                                max_points = punkty

                    if max_points is not None:
                        key = f"{oi[edycja-1]}_{etap}_{dzien}_{task_dir}"
                        tasks[key] = {
                            "edycja": edycja,
                            "etap": int(re.search(r"\d+", etap).group()),
                            "dzien": 0 if dzien == "probne" else int(re.search(r"\d+", dzien).group()),
                            "nazwa": task_dir,
                            "punkty": max_points,
                        }

            else:
                # etap bez dni (np. etap1)
                task_dir = dzien
                full_task_dir = os.path.join(etap_path, task_dir)
                if not os.path.isdir(full_task_dir):
                    continue

                max_points = None
                for f in os.listdir(full_task_dir):
                    if f.endswith(".cpp") and f.startswith(task_dir):
                        punkty = extract_points(f)
                        if punkty is None:
                            continue
                        if max_points is None or punkty > max_points:
                            max_points = punkty

                if max_points is not None:
                    key = f"{oi[edycja-1]}_{etap}_{task_dir}"
                    tasks[key] = {
                        "edycja": edycja,
                        "etap": int(re.search(r"\d+", etap).group()),
                        "dzien": 0,  # brak dni traktujemy jako 0
                        "nazwa": task_dir,
                        "punkty": max_points,
                    }

# zapis do JSON
with open("tasks.json", "w", encoding="utf-8") as f:
    json.dump(tasks, f, indent=4, ensure_ascii=False)

print("✅ tasks.json wygenerowany poprawnie")

