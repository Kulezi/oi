#!/bin/bash

./c.sh rozb
./c.sh rozg
./c.sh rozw

for test in {1..1000000}; do
    echo $test
    ./rozg > test.in
    time ./rozw < test.in 2>&1 >/dev/null
done

echo OJEJKU