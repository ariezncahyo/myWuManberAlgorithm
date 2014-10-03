run:main.o MyWu.o Matrix.o Vector.o Utility.o
	g++ -o run main.o MyWu.o Matrix.o Vector.o Utility.o
main.o:main.cpp MyWu.h matrix/Vector.h matrix/Utility.h matrix/Matrix.h
	g++ -c main.cpp 
MyWu.o:MyWu.cpp MyWu.h matrix/Matrix.h matrix/Vector.h matrix/Utility.h
	g++ -c MyWu.cpp 
Matrix.o: matrix/Matrix.cpp matrix/Matrix.h matrix/Vector.h matrix/Utility.h
	g++ -c matrix/Matrix.cpp
Vector.o: matrix/Vector.cpp matrix/Vector.h matrix/Utility.h
	g++ -c matrix/Vector.cpp
Utility.o: matrix/Utility.cpp matrix/Utility.h
	g++ -c matrix/Utility.cpp
clean:
	rm *.o
	rm run
