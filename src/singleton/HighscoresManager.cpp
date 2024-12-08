#include "HighscoresManager.h"
#include <fstream>

HighscoresManager::HighscoresManager() {
  std::ifstream names_file("highscores/names.txt");
  std::ifstream scores_file("highscores/scores.txt");
  if (!names_file.good() || !scores_file.good()) HighscoresManager::saveHighscores();

  this->highscores_str = std::make_shared<string>("");
  this->updateHighscoresStr();
}

void HighscoresManager::fetchHighScores() {
  this->highscores.clear();

  std::ifstream names_file("highscores/names.txt");
  std::ifstream scores_file("highscores/scores.txt");

  string name;
  string score;

  int i = 0;

  while (getline(names_file, name)) {
    getline(scores_file, score);

    this->highscores.push_back({ std::stol(score), name });
    i++;
  }

  this->num_highscores = i + 1;
  names_file.close();
  scores_file.close();
}

void HighscoresManager::updateHighscoresStr() {
  this->fetchHighScores();

  string highscores_string = "Highscores:\n\n";

  int i = 1;
  for (auto& score : this->highscores) {
    string score_time = std::to_string((double)score.first/1000);
    score_time.erase ( score_time.find_last_not_of('0') + 1, std::string::npos );
    score_time.erase ( score_time.find_last_not_of('.') + 1, std::string::npos );
    highscores_string += std::to_string(i++) + ". " + score.second + " - " + score_time + "s\n";
  }

  if (i == 1) highscores_string += "None yet!";

  *this->highscores_str = highscores_string;
}

// Note: Only saves the score if its a highscore
void HighscoresManager::addScore(string name, long int milliseconds) {
  bool added = false;
  for (int i = 0; i < this->highscores.size(); i++) {
    pair<long int, string>& score = this->highscores[i];
    
    if (milliseconds < score.first) {
      added = true;
      this->highscores.insert(this->highscores.begin() + i, {milliseconds, name});
      while (this->highscores.size() > 5) this->highscores.pop_back();
      break;
    }
  }

  // if havent added but highscore list is less than 5...
  if (!added && this->highscores.size() < 5) this->highscores.push_back({milliseconds, name});

  HighscoresManager::saveHighscores();
  HighscoresManager::updateHighscoresStr();
}

void HighscoresManager::saveHighscores() {
  std::ofstream names_file("highscores/names.txt");
  std::ofstream scores_file("highscores/scores.txt");
  
  for (pair<long int, string>& score : this->highscores) {
    names_file << score.second << "\n";
    scores_file << std::to_string(score.first) << "\n";
  }

  names_file.close();
  scores_file.close();
}

bool HighscoresManager::isHighscore(long int milliseconds) {
  if (this->highscores.size() < 5) return true;

  for (pair<long int, string>& score : this->highscores)
    if (milliseconds < score.first) return true;
  
  return false;
}