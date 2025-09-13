import json
from collections import defaultdict
print("# Zadania uszeregowane po średnim wyniku zawodnika")
print ("Disclaimer: Wyniki są zawyżone - wliczają tylko zawodników, którzy osiągneli **próg** (przejścia do następnego etapu bądź otrzymania tytulu finalisty z wyróżnieniem)")

# wczytanie pliku JSON
with open("wyniki.json", "r", encoding="utf-8") as f:
    data = json.load(f)

# struktura: etap -> lista zadań
etapy = defaultdict(list)
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

for key, zadanie in data.items():
    edycja = zadanie["edycja"]
    etap = zadanie["etap"]
    dzien = zadanie["dzien"]
    wyniki = zadanie["wyniki"]
    full_name = zadanie.get("full_name", zadanie["nazwa"].upper())
    task_url = zadanie.get("task_url", "#")  # jeśli brak linku

    if not wyniki:
        continue

    srednia = sum(wyniki) / len(wyniki)
    procent_setek = wyniki.count(100) / len(wyniki) * 100

    etapy[etap].append({
        "edycja": edycja,
        "dzien": dzien,
        "srednia": srednia,
        "procent_setek": procent_setek,
        "full_name": full_name,
        "task_url": task_url
    })

# funkcja do kolorowania procentu setek
def kolor_procent(p):
    if p >= 50:
        return f"🟢 {p:.1f}%"
    elif p >= 20:
        return f"🟡 {p:.1f}%"
    else:
        return f"🔴 {p:.1f}%"

# generowanie tabel markdown po etapach
for etap in sorted(etapy.keys()):
    print(f"\n## Etap {etap}\n")
    print("| Zadanie | Średni wynik | Procent setek |")
    print("|---------|--------------|---------------|")

    zadania_sorted = sorted(etapy[etap], key=lambda x: x["srednia"], reverse=True)

    for z in zadania_sorted:
        edycja = int_to_roman(z["edycja"])
        dzien = z["dzien"]
        full_name = z["full_name"]
        task_url = z["task_url"]
        srednia = round(z["srednia"], 2)
        procent = kolor_procent(z["procent_setek"])
        if etap in [2, 3]:
            print(f"| {edycja} OI - dzień {dzien} - [{full_name}]({task_url}) | {srednia} | {procent} |")
        else:
            print(f"| {edycja} OI - [{full_name}]({task_url}) | {srednia} | {procent} |")
