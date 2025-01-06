BIN_NAME = main.out
CC_FLAGS = 
INCLUDES = -Ilibs/sfml/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES = $(wildcard src/singleton/*.cpp) $(wildcard src/*.cpp)
O_FILES = $(patsubst src/%.cpp, %.o, $(patsubst src/singleton/%.cpp, %.o, $(SRC_FILES)) )
TEST_O_FILES = $(patsubst main.o,, $(O_FILES))

all: build run

NewPlayer.o: src/NewPlayer.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

NewEntity.o: src/NewEntity.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

AnimController.o: src/AnimController.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Renderable.o: src/Renderable.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Camera.o: src/Camera.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

IronSpider.o: src/IronSpider.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Potion.o: src/Potion.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

RenderedObject.o: src/RenderedObject.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Item.o: src/Item.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

UI.o: src/UI.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Vector.o: src/Vector.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Obstacle.o: src/Obstacle.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Cat.o: src/Cat.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Entity.o: src/Entity.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Enemy.o: src/Enemy.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Button.o: src/Button.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Environment.o: src/Environment.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Player.o: src/Player.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

MazeGenerator.o: src/MazeGenerator.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Game.o: src/Game.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

TexturesHandler.o: src/TexturesHandler.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Screen.o: src/Screen.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

ScreenFactory.o: src/ScreenFactory.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

main.o: src/main.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Utility.o: src/singleton/Utility.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

Singleton.o: src/singleton/Singleton.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

ScreenManager.o: src/singleton/ScreenManager.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

HighscoresManager.o: src/singleton/HighscoresManager.cpp
	g++ -c $^ $(CC_FLAGS) $(INCLUDES)

build: $(O_FILES)
	g++ -o $(BIN_NAME) $(O_FILES) -Llibs/sfml/lib $(LIBS)

%.test: 
	g++ -c test/$@.cpp $(CC_FLAGS) $(INCLUDES)
	g++ $(CC_FLAGS) $@.o $(TEST_O_FILES) -o test/bin/$@ -Llibs/sfml/lib -lcriterion $(LIBS)
	export LD_LIBRARY_PATH=libs/sfml/lib && ./test/bin/$@ --verbose

clean:
	rm -rf src/*.o src/*.out *.o *.out src/*.h.gch

run:
	export LD_LIBRARY_PATH=libs/sfml/lib && ./$(BIN_NAME)

.PHONY: all clean build run main
