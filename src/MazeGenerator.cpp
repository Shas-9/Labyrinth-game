#include "MazeGenerator.hpp"

void MazeGenerator::setValidMazeNeighboringPoints(
  int* possible_visiting_points_num_ptr,
  PointList* possible_visiting_points_ptr,
  PointList* points_visited_ptr, Point current_point) {
  // This function takes in a point from the maze and a size for the
  // maze and returns all the neighboring elements for the point that
  // the point could randomly choose to go to. This function assumes
  // the point given is valid and lies within the specified size.

  // Initialize the vector for neighboring points/elements (each row
  // will store a point with x, y coordinates)
  PointList points_visited = *points_visited_ptr;

  // Add left neighboring element if it exists & not already vistied
  Point left_neighboring_point = { current_point.first - 1, current_point.second };
  if (
    left_neighboring_point.first >= 0 &&
    !std::count(points_visited.begin(), points_visited.end(), left_neighboring_point)
    ) {
    possible_visiting_points_ptr->push_back(left_neighboring_point);
    (*possible_visiting_points_num_ptr) += 1;
  }

  // Add right neighboring element if it exists & not already vistied
  Point right_neighboring_point = { current_point.first + 1, current_point.second };
  if (
    right_neighboring_point.first <= MAZE_WIDTH - 1 &&
    !std::count(points_visited.begin(), points_visited.end(), right_neighboring_point)
    ) {
    possible_visiting_points_ptr->push_back(right_neighboring_point);
    (*possible_visiting_points_num_ptr) += 1;
  }

  // Add top neighboring element if it exists & not already vistied
  Point top_neighboring_point = { current_point.first, current_point.second - 1 };
  if (
    top_neighboring_point.second >= 0 &&
    !std::count(points_visited.begin(), points_visited.end(), top_neighboring_point)
    ) {
    possible_visiting_points_ptr->push_back(top_neighboring_point);
    (*possible_visiting_points_num_ptr) += 1;
  }

  // Add bottom neighboring element if it exists & not already vistied
  Point bottom_neighboring_point = { current_point.first, current_point.second + 1 };
  if (
    bottom_neighboring_point.second <= MAZE_HEIGHT - 1 &&
    !std::count(points_visited.begin(), points_visited.end(), bottom_neighboring_point)
    ) {
    possible_visiting_points_ptr->push_back(bottom_neighboring_point);
    (*possible_visiting_points_num_ptr) += 1;
  }
}

// Utility function
void MazeGenerator::printGrid(int grid[][MAZE_HEIGHT]) {
  for (int i = 0; i < MAZE_WIDTH; i++) {
    for (int k = 0; k < MAZE_HEIGHT; k++) {
      std::cout << grid[i][k] << " ";
    }
    std::cout << std::endl;
  }
}

// Utility function
void MazeGenerator::printPointsVisited(PointList points) {
  int grid[MAZE_WIDTH][MAZE_HEIGHT];

  for (int i = 0; i < MAZE_WIDTH; i++) {
    for (int k = 0; k < MAZE_HEIGHT; k++) {
      grid[i][k] = 0;
    }
  }

  for (auto it = begin(points); it != end(points); ++it) {
    grid[it.base()->first][it.base()->second] = 1;
  }

  this->printGrid(grid);
}

PointConnections MazeGenerator::generateMazePathConnections() {
  /* initialize random seed: */
  srand(time(NULL));

  Point starting_point = { rand() % MAZE_WIDTH, rand() % MAZE_HEIGHT };

  PointList points_visited;
  points_visited.push_back(starting_point);

  stack<Point> points_stack;
  points_stack.push(starting_point);

  PointConnections points_connections = {};

  while (points_visited.size() < MAZE_WIDTH * MAZE_HEIGHT) {
    // Get the valid neighboring (the ones that havent been visited
    // before) elements of the latest added element (first row) of the
    // pointStack matrix
    // Get the number of the neighbors found
    int possible_visiting_points_num = 0;
    PointList possible_visiting_points;
    this->setValidMazeNeighboringPoints(
      &possible_visiting_points_num,
      &possible_visiting_points,
      &points_visited,
      points_stack.top()
    );

    // Check that the number of neighbors is not zero (a dead end)
    if (possible_visiting_points_num != 0) {
      // Choose a random neighbor element to visit from the
      // valid neighboring elements/points
      int random_index = rand() % possible_visiting_points_num;
      Point chosen_visiting_point = possible_visiting_points.at(random_index);

      // The connection between the current location and the randomly
      // chosen location to visit next is added to the
      // 'pointsConnections' matrix to return the full set of
      // connections between each location and the other when the
      // function finishes.
      points_connections.push_back({ points_stack.top(), chosen_visiting_point });

      // Add the chosen element/point to the pointsVisited matrix and
      // the stack
      points_visited.push_back(chosen_visiting_point);
      points_stack.push(chosen_visiting_point);
    } else {
      // Else remove the latest visited point from the stack so that
      // the next loop will look for neighboring points for the
      // previous point since the current one has reached a dead end
      points_stack.pop();
    }
  }

  return points_connections;
}

void MazeGenerator::saveDataToFile() {
  std::ofstream outfile;

  outfile.open("map_preview.html", std::ios_base::out);

  outfile << "<!DOCTYPE html><html lang=\"en\"><head>    <meta charset=\"UTF-8\" />    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />    <title>Test</title>  </head>  <body>    <canvas id=\"canvas\"></canvas>    <script>      arr = [";

  for (int i = 0; i < this->obstacles_num; i++) {
    this->obstacles[i].printData(&outfile);
  }

  outfile << "];      const canvas = document.getElementById(\"canvas\");      const WIDTH = 7000;      const HEIGHT = 7000;      canvas.width = WIDTH;      canvas.height = HEIGHT;      const ctx = canvas.getContext(\"2d\");      ctx.fillStyle = \"#1aa7c7\";      ctx.fillRect(0, 0, WIDTH, HEIGHT);      ctx.fillStyle = \"black\";      arr.forEach((item) => {        ctx.fillRect(          item.position[0],          item.position[1],          item.dimensions[0],          item.dimensions[1]        );      });    </script>  </body></html>";

}

// Generates paths for the map and returns the corresponding obstacles array.
// Sets the obstacles_num attribute at the end of the function so that
// the length of the return array is known.
void MazeGenerator::generatePaths() {
  PointConnections connections = this->generateMazePathConnections();
  Obstacle** generated_obstacles = this->computeGrid(0, 0, MAZE_WIDTH, MAZE_BOX_SIZE, MAZE_BOX_THICKNESS, connections);

  this->obstacles = new Obstacle[this->obstacles_num];
  for (int i = 0; i < this->obstacles_num; i++) {
    this->obstacles[i] = *(generated_obstacles[i]);
  }

  this->saveDataToFile();
}

int MazeGenerator::getOpenSideForPoint(Point target_point, Point reference_point) {
  // This function takes in two points that are assumed to be
  // connected (has integer coordinates that make them next to each
  // other) and computes which side they are connected at (from the
  // perspective of the target point).

  // 0 = No connections found
  // 1 = left
  // 2 = right
  // 3 = top
  // 4 = bottom

  // If the two points share the same y-position (then they must be
  // horizontal neighbors)
  if (target_point.second == reference_point.second) {

    // Check if the connected side is to the left of the target point
    if (target_point.first - 1 == reference_point.first)
      return 1;   // Left


    // Check if the connected side is to the right of the target point
    if (target_point.first + 1 == reference_point.first)
      return 2;   // Right

  } else if (target_point.first == reference_point.first) {
    // If the two points share the same x-position (then they must be
    // vertical neighbors)

    // Check if the connected side is to the top of the target point
    if (target_point.second - 1 == reference_point.second)
      return 3;   // Top


    // Check if the connected side is to the bottom of the target point
    if (target_point.second + 1 == reference_point.second)
      return 4;   // Bottom
  }

  return 0;
}

// Returns a bool array of 4 elements, corresponding to each side of the box 
// and whether it should be shown or not
// 0th element: left
// 1st element: right
// 2nd element: top
// 3rd element: bottom
void MazeGenerator::findConnectionsForBox(Point point, PointConnections connections, bool sides_of_box[]) {
  // This function finds the connections that a point/box will have with
  // other neighboring boxes if any given a connections matrix

  // Set the sides of the box to be all shown by default (1 is for shown,
  // 0 is for hidden), (order goes as: left, right, top, bottom)
  // bool sides_of_box[4] = { true, true, true, true };

  // Loop through the connections matrix to process every single
  // connection between two points/boxes
  for (int connection_index = 0; connection_index < connections.size(); connection_index++) {

    // Define the two points/boxes in the current loop that share a
    // connection (first point and second point)
    Point first_connection_point = { connections[connection_index].first.first, connections[connection_index].first.second };
    Point second_connection_point = { connections[connection_index].second.first, connections[connection_index].second.second };

    // Check if the FIRST point in the connection is equal to our target
    // point (meaning that our target point must be connected to the
    // SECOND point)
    if (first_connection_point.first == point.first && first_connection_point.second == point.second) {

      // Get which side is the connected side between our target
      // point / box and the second connected point(if any)
      int open_side = getOpenSideForPoint(point, second_connection_point);

      // Set the side that is found to be connected between the two
      //   % points to be hidden for the point to paint the full maze
      if (open_side != 0) sides_of_box[open_side - 1] = false;
    }


    // Check if the SECOND point in the connection is equal to our target
    // point(meaning that our target point must be connected to the
    //   % FIRST point)
    else if (second_connection_point.first == point.first && second_connection_point.second == point.second) {

      // Get which side is the connected side between our target
      // point / box and the first connected point(if any)
      int open_side = getOpenSideForPoint(point, first_connection_point);

      // Set the side that is found to be connected between the two
      // points to be hidden for the point to paint the full maze
      if (open_side != 0) sides_of_box[open_side - 1] = false;
    }
  }
}

Obstacle** MazeGenerator::computeGrid(int x, int y, int gridSize, int boxSize, int thickness, PointConnections connections) {

  // This function computes the grid of a maze given the coordinates of
  // the grid, the gridSize (to create a gridSize*gridSize grid), a box
  // size for the dimensions of each singular box inside the grid, and the
  // thickness, and the connections between each two boxes in the grid.
  // Returns the obstacles used to create the maze in the totalObstacles.

  // Define a vector to store all the objects that will be created by the
  // drawBox functino when looping and creating the grid.
  vector<Obstacle*> total_obstacles = {};
  // Loop through every single box in the grid that will be painted using
  // a nested loop
  for (int row = 0; row < gridSize; row++) {
    for (int col = 0; col < gridSize; col++) {
      // Define which sides of the current box are connected (not
      // going to be drawn on the screen) with respect to its
      // neighboring boxes

      // Set the sides of the box to be all shown by default (1 is for shown,
      // 0 is for hidden), (order goes as: left, right, top, bottom)
      bool sides_of_box[4] = { true, true, true, true };
      this->findConnectionsForBox({ col, row }, connections, sides_of_box);

      // Left
      // Right
      // Top
      // Bottom
      if (row == gridSize && col == 0)
        sides_of_box[3] = false;
      else if (row == 0 && col == gridSize)
        sides_of_box[2] = false;


      // Define the x coordinate for the box (the horizontal sides of
      // the boxes in each column must be overlapping)
      double boxX = x + (col)*boxSize - (col)*thickness;

      // Define the y coordinate for the box (the vertical sides of
      // the boxes in each row must be overlapping)
      double boxY = y + (row)*boxSize - (row)*thickness;

      // Draw the current box in the screenState end extract the
      // rectangular obstacles used to make it

      // [boxObstacles] = computeBox(boxX, boxY, boxSize, thickness, sides_of_box);


      // If the left side is set to true add the left side of the box
      if (sides_of_box[0] == true) {
        Obstacle* obs = new Obstacle(Vector(boxX, boxY), "obstacle", Vector(thickness, boxSize));
        total_obstacles.push_back(obs);
      }


      // If the right side is set to true add the right side of the box
      if (sides_of_box[1] == true) {
        Obstacle* obs = new Obstacle(Vector(boxX + boxSize - thickness, boxY), "obstacle", Vector(thickness, boxSize));
        total_obstacles.push_back(obs);
      }


      // If the top side is set to true add the top side of the box
      if (sides_of_box[2] == true) {
        Obstacle* obs = new Obstacle(Vector(boxX, boxY), "obstacle", Vector(boxSize, thickness));
        total_obstacles.push_back(obs);
      }

      // If the bottom side is set to true add the bottom side of the box
      if (sides_of_box[3] == true) {
        Obstacle* obs = new Obstacle(Vector(boxX, boxY + boxSize - thickness), "obstacle", Vector(boxSize, thickness));
        total_obstacles.push_back(obs);
      }
    }
  }

  this->obstacles_num = total_obstacles.size();
  Obstacle** obstacles = new Obstacle * [this->obstacles_num];
  for (int i = 0; i < this->obstacles_num; i++)
  {
    obstacles[i] = total_obstacles[i];
  }

  // Obstacle* returned_obstacles = &total_obstacles[0];
  return obstacles;
}

Obstacle* MazeGenerator::getObstacles() { return this->obstacles; }
int MazeGenerator::getObstaclesNum() { return this->obstacles_num; }