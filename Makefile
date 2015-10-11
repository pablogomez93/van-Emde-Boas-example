all:
	@g++ -std=c++11 test.cpp vEB.cpp -o vEB

runtests:
	./vEB

clear:
	@rm vEB
