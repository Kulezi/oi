#!/bin/bash
# Skrypt testujący rozwiązanie

if [ $# -ne 3 ]; then
    echo "usage: ./spr.sh <sol> <chk> <gen>"
    exit 1
fi


SOL=$1
CHK=$2
GEN=$3

RESET=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)

CC="g++ -g"
compile() {
    $CC $1.cpp -o $1
    return $?
}

compile $CHK && compile $SOL && compile $GEN

for i in {1..10000}; do
    echo -ne   "$i:" 
    ./$GEN > test.in
    ./$SOL < test.in > sol.out
    if [ $? -ne 0 ]; then
        echo "$RED[RE]$RESET"
        exit 1
    fi

    ./$CHK test.in sol.out
    if [ $? -ne 0 ]; then
        echo "$RED[WA]$RESET"
        exit 1
    else
        echo "$GREEN[OK]$RESET"
    fi
done
