CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++20

compile:
	${CXX} ${CXX_FLAGS} src/*.cpp main.cpp -o build/main

test_deposit:
	${CXX} ${CXX_FLAGS} src/*.cpp tests/test_deposit.cpp -o build/test_deposit

test_bank_account:
	${CXX} ${CXX_FLAGS} src/*.cpp tests/test_bank_account.cpp -o build/test_bank_account

test_copy:
	${CXX} ${CXX_FLAGS} src/*.cpp copy.cpp -o build/copy

clean:
	rm build/*