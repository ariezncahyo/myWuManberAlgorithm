CC = g++
main = main_testTime


run:$(main).o MyWu.o Matrix.o Vector.o Utility.o getData.o
	$(CC) -o run $(main).o MyWu.o Matrix.o Vector.o Utility.o getData.o
$(main).o:$(main).cpp MyWu.h matrix/Vector.h matrix/Utility.h matrix/Matrix.h getData.h
	$(CC) -c -g $(main).cpp 
MyWu.o:MyWu.cpp MyWu.h matrix/Matrix.h matrix/Vector.h matrix/Utility.h
	$(CC) -c -g MyWu.cpp 
Matrix.o: matrix/Matrix.cpp matrix/Matrix.h matrix/Vector.h matrix/Utility.h
	$(CC) -c -g matrix/Matrix.cpp
Vector.o: matrix/Vector.cpp matrix/Vector.h matrix/Utility.h
	$(CC) -c -g matrix/Vector.cpp
Utility.o: matrix/Utility.cpp matrix/Utility.h
	$(CC) -c -g matrix/Utility.cpp
getData.o: getData.cpp getData.h
	$(CC) -c -g getData.cpp
clean:
	rm *.o
	rm run
