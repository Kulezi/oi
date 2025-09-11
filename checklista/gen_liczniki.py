import json

# --- wczytywanie danych z tasks.json ---
with open("tasks.json", "r", encoding="utf-8") as f:
    data = json.load(f)

# --- hardcodowane maksima ---
MAX_ETAP = {1: 150, 2: 157, 3: 200}       # dla etapów

def etap1_tasks(edycja):
    if edycja == 1:
        return 3
    if edycja <= 9:
        return 4
    if edycja <= 31:
        return 5
    return 6

def etap2_tasks(edycja):
    if edycja == 1:
        return 3
    if edycja == 3:
        return 4
    return 5

def etap3_tasks(edycja):
    if edycja == 27:
        return 0
    if edycja == 1:
        return 4
    if edycja in [2, 3]:
        return 5
    if edycja in [6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 24]:
        return 6
    if edycja == 25:
        return 8
    return 7

MAX_EDYCJA = {
    i: etap1_tasks(i) + etap2_tasks(i) + etap3_tasks(i)
    for i in range(1, 33)
}


# --- liczniki ---
wbite_etap = {i: 0 for i in range(1, 4)}
wbite_edycja = {i: 0 for i in range(1, 33)}

for entry in data.values():
    etap = entry["etap"]
    edycja = entry["edycja"]
    punkty = entry["punkty"]

    if punkty == 100:
        wbite_etap[etap] += 1
        wbite_edycja[edycja] += 1


# --- generowanie treści markdown ---
lines = ["# Podsumowanie", ""]

def to_roman(num: int) -> str:
    vals = [
        (1000, "M"), (900, "CM"), (500, "D"), (400, "CD"),
        (100, "C"), (90, "XC"), (50, "L"), (40, "XL"),
        (10, "X"), (9, "IX"), (5, "V"), (4, "IV"),
        (1, "I"),
    ]
    res = ""
    for val, sym in vals:
        while num >= val:
            res += sym
            num -= val
    return res


# --- tabela etapów ---
lines.append("## Rozwiązane zadania wg etapów\n")
header = ["Etap I", "Etap II", "Etap III", "Łącznie"]
lines.append(" | ".join(header))
lines.append(" | ".join([":---:"] * len(header)))

row = []
wbitych = sum(wbite_etap.values())
wszystkich = sum(MAX_ETAP.values())
for etap in [1, 2, 3]:
    wbite = wbite_etap.get(etap, 0)
    wszystkie = MAX_ETAP[etap]
    row.append(f"{wbite}/{wszystkie} ({100*(wbite/wszystkie):.0f}%)")
row.append(f"{wbitych}/{wszystkich} ({100*(wbitych/wszystkich):.0f}%)")
lines.append(" | ".join(row))


# --- tabela edycji w układzie kolumnowym ---
lines.append("\n## Rozwiązane zadania wg edycji\n")

group_size = 10
num_groups = (len(MAX_EDYCJA) + group_size - 1) // group_size

# nagłówki
headers = []
align = []
for g in range(num_groups):
    headers += ["Edycja", "Wynik"]
    align += [":---", "---:"]
lines.append(" | ".join(headers))
lines.append(" | ".join(align))

# wiersze
for i in range(group_size):
    row = []
    for g in range(num_groups):
        edycja = g*group_size + (i+1)
        if edycja in MAX_EDYCJA:
            wbite = wbite_edycja.get(edycja, 0)
            wszystkie = MAX_EDYCJA[edycja]
            wynik = f"{wbite}/{wszystkie} ({100*wbite/wszystkie:.0f}%)"
            row += [to_roman(edycja), wynik]
        else:
            row += ["", ""]
    lines.append(" | ".join(row))


print("\n".join(lines))


