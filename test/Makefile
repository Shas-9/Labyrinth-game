CC_FLAGS = 
INCLUDES = -I../libs/sfml/include
BIN_NAME = test.out

QuadTree: ../src/PerformanceTester.cpp QuadTree.test.cpp
	rm -rf bin/*.o bin/*.out *.o *.out bin/*.h.gch

	cd bin && g++ -c $(patsubst %.cpp, ../%.cpp, $^) $(CC_FLAGS) $(INCLUDES)
	g++ -o $(BIN_NAME) $(wildcard bin/*.o) $(CC_FLAGS) $(INCLUDES)
	export LD_LIBRARY_PATH=libs/sfml/lib && ./$(BIN_NAME)
