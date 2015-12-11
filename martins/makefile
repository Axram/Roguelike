CC = g++
#CC = clang
FLAGS = -std=c++11 

main.out: main.cpp gameobject.o wall.o
	$(CC) $(FLAGS) main.cpp gameobject.o wall.o -o main.out
gameobject.o: gameobject.cpp
	$(CC) $(FLAGS) -c -o gameobject.o gameobject.cpp
wall.o: wall.cpp
	$(CC) $(FLAGS) -c -o wall.o wall.cpp
clean:
	rm -f *.o *.out
