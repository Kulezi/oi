#!/bin/bash

make brut
make wzo
make gen

for i in {1..1000}
do
    echo $i
    ./gen > test.in
    ./brut < test.in > brut.out
    ./wzo < test.in > wzo.out
    
    diff brut.out wzo.out
    if [ $? -ne 0 ]; then
        echo OJEJKU
        exit 1
    fi
done