./compile.sh rycb
./compile.sh rycw
./compile.sh rycg

for i in {1..10000}
do
    echo $i
    ./rycg > test.in
    ./rycb < test.in > brut.out
    ./rycw < test.in > wzo.out

    diff brut.out wzo.out || exit 1
done