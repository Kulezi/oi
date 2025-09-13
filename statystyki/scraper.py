#!/usr/bin/env python3
import requests
import time
import os
from pathlib import Path

BASE = "https://oi.edu.pl/l"
OUTDIR = Path("oi_pages")
OUTDIR.mkdir(exist_ok=True)

HEADERS = {
    "User-Agent": "Mozilla/5.0 (compatible; oi-downloader/1.0; +https://example.com)"
}

def fetch(url, attempts=3, backoff=1.5):
    for i in range(1, attempts+1):
        try:
            resp = requests.get(url, headers=HEADERS, timeout=20)
            resp.raise_for_status()
            return resp.text
        except requests.RequestException as e:
            print(f"Próba {i}/{attempts} nie powiodła się dla {url}: {e}")
            if i < attempts:
                sleep = backoff ** i
                print(f"  czekam {sleep:.1f}s przed ponowną próbą...")
                time.sleep(sleep)
    return None

def main():
    for etap in range(1, 4):
        for edycja in range(1, 33):
            url = f"{BASE}/{edycja}oi_{etap}etap_wyniki/"
            outfile = OUTDIR / f"{edycja}oi_{etap}etap.html"
            print(f"Pobieram etap {etap}: {url}")
            content = fetch(url)
            if content is None:
                print(f"  Błąd: nie udało się pobrać {url}")
                continue
            outfile.write_text(content, encoding="utf-8")
            print(f"  Zapisano -> {outfile}")
            time.sleep(0.1)  # krótka przerwa między żądaniami (by nie obciążać serwera)

    print("Zakończono.")

if __name__ == "__main__":
    main()

