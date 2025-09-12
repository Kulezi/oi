#!/bin/bash

# Tu sobie ustawiamy flagi jakie chcemy, najlepiej z ustaleń technicznych konkursu.
# Ewentualnie debugowe.
compile() {
	echo "g++ -g -O3 -static $1.cpp -o $1"
	g++ -g -O3 -static $1.cpp -o $1
}

# Sprawdzamy czy poprawnie odpaliliśmy skrypt.
if [[ $# -lt 3 ]]; then
    echo "sposób użycia: ./testuj <brut> <wzorcówka> <generatorka> [limit czasu w sekundach]"
	echo ""
	echo "nazwy wpisuj bez końcówki .cpp,"
	echo "np. ./testuj kolb kol kolg 3"
    exit 1
fi

# Nazwy plików bruta, wzorcówki i generatorki bez rozszerzeń.
brute=$1
model=$2
gen=$3

# Ustawiamy time limit w sekundach, domyślnie sekunda.
TL=1
if [[ $# -gt 3 ]]; then
	TL=$4
fi

# Przed testowaniem kompilujemy - wywalamy skrypt przy błędzie kompilacji.
# set -x sprawia, że terminal wypisuje wszystkie komendy które uruchamia a nie tylko ich wynik.
set -x 
compile $brute || exit 1
compile $model || exit 1
compile $gen || exit 1

# set +x wyłącza wypisywanie komend.
set +x

# Kolory czcionki terminala, żeby ich użyć w echo przed napisem dopisz ${KOLOR}.
RESET=$(tput setaf sgr0) # Ten kolor przywraca domyślny kolor czcionki.
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
GRAY=$(tput setaf 244)


# Timeout domyślnie ignoruje CTRL+C i czeka aż program wytimeoutuje,
# przez co czasem trudno zatrzymać skrypt.
# Żeby zawsze od razu reagował na CTRL+C trzeba przechwycić CTRL+C trapem i go zabić.
trap 'echo "Aborted."; pkill -P $$; exit 1' INT

# 'run xyz' Odpala program o nazwie xyz z limitem czasu
# - zapisuje zużycie czasu i pamięci w pliku xyz.time
# - wyjście programu w pliku xyz.out
run() {
	# --foreground sprawia, że sygnał CTRL+C pójdzie też do programu a nie tylko do timeout.
    timeout --foreground $TL \
		/usr/bin/time -f "seconds=%e\nkbytes=%M\nexit_code=%x" -o $1.time \ # Zapisujemy istotne wyniki /usr/bin/time do pliku.
		./$1 < test.in > $1.out 2> $1.err;

	exit_code=$?
    # Jak program zakończył wykonanie z kodem 124 (SIGTERM) to znaczy, że komenda timeout go zabiła.
    if [ $exit_code -eq 124 ]; then
		echo "${BLUE}[TLE]${GRAY} ($1.cpp, exit code ${exit_code} }limit was set to ${TL} seconds)${RESET}"
        exit 1
    elif [ $exit_code -ne 0 ]; then 
		echo "${YELLOW}[RE]${GRAY} ($1, /usr/bin/time exit code ${exit_code})${RESET}"
		exit 1
	fi

	source $1.time
	if [[ $exit_code -ne 0 ]]; then
		echo "${YELLOW}[RE]${GRAY} ($1, exit code ${exit_code})${RESET}"
		echo "Check $1.err for details"
		exit 1
	fi
}

# Testujemy w nieskończoność, można dopisać np. i < 1000 do fora, żeby było mniej testów. 
for ((i=0; ; ++i)); do
    echo -ne "$i "
    ./$gen > test.in
    run $brute || exit 1
    run $model || exit 1

	# `cmp` wypisze nam tylko gdzie jest pierwszy błąd.
	# jeśli chcemy wszystkie można je zamienić na `diff`
	# Jak jest jakiś błąd przerywamy skrypt.
    cmp $brute.out $model.out || break

	# Wczytuje zużycie czasu i pamięci z pliku .time wyplutego przez wzorcówkę.
    source ${model}.time
	
    echo -ne "${GREEN}[OK]${RESET} ${seconds}s $(expr ${kbytes} / 1024)MB "

	source ${brute}.time
	echo "${GRAY}(brute: ${seconds}s $(expr ${kbytes} / 1024)MB${RESET})"

done

echo "${RED}[WA]${RESET}"
