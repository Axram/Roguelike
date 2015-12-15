CC = g++
#CC = clang
FLAGS = -std=c++11 

main.out: main.cpp gameobject.o wall.o camera.o functions.o player.o actor.o
	$(CC) $(FLAGS) main.cpp gameobject.o wall.o camera.o functions.o actor.o player.o -o main.out
gameobject.o: gameobject.cpp
	$(CC) $(FLAGS) -c -o gameobject.o gameobject.cpp
wall.o: wall.cpp
	$(CC) $(FLAGS) -c -o wall.o wall.cpp
camera.o: camera.cpp
	$(CC) $(FLAGS) -c -o camera.o camera.cpp
functions.o: functions.cpp
	$(CC) $(FLAGS) -c -o functions.o functions.cpp
actor.o: actor.cpp
	$(CC) $(FLAGS) -c -o actor.o actor.cpp
player.o: player.cpp
	$(CC) $(FLAGS) -c -o player.o player.cpp
map.o: map.cpp
	$(CC) $(FLAGS) -c -o map.o map.cpp
clean:
	rm -f *.o *.out
