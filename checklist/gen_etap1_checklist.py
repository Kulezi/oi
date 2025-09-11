import json
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
wybrany_etap = 1
zadania_etapu = [v for v in data.values() if v["etap"] == wybrany_etap]

# Grupujemy po edycji
grupy = defaultdict(list)
for zad in zadania_etapu:
    grupy[zad["edycja"]].append(zad)

def zadania_edycja(edycja):
    if edycja == 1:
        return 3
    if edycja <= 9:
        return 4
    if edycja <= 31:
        return 5
    return 6

# Znajdź wszystkie edycje
wszystkie_edycje = range(1, max(v["edycja"] for v in data.values()) + 1)

# Przygotowujemy tabelę markdown
header = ["Edycja"] + [f"Zad. {i}" for i in range(1, 7)]
# Pierwszy wiersz to nagłówek
lines = [" | ".join(header)]
# Drugi wiersz to wyrównanie: pierwszy do lewej, reszta do prawej
alignment = [":---"] + ["---:" for _ in header[1:]]
lines.append(" | ".join(alignment))

for edycja in wszystkie_edycje:
    row = [int_to_roman(edycja)]
    zadania = sorted(grupy.get(edycja, []), key=lambda x: x["dzien"])
    for i in range(6):
        if i < len(zadania):
            zad = zadania[i]
            if zad["punkty"] == 100:
                row.append(f"{zad['nazwa']} ✅")
            else:
                row.append(f"{zad['nazwa']} 🤔")
        elif i < zadania_edycja(edycja):
            row.append(" ")
        else:
            row.append("—")
    lines.append(" | ".join(row))

markdown = "\n".join(lines)

# Zapis do pliku
with open("tabela.md", "w", encoding="utf-8") as f:
    f.write(markdown)

print(markdown)

