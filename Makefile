BIN_NAME = main.out
CC_FLAGS = -Wall -Wextra
INCLUDES = -Ilibs/sfml/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES = $(wildcard src/*.cpp src/*.h)
#OBJ_FILES = $(wildcard src/*.cpp)
#OBJ_FILES := $(filter %.o,$(SRC_FILES:.cpp=.o))

build:
	g++ -c $(SRC_FILES) $(CC_FLAGS)
	g++ -o $(BIN_NAME) test.o foo.o $(INCLUDES) $(LIBS)

clean:
	rm -rf src/*.o src/*.out *.o *.out

run:
	./$(BIN_NAME)

test:
	echo UNIMPLEMENTED

all: clean build run

.PHONY: all clean build run test
