#!/usr/bin/env python3
import subprocess
import sys
from pathlib import Path

root = Path(__file__).resolve().parent.parent
readme = root / "README.md"
checklist_dir = root / "checklista"

# wczytaj README.md
content = readme.read_text(encoding="utf-8")

marker = "<!-- AUTO-CHECKLIST -->"
if marker not in content:
    print("❌ Nie znaleziono sekcji automatycznej w README.md", file=sys.stderr)
    sys.exit(1)

# uruchomienie gen_json.py (w katalogu checklist)
subprocess.run(["python3", "gen_json.py"], cwd=checklist_dir, check=True)

tables = []

# uruchomienie gen_liczniki.py
out = subprocess.check_output(
    ["python3", "gen_liczniki.py"],
    cwd=checklist_dir,
    text=True
)
tables.append("\n\n" + out.strip() + "\n")

roman = {1: "I", 2: "II", 3: "III"}

# uruchomienie 3 generatorów (również w katalogu checklist)
for etap in [1, 2, 3]:
    out = subprocess.check_output(
        ["python3", f"gen_etap{etap}_checklist.py"],
        cwd=checklist_dir,
        text=True
    )
    tables.append(f"## Rozwiązane zadania z {roman[etap]} etapu\n\n" + out.strip() + "\n")

# komunikat ostrzegawczy
warning = (
    "> ⚠️ **UWAGA:** Sekcja poniżej jest generowana automatycznie.\n"
    "> Nie modyfikuj README poniżej tego napisu.\n"
    "> ✅ oznacza wykonane zadanie.\n"
    "> 🤔 oznacza zadanie z mniej niż 100 punktów.\n"
)

# podmiana zawartości po markerze
base, _ = content.split(marker, 1)
new_content = base + marker + "\n\n" + warning + "\n\n".join(tables)

# zapisz
readme.write_text(new_content, encoding="utf-8")
print("✅ README.md zostało zaktualizowane")

