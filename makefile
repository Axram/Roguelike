CC = g++
#CC = clang
FLAGS = -std=c++11 

main.out: main.cpp gameobject.o wall.o map.o functions.o
	$(CC) $(FLAGS) main.cpp gameobject.o wall.o map.o functions.o -o main.out
gameobject.o: gameobject.cpp
	$(CC) $(FLAGS) -c -o gameobject.o gameobject.cpp
wall.o: wall.cpp
	$(CC) $(FLAGS) -c -o wall.o wall.cpp
map.o: map.cpp
	$(CC) $(FLAGS) -c -o map.o map.cpp
functions.o: functions.cpp
	$(CC) $(FLAGS) -c -o functions.o functions.cpp
clean:
	rm -f *.o *.out
