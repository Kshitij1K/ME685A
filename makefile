main: main.o matrix.o
	g++ $^ -o $@

matrix.o: library/matrix.cpp include/matrix.hpp
	g++ -c library/matrix.cpp

main.o: main.cpp include/matrix.hpp
	g++ -c main.cpp