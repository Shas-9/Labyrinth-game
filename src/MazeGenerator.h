#ifndef MAZE_GENERATOR_INCLUDE
#define MAZE_GENERATOR_INCLUDE

#include "Obstacle.h"

#include <ctime>
#include <iostream>
#include <random>
#include <stack>
#include <utility>
#include <vector>
#include <stack>
#include <fstream>

using std::cout;
using std::endl;
using std::pair;
using std::stack;
using std::vector;

#define MAZE_WIDTH 14
#define MAZE_HEIGHT 14
#define MAZE_BOX_SIZE 200
#define MAZE_BOX_THICKNESS 48

#define Point pair<int, int>
#define PointList vector<Point>
#define PointConnections vector<pair<Point, Point>>

class MazeGenerator {
private:
  int obstacles_num;
  Obstacle* obstacles;

  void printGrid(int grid[][MAZE_HEIGHT]);
  void printPointsVisited(PointList points);
  int getOpenSideForPoint(Point target_point, Point reference_point);
  Obstacle** computeGrid(int x, int y, int gridSize, int boxSize, int thickness, PointConnections connections);
  void findConnectionsForBox(Point point, PointConnections connections, bool sides_of_box[]);
  void saveDataToFile();
  PointConnections generateMazePathConnections();
  void setValidMazeNeighboringPoints(
    int* possible_visiting_points_num_ptr,
    PointList* possible_visiting_points_ptr,
    PointList* points_visited_ptr, Point current_point
  );
public:
  void generatePaths();
  Obstacle* getObstacles();
};

#endif