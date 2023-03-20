CXX = g++
CXX_FLAGS = -Wall -std=c++20

compile:
	${CXX} ${CXX_FLAGS} src/*.cpp main.cpp -o build/main

test_deposit:
	${CXX} ${CXX_FLAGS} src/*.cpp tests/test_deposit.cpp -o build/test_deposit