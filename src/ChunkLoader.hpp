#ifndef CHUNK_LOADER_INCLUDE
#define CHUNK_LOADER_INCLUDE

// Data Structures
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>

// C++ APIs
#include <iostream>
#include <fstream>
#include <string>

// Abstract Classes
#include "Renderable.hpp"
#include "Block.hpp"
#include "Entity.hpp"
#include "Item.hpp"

// Namespaces
using std::vector;
using std::pair;
using std::unordered_map;
using std::unordered_set;
using std::string;

// Chunk structure
struct Chunk {
  // vector<Block*> blocks;
  // vector<Entity*> entities;
  // vector<Item*> items;
  vector<Renderable*> renderables;
};

// MapWrapper file handling class
class MapWrapper {
public:
  static void updateChunk(pair<int, int> coords, Chunk* chunk);
  static void readChunk(pair<int, int> coords, Chunk* chunk);
};

// ChunkLoader for managing chunks and render lists
class ChunkLoader {
  unordered_map<pair<int, int>, unordered_set<int>> active_chunks;
public:
  vector<Renderable*> getActiveChunks();
  pair<int, int> getChunkFromPos(Vector position);
  void loadChunk(pair<int, int> coords);
  void unLoadChunk(pair<int, int> coords);
  Vector convertGridCoordsToPosition();
};

#endif