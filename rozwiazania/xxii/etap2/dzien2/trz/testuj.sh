#!/bin/bash

compile() {
    g++ -O3 -static -g $1.cpp -o $1
}

MODEL=$1
BRUTE=$2
GEN=$3

trap 'echo STOP; exit 0' INT

run() {
    /usr/bin/time -f "seconds=%e\nkbytes=%M\nexitcode=%x" -o $1.time ./$1 < test.in > $1.out 2> $1.err
}

info() {
    source $1.time
    echo -ne "(${1}: ${seconds}s, $((kbytes / 1024)) MB) "
}

set -x
compile $MODEL && compile $BRUTE && compile $GEN
set +x

for i in $(seq 1 100000); do
    echo -n $i

    ./$GEN > test.in
    run $1 
    run $2
    
    cmp $1.out $2.out
    if [[ $? -ne 0 ]]; then
        echo -ne " [FAIL] "
        exit 1
    fi

    echo -n " [OK] "
    info $1
    info $2
    echo ""

done
