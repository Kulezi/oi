import json

# --- wczytywanie danych ---
with open("tasks.json", "r", encoding="utf-8") as f:
    data = json.load(f)

MAX_ETAP = {1: 150, 2: 157, 3: 200}

def etap1_tasks(edycja):
    if edycja == 1: return 3
    if edycja <= 9: return 4
    if edycja <= 31: return 5
    return 6

def etap2_tasks(edycja):
    if edycja == 1: return 3
    if edycja == 3: return 4
    return 5

def etap3_tasks(edycja):
    if edycja == 27: return 0
    if edycja == 1: return 4
    if edycja in [2,3]: return 5
    if edycja in [6,7,8,9,10,11,13,14,15,16,24]: return 6
    if edycja == 25: return 8
    return 7

MAX_EDYCJA_ETAP = {etap: {edycja: 0 for edycja in range(1,33)} for etap in [1,2,3]}
MAX_EDYCJA = {i: etap1_tasks(i)+etap2_tasks(i)+etap3_tasks(i) for i in range(1,33)}
for edycja in range(1,33):
    MAX_EDYCJA_ETAP[1][edycja] = etap1_tasks(edycja)
    MAX_EDYCJA_ETAP[2][edycja] = etap2_tasks(edycja)
    MAX_EDYCJA_ETAP[3][edycja] = etap3_tasks(edycja)

# --- liczniki ---
wbite_etap = {i:0 for i in range(1,4)}
wbite_edycja = {i:0 for i in range(1,33)}
wbite_etap_edycja = {etap: {edycja:0 for edycja in range(1,33)} for etap in [1,2,3]}

for entry in data.values():
    etap = entry["etap"]
    edycja = entry["edycja"]
    punkty = entry["punkty"]
    if punkty == 100:
        wbite_etap[etap] += 1
        wbite_edycja[edycja] += 1
        wbite_etap_edycja[etap][edycja] += 1

def percent(numerator, denominator):
    return int(100 * numerator / denominator) if denominator else 0

def color_for_pct(pct):
    if pct >= 100:
        return "gold"
    elif pct > 0:
        alpha = pct / 100
        return f'rgba(0,255,0,{alpha:.2f})'
    else:
        return 'rgba(0,0,0,0)'

def to_roman(n):
    vals = [
        (10, "X"), (9, "IX"), (8, "VIII"), (7,"VII"), (6,"VI"),
        (5,"V"), (4,"IV"), (3,"III"), (2,"II"), (1,"I")
    ]
    res = ""
    for val, sym in vals:
        while n >= val:
            res += sym
            n -= val
    return res

UNIT = 20
GAP = 3
BLOCK_GAP = 20
CENTRAL_SCALE = 3
num_editions = len(MAX_EDYCJA)

central_size = 3*UNIT + 2*GAP
width = central_size + BLOCK_GAP + 2*UNIT + BLOCK_GAP + num_editions*(UNIT+GAP) + 20
height = central_size + 15  # zostawimy miejsce na rzymskie cyfry

total_done = sum(wbite_etap.values())
total_max = sum(MAX_ETAP.values())
center_pct = percent(total_done, total_max)

svg_parts = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}">']

# centralny kwadrat
svg_parts.append(f'<rect x="0" y="0" width="{central_size}" height="{central_size}" fill="{color_for_pct(center_pct)}" stroke="white" stroke-width="1"/>')
svg_parts.append(f'<text x="{central_size/2}" y="{central_size/2}" text-anchor="middle" dominant-baseline="middle" font-size="20" fill="white" font-family="monospace">{center_pct}%</text>')

# prostokąty etapów z napisami
etap_labels = {1: "I", 2: "II", 3: "III"}
x0 = central_size + BLOCK_GAP + 4
for i, etap in enumerate([1,2,3]):
    y0 = i*(UNIT + GAP)
    pct = percent(wbite_etap[etap], MAX_ETAP[etap])
    svg_parts.append(f'<rect x="{x0}" y="{y0}" width="{2*UNIT}" height="{UNIT}" fill="{color_for_pct(pct)}" stroke="white" stroke-width="1">')
    svg_parts.append(f'<title>{etap} Etap – {pct}%</title></rect>')
    # numer etapu.
    svg_parts.append(f'<text x="{x0 - (BLOCK_GAP + 4) / 2}" y="{y0 + UNIT/2}" text-anchor="middle" dominant-baseline="middle" font-size="10" fill="white" font-family="monospace">{etap_labels[etap]}</text>')
    # procent w środku boxa.
    svg_parts.append(f'<text x="{x0 + UNIT}" y="{y0 + UNIT/2}" text-anchor="middle" dominant-baseline="middle" font-size="10" fill="white" font-family="monospace">{pct}%</text>')

# kwadraty edycji z tooltipami
x0 = central_size + BLOCK_GAP / 2 + 2*UNIT + BLOCK_GAP
for e_idx, edycja in enumerate(range(1, num_editions+1)):
    x_pos = x0 + e_idx*(UNIT+GAP)
    for etap in [1,2,3]:
        y0 = (etap-1)*(UNIT + GAP)
        pct = percent(wbite_etap_edycja[etap][edycja], MAX_EDYCJA_ETAP[etap][edycja])
        svg_parts.append(f'<rect x="{x_pos}" y="{y0}" width="{UNIT}" height="{UNIT}" fill="{color_for_pct(pct)}" stroke="white" stroke-width="1">')
        svg_parts.append(f'<title>{etap} Etap {edycja} OI – {pct}%</title></rect>')
    # rzymska cyfra pod kolumną
    svg_parts.append(f'<text x="{x_pos + UNIT/2}" y="{central_size + 12}" text-anchor="middle" dominant-baseline="middle" font-size="5" fill="white" font-family="monospace">{to_roman(edycja)}</text>')

svg_parts.append('</svg>')

with open("oi_progress.svg", "w", encoding="utf-8") as f:
    f.write("\n".join(svg_parts))

