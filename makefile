main: main.o
	if [ -d build ]; then echo "Build directory already exists. Not making one."; else mkdir build; fi
	g++ -g $^ -o $@
	mv *.o build/

main.o: main.cpp include/matrix.hpp include/vector.hpp include/nr.hpp
	g++ -Iinclude -g -c main.cpp