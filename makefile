CC = g++
#CC = clang
FLAGS = -std=c++11 -Wall -pedantic
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
main.out: $(OBJ_FILES)
	$(CC) $(FLAGS)  -I "/usr/include/"  -o $@ $^ -lncurses
obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $<
clean:
	rm -f obj/*.o *.out
