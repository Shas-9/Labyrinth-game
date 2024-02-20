#include "ChunkLoader.hpp"

Renderable* getNewInstance(string type, Vector pos) {
  if (type == "stone") return new Block(pos);
  // if (type == "spider") return new IronSpider();

  return NULL;
}

// assumes the file for the chunk exists
void MapWrapper::readChunk(pair<int, int> coords, Chunk* chunk) {
  string file = "files/map_data/chunk" + std::to_string(coords.first) + "-" + std::to_string(coords.second);
  std::ifstream myfile(file);

  bool awaiting_title = true;
  string current_title = "";

  string first_coord = "";
  string second_coord = "";

  string token;
  if (myfile.is_open()) {
    while (myfile.good()) {
      myfile >> token;
      if (awaiting_title) {
        current_title = token;
        awaiting_title = false;
      } else if (!awaiting_title) {
        myfile >> first_coord;
        if (first_coord == "---") {
          awaiting_title = true;
          continue;
        }
        myfile >> second_coord;

        chunk->renderables.push_back(getNewInstance(current_title, Vector(std::stoi(first_coord), std::stoi(second_coord))));
      }
    }
  }

  myfile.close();
}