main: main.o matrix.o
	# if [ -d build ]; then echo "Build directory already exists. Not making one."; else mkdir build; fi
	g++ $^ -o yo
	# g++ vector.o -L. matrix.a 
	# mv *.o build/

main.o: main.cpp include/matrix.hpp include/vector.hpp
	g++ -Iinclude -c main.cpp

# vector.o: vector matrix.o
# 	g++ -c $^ -o $@

vector.o: library/vector.cpp library/vector_defs.cpp include/vector.hpp matrix.o
	g++ -Iinclude -Ilibrary -c library/vector.cpp -o $@ 

matrix.o: library/matrix.cpp library/matrix_calculations.cpp library/matrix_class_defs.cpp library/matrix_operations.cpp include/matrix.hpp
	g++ -Iinclude -Ilibrary -c library/matrix.cpp

# matrix_operations.o: library/matrix_operations.cpp include/matrix.hpp
# 	g++ -Iinclude -c library/matrix_operations.cpp

# matrix_class_defs.o: library/matrix_class_defs.cpp include/matrix.hpp
# 	g++ -Iinclude -c library/matrix_class_defs.cpp

# matrix_calculations.o: library/matrix_calculations.cpp include/matrix.hpp
# 	g++ -Iinclude -c library/matrix_calculations.cpp