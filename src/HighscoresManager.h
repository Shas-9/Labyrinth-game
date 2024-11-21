#ifndef HIGHSCORES_MANAGER_INCLUDE
#define HIGHSCORES_MANAGER_INCLUDE

#include "global.h"
#include "Button.h"
#include <vector>

using std::vector;
using std::pair;
using std::string;

class HighscoresManager {
private:
  HighscoresManager();
  vector<pair<int, string>> highscores;
  int num_highscores;
public:
  static HighscoresManager& getInstance();
  HighscoresManager(HighscoresManager const&) = delete;
  void operator=(HighscoresManager const&) = delete;

  void fetchHighScores();
  string formatHighscores();
};

#endif