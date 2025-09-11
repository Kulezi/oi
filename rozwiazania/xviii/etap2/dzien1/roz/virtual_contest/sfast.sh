#!/bin/bash

./cfast.sh rozb
./cfast.sh rozg
./cfast.sh rozw

for test in {1..1000000}; do
    echo $test
    ./rozg > test.in
    ./rozb < test.in > b.out
    ./rozw < test.in > w.out
    diff b.out w.out || break
done

echo OJEJKU