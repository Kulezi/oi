import json
import sys
from collections import defaultdict

# Funkcja konwertująca liczbę na rzymską
def int_to_roman(num):
    val = [
        1000, 900, 500, 400, 100, 90,
        50, 40, 10, 9, 5, 4, 1
    ]
    syms = [
        "M", "CM", "D", "CD", "C", "XC",
        "L", "XL", "X", "IX", "V", "IV", "I"
    ]
    roman = ""
    i = 0
    while num > 0:
        for _ in range(num // val[i]):
            roman += syms[i]
            num -= val[i]
        i += 1
    return roman

# Wczytaj dane
with open("tasks.json", "r", encoding="utf-8") as f:
    data = json.load(f)

# Wybierz tylko etap 2 (możesz zmienić)
wybrany_etap = 3
zadania_etapu = [v for v in data.values() if v["etap"] == wybrany_etap]

# Grupujemy po edycji
grupy = defaultdict(list)
for zad in zadania_etapu:
    grupy[zad["edycja"]].append(zad)

# Dla edycji zwraca trójkę (zadań próbnych, zadań dnia 1, zadań dnia 2)
def zadania_edycja(edycja):
    wyjatki = {
        1: [1, 2, 1],
        2: [1, 2, 2],
        3: [1, 2, 2],
        4: [1, 3, 2],
        6: [1, 2, 3],
        7: [1, 2, 3],
        8: [1, 2, 3],
        9: [1, 2, 3],
        10: [1, 2, 3],
        11: [1, 3, 2],
        13: [1, 2, 3],
        14: [1, 2, 3],
        15: [1, 3, 2],
        16: [1, 3, 2],
        24: [1, 3, 2],
        25: [2, 3, 3],
        27: [0, 0, 0],
        29: [2, 3, 3],
    }
    
    return wyjatki.get(edycja, [1, 3, 3])
    

# Dla numeru zadania zwraca parę (dzień, numer zadania w dniu)
def ktory_dzien(numer):
    # 0 -> 1, 1 -> 1, 2 -=> 2, 3 -> 1, 4 -> 2
    if numer < 2:
        return 0, numer + 1
    if numer < 6:
        return 1, numer - 3
    return 2, numer - 5 

# Znajdź wszystkie edycje
wszystkie_edycje = range(1, max(v["edycja"] for v in data.values()) + 1)

# Przygotowujemy tabelę markdown
header = ["edycja", "Dzień próbny, zad. 1", "Dzień próbny, zad. 2", "Dzień 1 - zad. 1", "Dzień 1 - zad. 2", "Dzień 1 - zad. 3", "Dzień 2 - zad. 1", "Dzień 2 - zad. 2", "Dzień 2 - zad. 3"] 
# Pierwszy wiersz to nagłówek
lines = [" | ".join(header)]
# Drugi wiersz to wyrównanie: pierwszy do lewej, reszta do prawej
alignment = [":---"] + ["---:" for _ in header[1:]]
lines.append(" | ".join(alignment))
for edycja in wszystkie_edycje:
    row = [int_to_roman(edycja)]
    zadania = sorted(grupy.get(edycja, []), key=lambda x: x["dzien"])
 
    i = 0
    for col in range(8):
        dzien, ktore = ktory_dzien(col)
        if i < len(zadania):
            zad = zadania[i]
            if zad["dzien"] == dzien:
                if zad["punkty"] == 100:
                    row.append(f"{zad['nazwa']} ✅")
                else:
                    row.append(f"{zad['nazwa']} 🤔")
                i += 1
                continue
            elif zad["dzien"] < dzien:
                print(f"Coś chyba za dużo ci się tych zadań dodało do dnia {zad['dzien']} 2 etapu {int_to_roman(edycja)}...", file=sys.stderr)
                exit(1)

        if ktore > zadania_edycja(edycja)[dzien]:
            row.append("—")
        else:
            row.append(" ")
    lines.append(" | ".join(row))

markdown = "\n".join(lines)

# Zapis do pliku
with open("tabela.md", "w", encoding="utf-8") as f:
    f.write(markdown)

print(markdown)

