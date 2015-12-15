CC = g++
#CC = clang
FLAGS = -std=c++11 
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
main.out: $(OBJ_FILES)
	$(CC) $(FLAGS) -o $@ $^
obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $<
clean:
	rm -f *.o *.out
