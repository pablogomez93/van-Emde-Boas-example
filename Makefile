all:
	@g++ -std=c++11 tests.cpp vEB.cpp -o vEB

runtests:
	./vEB

clear:
	@rm vEB
