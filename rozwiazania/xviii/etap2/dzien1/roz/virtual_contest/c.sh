#!/bin/bash

g++ -g -DGLIBCXX_DEBUG -DGLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -Wshadow -Wall $1.cpp -o $1