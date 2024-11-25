#ifndef HIGHSCORES_MANAGER_INCLUDE
#define HIGHSCORES_MANAGER_INCLUDE

#include "Singleton.h"
#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::string;

class HighscoresManager : public Singleton<HighscoresManager> {
private:
  friend class Singleton<HighscoresManager>;
  vector<pair<int, string>> highscores;
  int num_highscores;
public:
  void fetchHighScores();
  string formatHighscores();
};

#endif