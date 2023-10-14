BIN_NAME = main.out
CC_FLAGS = -Wall -Wextra
INCLUDES = -Ilibs/sfml/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES = $(wildcard src/*.cpp)
O_FILES = $(patsubst src/%.cpp, %.o, $(SRC_FILES))

all: clean build run

build:
	g++ -c $(SRC_FILES) $(CC_FLAGS) $(INCLUDES)
	g++ -o $(BIN_NAME) $(O_FILES) -Llibs/sfml/lib $(LIBS)

%.test: 
	g++ -c test/$@.cpp $(CC_FLAGS) $(INCLUDES)
	g++ $(CC_FLAGS) $@.o Environment.o Obstacle.o Vector.o RenderedObject.o -o test/bin/$@ -Llibs/sfml/lib -lcriterion $(LIBS)
	export LD_LIBRARY_PATH=libs/sfml/lib && ./test/bin/$@ --verbose

clean:
	rm -rf src/*.o src/*.out *.o *.out src/*.h.gch

run:
	export LD_LIBRARY_PATH=libs/sfml/lib && ./$(BIN_NAME)

.PHONY: all clean build run main
