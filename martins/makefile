CC = g++
#CC = clang
FLAGS = -std=c++11 

main.out: main.cpp gameobject.o
	$(CC) $(FLAGS) main.cpp gameobject.o -o main.out
gameobject.o: gameobject.cpp
	$(CC) $(FLAGS) -c -o gameobject.o gameobject.cpp
clean:
	rm -f *.o *.out
