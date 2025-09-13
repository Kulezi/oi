#!/bin/bash
# Autor skryptu: Paweł Putra (https://github.com/kulezi)

# Tu sobie ustawiamy flagi jakie chcemy, najlepiej z ustaleń technicznych konkursu.
# Ewentualnie debugowe.
compile() {
	g++ -g -O3 -static $1.cpp -o $1
}

# Nazwy plików bruta, wzorcówki i generatorki bez rozszerzeń.
brute=$1
model=$2
gen=$3

TL=1

# Przed testowaniem kompilujemy - wywalamy skrypt przy błędzie kompilacji.
# set -x sprawia, że terminal wypisuje wszystkie komendy które uruchamia a nie tylko ich wynik.
set -x 
compile $brute || exit 1
compile $model || exit 1
compile $gen || exit 1

# set +x wyłącza wypisywanie komend.
set +x

# 'run xyz' Odpala program o nazwie xyz z limitem czasu
# - zapisuje zużycie czasu i pamięci w pliku xyz.time
# - wyjście programu w pliku xyz.out
run() {
	# Zapisujemy istotne wyniki /usr/bin/time do pliku.
	# `\` pozwala podzielić komendę na kilka linijek.
    timeout $TL \
		/usr/bin/time -f "seconds=%e\nkbytes=%M\nexit_code=%x" -o $1.time \ 
		./$1 < test.in > $1.out 2> $1.err;

	# Ważne - jak nie damy spacji między nawiasami a argumentami to dostaniemy enigmatyczny `Syntax error`.
	# Operatory porównań: -ne (not equal), -ge (greater or equal), -lt (less than), -gt (greater than), -eq (equals).
    if [ $? -ne 0 ]; then 
		exit 1
	fi

	source $1.time
	if [[ $exit_code -ne 0 ]]; then
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
	
    echo -ne "[OK] ${seconds}s $(expr ${kbytes} / 1024)MB "
done

echo "[ERROR]"
