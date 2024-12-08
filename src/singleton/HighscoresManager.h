#ifndef HIGHSCORES_MANAGER_INCLUDE
#define HIGHSCORES_MANAGER_INCLUDE

#include "Singleton.h"
#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::pair;
using std::string;

class HighscoresManager : public Singleton<HighscoresManager> {
private:
  HighscoresManager();
  friend class Singleton<HighscoresManager>;
  
  vector<pair<long int, string>> highscores;
  int num_highscores;

  void saveHighscores();
  void updateHighscoresStr();
  void fetchHighScores();
public:
  std::shared_ptr<string> highscores_str;
  void addScore(string name, long int milliseconds);
  bool isHighscore(long int milliseconds);
};

#endif