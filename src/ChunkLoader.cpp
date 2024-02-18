#include "ChunkLoader.hpp"

Renderable* getNewInstance(string type, Vector pos) {
  switch (type)
  {
  case "stone":
    return new Block(pos);
    break;
  
  default:
    break;
  }
}

// assumes the file for the chunk exists
void MapWrapper::readChunk(pair<int, int> coords, Chunk* chunk) {
  string file = "files/map_data/chunk" + std::to_string(coords.first) + "-" + std::to_string(coords.second);
  std::ifstream myfile(file); 
  
  

}