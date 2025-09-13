import os
import re
import json
import pathlib
from bs4 import BeautifulSoup

def arabic_to_roman(num: int) -> str:
    numerals = [
        (1000, "m"), (900, "cm"), (500, "d"), (400, "cd"),
        (100, "c"), (90, "xc"), (50, "l"), (40, "xl"),
        (10, "x"), (9, "ix"), (5, "v"), (4, "iv"), (1, "i")
    ]
    result = ""
    for value, symbol in numerals:
        while num >= value:
            result += symbol
            num -= value
    return result

# kolumny nie będące zadaniami
NON_TASK_COLS = {
    "lp.", "nazwa", "miejsce", "miasto", "kl.", "klaza", "lp", "l.p.", "szkoła", "imię", "miejscowość szkoły", "nazwisko", "imię i nazwisko", "klasa", "nazwa szkoły", "wojewodztwo", "miejscowść",
    "miejscowość", "województwo", "suma"
}

# wzorzec skrótu zadania: 3 litery + opcjonalna gwiazdka
TASK_PATTERN = re.compile(r"^[a-ząćęłńóśźż]{3}\*?$", re.IGNORECASE)

# funkcje określające liczbę zadań na dzień
def etap2_zadan(edycja):
    if edycja == 1:
        return [1, 1, 1]
    if edycja == 3:
        return [1, 1, 2]
    if edycja in [5, 6, 7, 8, 13, 20]:
        return [0, 2, 2] # Próbnego nie ma w tabeli.
    return [1, 2, 2]

def etap3_zadan(edycja):
    wyjatki = {
        1: [1, 2, 1],
        2: [1, 2, 2],
        3: [1, 2, 2],
        4: [1, 3, 2], 
        5: [0, 3, 3], # Dla 'Układów assemblerowych' nie ma danych w tabeli.
        6: [0, 2, 3], # Nie ma próbnego w tabeli.
        7: [0, 2, 3], # Dla lollobrygidy nie ma danych w tabeli, trzeba sprawdzić w niebieskiej książeczce.
        8: [0, 2, 3], # Nie ma próbnego w tabeli.
        9: [1, 2, 3],
        10: [1, 2, 3],
        11: [1, 3, 2],
        13: [0, 2, 3], # Nie ma próbnego w tabeli.
        14: [1, 2, 3],
        15: [1, 3, 2],
        16: [1, 3, 2],
        24: [1, 3, 2],
        25: [2, 3, 3],
        27: [0, 0, 0],
        29: [2, 3, 3],
        30: [0, 3, 3], # Nie ma próbnego w tabeli.
    }
    
    return wyjatki.get(edycja, [1, 3, 3])

data = {}
files_count = 0
tables_count = 0

def get_score(edycja, etap, s):
    if s in ["", "-"]:
        return 0
    return int(s)

folder = pathlib.Path("oi_pages")
for filename in folder.glob("*.html"):
    m = re.match(r"(\d+)oi_(\d)etap\.html", filename.name)
    if not m:
        continue

    edycja = int(m.group(1))
    etap = int(m.group(2))
    edycja_roman = arabic_to_roman(edycja)

    if edycja <= 4:
        continue

    with open(filename, encoding="utf-8") as f:
        soup = BeautifulSoup(f, "html.parser")

    files_count += 1

    for table in soup.select("table.results_table"):
        prev_div = table.find_previous_sibling("div")
        if prev_div and prev_div.get_text(strip=True).lower() in ["finalista"]:
            continue  # ignorujemy finalistów bez wyróżnienia

        tables_count += 1
        header_cells = [th.get_text(strip=True).lower() for th in table.select("tr th")]

        # sprawdzamy poprawność kolumn
        for col in header_cells:
            if col in NON_TASK_COLS:
                continue
            if TASK_PATTERN.match(col):
                continue
            raise ValueError(f"Nieznana kolumna '{col}' w pliku {filename}")

        # wyciągamy tylko kolumny z zadaniami
        task_names = [col for col in header_cells if col not in NON_TASK_COLS]

        # ustalamy dni dla zadań
        if etap == 2:
            counts = etap2_zadan(edycja)
        elif etap == 3:
            counts = etap3_zadan(edycja)
        else:
            counts = None  # dla etapu 1 pozostawiamy wcześniejszą logikę

        # tworzymy listę dni dla wszystkich zadań w kolejności w tabeli
        if counts:
            days = []
            for day_index, count in enumerate(counts):
                days.extend([day_index] * count)
            if len(days) != len(task_names):
                raise ValueError(f"Liczba zadań w tabeli nie zgadza się z funkcją etap{etap}_zadan dla edycji {edycja}")
        else:
            days = [0 if t.endswith("*") else 1 for t in task_names]

        rows = table.select("tr")[1:]  # pomijamy nagłówek
        for task, dzien in zip(task_names, days):
            nazwa = task.replace("*", "").lower()

            wyniki = []
            for row in rows:
                cells = row.find_all("td")
                if not cells:
                    continue

                if all(cell.get_text(strip=True) == "" for cell in cells):
                    print(f"Pominięto pusty wiersz w pliku {filename}")
                    continue

                if len(cells) != len(header_cells):
                    print(row)
                    print(cells)
                    print(header_cells)
                    raise ValueError(f"Niezgodna liczba komórek w wierszu (plik {filename})")

                row_dict = {header_cells[i]: cells[i].get_text(strip=True) for i in range(len(cells))}
                wyniki.append(get_score(edycja, etap, row_dict.get(task, "")))

            key = f"{edycja_roman}_etap{etap}_{nazwa}"
            if key not in data:
                data[key] = {
                    "edycja": edycja,
                    "etap": etap,
                    "dzien": dzien,
                    "nazwa": nazwa,
                    "wyniki": []
                }
            data[key]["wyniki"].extend(wyniki)

def hardcode(edycja, etap, dzien, nazwa, p100, p75, p50, p1, p0, nope=0, P100=100, P75=87, P50=62, P1=25):
    key = f"{arabic_to_roman(edycja)}_etap{etap}_{nazwa}"
    # Mało wiadomo o wynikach, to założę że jak jest przedział punktowy [a, b],to srednio uczestnik dostal (a+b)/2 punktow.
    t = [[P100] * p100, [P75] * p75, [P50] * p50, [P1] * p1, [0] * (p0+nope)]
    data[key] = {
        "edycja": edycja,
        "etap": etap,
        "dzien": dzien,
        "nazwa": nazwa,
        "wyniki": sum(t, [])
    }

# Dla I Etapu X OI dane są tylko w niebieskiej książeczce, hardcodujemy.
hardcode(10, 1, 0, "cia", 151, 49, 68, 269, 312)
hardcode(10, 1, 0, "cze", 587, 26, 82, 78, 76)
hardcode(10, 1, 0, "lic", 109, 35, 25, 114, 566)
hardcode(10, 1, 0, "ply", 67, 2, 13, 326, 441)
hardcode(10, 1, 0, "prz", 138, 105, 124, 160, 322)

# Zadanie próbne z XX OI - dane z książeczki.
hardcode(20, 2, 0, "spa", 4, 3, 7, 145, 157, 56)

# Na II etapie XIII OI były dwa próbne :O
hardcode(13, 2, 0, "szk", 5, 16, 46, 95, 90, 103)
hardcode(13, 2, 0, "mag", 6, 2, 23, 228, 48, 48)
hardcode(13, 3, 0, "tan", 0, 0, 4, 38, 14, 11)
# II Etap VIII OI - brakujące próbne
hardcode(8, 2, 0, "gor", 19, 20, 18, 46, 174)

# IV OI manualnie z książeczki.
# I etap.
hardcode(4, 1, 0, "xor", 52, 37, 243, 487, 91)
hardcode(4, 1, 0, "lic", 16 , 266, 277, 230, 40)
hardcode(4, 1, 0, "tan", 110, 54, 85, 376, 125)
hardcode(4, 1, 0, "sko", 68, 101, 115, 327, 38)

# II etap.
hardcode(4, 2, 1, "add", 20, 20, 22, 13, 40)
hardcode(4, 2, 1, "gen", 0, 3, 5, 47, 60)
hardcode(4, 2, 2, "rek", 1, 1, 3, 48, 62)
hardcode(4, 2, 2, "pal", 24, 8, 15, 63, 5)

# III etap.
hardcode(4, 3, 1, "liz", 7 , 5, 16, 14, 2)
hardcode(4, 3, 1, "tro", 2, 1, 3, 29, 9)
hardcode(4, 3, 1, "kaj", 22, 7, 1, 12, 2)
hardcode(4, 3, 2, "ali", 19, 9, 0, 8, 8)
hardcode(4, 3, 2, "rez", 20, 5, 8, 10, 1)

# III OI manualnie z książeczki.
# I etap.
hardcode(3, 1, 0, "zam", 1, 1, 3, 172, 133)
hardcode(3, 1, 0, "pre", 29, 11, 30, 350, 45)
hardcode(3, 1, 0, "mok", 17, 18, 27, 198, 17)
hardcode(3, 1, 0, "gon", 5, 9, 28, 216, 54)

# II etap.
hardcode(3, 2, 1, "wie", 3, 8, 4, 83, 9)
hardcode(3, 2, 2, "slo", 1, 16, 5, 78, 7)
hardcode(3, 2, 2, "haz", 0, 1, 0, 89, 17)

# III etap.
hardcode(3, 3, 1, "age", 0, 2, 8, 27, 1)
hardcode(3, 3, 1, "kul", 0, 1, 0, 36, 1)
hardcode(3, 3, 2, "nie", 0, 7, 0, 23, 8)
hardcode(3, 3, 2, "wyr", 0, 3, 4, 29, 2)

# II OI manualnie z książeczki.
# I etap.
hardcode(2, 1, 0, "jed", 45, 27, 43, 276, 31)
hardcode(2, 1, 0, "drz", 87, 75, 62, 141, 67)
hardcode(2, 1, 0, "opt", 36, 21, 48, 224, 21)
hardcode(2, 1, 0, "pal", 77, 129, 154, 84, 17)

# II etap.
hardcode(2, 2, 1, "mud", 4, 4, 3, 63, 28)
hardcode(2, 2, 1, "tro", 39, 16, 29, 9, 9)
hardcode(2, 2, 2, "sza", 1, 14, 29, 45, 13)
hardcode(2, 2, 2, "wie", 3, 5, 10, 61, 23)

# III etap.
hardcode(2, 3, 1, "obc", 8, 7, 5, 20, 6)
hardcode(2, 3, 1, "poc", 0, 6, 5, 20, 15)
hardcode(2, 3, 2, "skl", 11, 12, 14, 8, 1)
hardcode(2, 3, 2, "sze", 12, 5, 5, 17, 7)

# Wyniki z I OI nie są ustandaryzowane to nie spisuję.

# Na VII OI były różne ilości punktów per zadanie.
# Dodatkowo nie ma w sprawozdaniu ile za próbne...

# TODO: Przeskalować wyniki żeby każde zadanie było na 100 pkt.

# TODO: Dodać zadania z nieznanymi wynikami.
from urllib.parse import urljoin
import re
from bs4 import BeautifulSoup
# --- wczytanie oi_zadania.html ---
tasks_map = {}
with open("oi_zadania.html", encoding="utf-8") as f:
    soup = BeautifulSoup(f, "html.parser")

for row in soup.select("table tr"):
    cells = row.find_all("td")
    if not cells or len(cells) < 2:
        continue

    # link do zadania
    a_tag = row.find("a", href=True)
    if not a_tag:
        continue
    url = a_tag["href"]
    m = re.search(r"/archive/oi/(\d+)/([a-z]+)", url)
    if not m:
        continue
    edycja = int(m.group(1))
    nazwa = m.group(2).lower()
    full_name = cells[0].get_text(strip=True)
    dzien_str = cells[1].get_text(strip=True).lower()  # zakładamy, że dzień w drugim polu

    tasks_map[(edycja, nazwa)] = {
        "full_name": full_name,
        "task_url": f"https://oi.edu.pl/pl/archive/oi/{edycja}/{nazwa}",
        "dzien_str": dzien_str
    }

# --- podczas przetwarzania tabel wyników ---
for key, zadanie in data.items():
    edycja = zadanie["edycja"]
    etap = zadanie["etap"]
    nazwa = zadanie["nazwa"]

    task_info = tasks_map.get((edycja, nazwa))
    if task_info:
        zadanie["full_name"] = task_info["full_name"]
        zadanie["task_url"] = task_info["task_url"]

        # korekta dnia tylko dla etapów > 1
        if etap > 1:
            dzien_str = task_info["dzien_str"]
            if "próbny" in dzien_str:
                zadanie["dzien"] = 0
            elif "pierwszy" in dzien_str:
                zadanie["dzien"] = 1
            elif "drugi" in dzien_str:
                zadanie["dzien"] = 2

# zapis do JSON-a
json_str = json.dumps(data, ensure_ascii=False, indent=2)
json_str = re.sub(r'\n {6}', '', json_str)
with open("wyniki.json", "w", encoding="utf-8") as f:
    f.write(json_str)

# raport
total_tasks = len(data)
total_results = sum(len(v["wyniki"]) for v in data.values())
print("=== RAPORT ===")
print(f"Przetworzono plików: {files_count}")
print(f"Znaleziono tabel:    {tables_count}")
print(f"Zadań w JSON-ie:     {total_tasks}")
print(f"Łącznie wyników:     {total_results}")
print("================")

