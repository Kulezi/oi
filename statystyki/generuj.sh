#!/bin/bash
python3 scraper.py
python3 parser.py # Sporo trzeba poczyścić danych żeby się nie wywalił :(
python3 gen_ranking.py
