#!/bin/bash
# Autor skryptu: Paweł Putra (https://github.com/kulezi)

# Szczegóły działania skryptu możesz poczytać w testuj.sh, tu jest tylko mały wycinek.
brute=$1
model=$2
gen=$3

make $brute || exit 1
make $model || exit 1
make $gen || exit 1

set +x

run() {
	/usr/bin/time -f "seconds=%e\nkbytes=%M\nexit_code=%x" -o $1.time \ 
	./$1 < test.in > $1.out 2> $1.err;

	source $1.time
	if [[ $exit_code -ne 0 ]]; then
		exit 1
	fi
}

for ((i=0; ; ++i)); do
    echo -ne "$i "
    ./$gen > test.in
    run $brute || exit 1
    run $model || exit 1

    cmp $brute.out $model.out || break
    source ${model}.time	
    echo -ne "[OK] ${seconds}s $(expr ${kbytes} / 1024)MB "
done

echo "[ERROR]"
