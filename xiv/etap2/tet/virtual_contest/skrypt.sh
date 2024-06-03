make gen
make brut
make wzo
make chk

for i in {1..10000}
do
    echo -ne $i
    ./gen > test.in
    ./brut < test.in > brut.out
    ./wzo < test.in > wzo.out
    ./chk test.in brut.out wzo.out 2> /dev/null
    if [ $? -ne 0 ]; then
        echo OJEJKU
        exit 1
    fi

    echo " [OK]"
done