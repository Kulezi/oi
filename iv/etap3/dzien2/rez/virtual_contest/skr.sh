compile() {
    g++ -g -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wshadow -Wconversion -DGLIBCXX_DEBUG -DGLIBCXX_DEBUG_PEDANTIC $1.cpp -o $1 || exit 1
}

compile rezw
compile rezb
compile rezg

for tc in {1..10000}
do
    printf "$tc\n\r"
    ./rezg > test.in
    ./rezb < test.in > brute.out
    ./rezw < test.in > wzo.out

    diff brute.out wzo.out || exit 1
done
