g++ -g  -fno-sanitize-recover -fsanitize=address -fsanitize=undefined -Wshadow -Wall $1.cpp -o $1
echo "BEZ -O2"