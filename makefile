main: main.o
	if [ -d build ]; then echo "Build directory already exists. Not making one."; else mkdir build; fi
	g++ $^ -o $@
	mv *.o build/

main.o: main.cpp include/matrix.hpp
	g++ -Iinclude -c main.cpp