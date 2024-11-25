#include "HighscoresManager.h"
#include <fstream>

void HighscoresManager::fetchHighScores() {
  std::ifstream names_file("highscores/names.txt");
  std::ifstream scores_file("highscores/scores.txt");

  string name;
  string score;

  int i = 0;

  while (getline(names_file, name)) {
    getline(scores_file, score);

    this->highscores.push_back({ std::stoi(score), name });
    i++;
  }

  this->num_highscores = i + 1;
  names_file.close();
  scores_file.close();
}

string HighscoresManager::formatHighscores() {
  this->fetchHighScores();

  string highscores_string = "Highscores:\n\n";

  int i = 1;
  for (auto& player : this->highscores) {
    highscores_string += std::to_string(i++) + ". " + player.second + " - " + std::to_string(player.first) + "s\n";
  }

  return highscores_string;
}