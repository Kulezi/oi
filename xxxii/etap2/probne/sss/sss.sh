#!/bin/bash
g++ -O2 sss.cpp -o sss
g++ -O2 sssg.cpp -o sssg
subtasks="3"
for subtask in $subtasks; do
    for i in {1..10}; do
        echo $subtask | ./sssg > test.in
        echo -ne ${subtask}_${i}
        ./sss < test.in >/dev/null
    done

done