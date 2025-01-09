CC_FLAGS = 
INCLUDES = ../libs/sfml/include
LIBS = -L../libs/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
BIN_NAME = test.out

QuadTree: QuadTree.test.cpp ../src/Vector.cpp ../src/AreaShape.cpp ../src/singleton/ScreenManager.cpp
	rm -rf bin/*.o bin/*.out *.o *.out bin/*.h.gch

	cd bin && g++ -c $(patsubst %.cpp, ../%.cpp, $^) $(CC_FLAGS) -I../$(INCLUDES)
	g++ -o $(BIN_NAME) $(wildcard bin/*.o) $(CC_FLAGS) $(LIBS)
	export LD_LIBRARY_PATH=../libs/sfml/lib && ./$(BIN_NAME)
