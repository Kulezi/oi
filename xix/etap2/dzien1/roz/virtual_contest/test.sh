#!/bin/bash

make $1
make $2
make $3

for i in {1..999999}
do
    ./$3> test.in
    ./$1 < test.in > brute.out
    ./$2 < test.in > model.out

    diff brute.out model.out
    if [ $? -ne 0 ]; then
        echo OJEJKU
        exit 1
    fi

    printf "$i [ OK ]\r"
done