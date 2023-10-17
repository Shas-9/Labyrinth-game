#include "UI.h"

#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define PLAY_BUTTON_COLOR sf::Color (22, 30, 43)
#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)
#define BUTTON_TEXT_SIZE int (40)
#define BUTTON_SIZE Vector (250, 110)

// Default constructor
UI::UI() { UI(Vector(600, 600)); }

// Overloaded constructor with width and height
UI::UI(int width, int height) { UI(Vector(width, height)); }

// Overloaded constructor with Vector
UI::UI(Vector screen_dimensions) {
  this->fetchHighScores();

  this->screen_dimensions = screen_dimensions;

  sf::RenderWindow window(sf::VideoMode(this->screen_dimensions.getX(),
    this->screen_dimensions.getY()),
    "CatQuest");

  this->window_ptr = &window;

  Button tutorial_btn("How to play", Vector(1344, 810), BUTTON_SIZE,
    TUTORIAL_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 5);

  Button play_button("Play Game", Vector(288, 810), BUTTON_SIZE,
    PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 5);

  sf::Event event;
  this->event_ptr = &event;

  // Screen loop
  while ((*this->window_ptr).isOpen()) {

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch (event.type) {
      case sf::Event::Closed:
        (*this->window_ptr).close();
        break;

      case sf::Event::MouseButtonPressed:
        if ((play_button.isMouseOver(*this->window_ptr))) {
          std::cout << "Play button pressed" << std::endl;
          bool menu_button_pressed = false;

          while(!(menu_button_pressed)) {
            menu_button_pressed = this->enterName();
          }
        } else if (tutorial_btn.isMouseOver(*this->window_ptr)) {

          std::cout << "Tutorial button pressed" << std::endl;
          bool menu_button_pressed = false;

          while (!(menu_button_pressed)) {
            menu_button_pressed = this->drawTutorial();
          }
        }
        break;

      case sf::Event::MouseMoved:
        if (play_button.isMouseOver(*this->window_ptr)) {
          play_button.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          play_button.setBackToColor(PLAY_BUTTON_COLOR);
        }

        if (tutorial_btn.isMouseOver(*this->window_ptr)) {
          tutorial_btn.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          tutorial_btn.setBackToColor(TUTORIAL_BUTTON_COLOR);
        }
        break;
      }
    }

    // Display on the screen
    (*this->window_ptr).clear();
    this->renderUI();
    play_button.drawButton(*this->window_ptr);
    tutorial_btn.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}

// Rendering the UI image
void UI::renderUI() {
  sf::Texture title;
  title.loadFromFile("images/UI.png",
    sf::IntRect(0, 0, this->screen_dimensions.getX(),
      this->screen_dimensions.getY()));

  sf::Text cat_title;
  sf::Font cat_font;
  cat_font.loadFromFile("fonts/cat_font.ttf");
  cat_title.setFont(cat_font);
  cat_title.setString("CatQuest");
  cat_title.setCharacterSize(200);
  cat_title.setFillColor(sf::Color::White);
  cat_title.setPosition(480, 350);


  sf::Sprite ui_title;
  ui_title.setTexture(title);
  (*this->window_ptr).draw(ui_title);
  (*this->window_ptr).draw(cat_title);
}

// Fetching the highscores from the highscores folder
void UI::fetchHighScores() {
  std::ifstream names_file("highscores/names.txt");
  std::ifstream scores_file("highscores/scores.txt");

  std::string name;
  std::string score;

  int i = 0;

  while (getline(names_file, name)) {
    getline(scores_file, score);

    this->highscores.insert({ name, std::stoi(score) });
    i++;
  }

  this->num_highscores = i + 1;
  names_file.close();
  scores_file.close();
}

// Displaying the tutorial screen
bool UI::drawTutorial() {
  std::string how_to_play;
  how_to_play = ("Gameplay Instructions:\n\n"
    "Use the 'W' 'A' 'S' 'D' keys to move around the screen. "
    "Find the cat within the maze to win.\n"
    "Avoid the spiders, they will decrease your health points. "
    "If your health reaches 0, you lose.\n\n"
    "Press the menu button to return to the menu.");

  sf::Texture background;
  background.loadFromFile("images/UI.png",
    sf::IntRect(0, 0, this->screen_dimensions.getX(),
      this->screen_dimensions.getY()));

  sf::Sprite bg_sprite;
  bg_sprite.setTexture(background);

  Button game_instructions(how_to_play, Vector(590, 420), Vector(650, 270),
    sf::Color::Black, sf::Color::White, 32);

  Button menu("Back to Menu", Vector(1382, 810), Vector(290, 120),
    PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 5);

  // Screen loop
  while ((*this->window_ptr).isOpen()) {

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch ((*this->event_ptr).type) {
      case sf::Event::Closed:
        (*this->window_ptr).close();
        break;

      case sf::Event::MouseButtonPressed:
        if ((menu.isMouseOver(*this->window_ptr))) {
          std::cout << "Menu button pressed" << std::endl;
          // menu_button_pressed = true;
          return true;
        }
        break;

      case sf::Event::MouseMoved:
        if (menu.isMouseOver(*this->window_ptr)) {
          menu.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          menu.setBackToColor(PLAY_BUTTON_COLOR);
        }
        break;
      }
    }

    // Display on the screen
    (*this->window_ptr).clear();
    (*this->window_ptr).draw(bg_sprite);
    game_instructions.drawButton(*this->window_ptr);
    menu.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}

void UI::drawGame() {
  
}

// Entering the name of the player screen
bool UI::enterName() {
  sf::Text enter_name;
  sf::Font score_font;
  score_font.loadFromFile("fonts/MouldyCheese.ttf");
  enter_name.setFont(score_font);
  enter_name.setString("Enter your name: ");
  enter_name.setCharacterSize(40);
  enter_name.setFillColor(sf::Color::White);
  enter_name.setPosition(1250, 450);

  sf::Text highscores_text;
  highscores_text.setFont(score_font);
  std::string highscores_string = "Highscores:\n\n";
  
  int i = 1;
  for (auto& player : this->highscores) {
    highscores_string += std::to_string(i++) + ". " + player.first + " - " + std::to_string(player.second) + "\n";
  }

  highscores_text.setString(highscores_string);
  highscores_text.setCharacterSize(50);
  highscores_text.setFillColor(sf::Color::White);
  highscores_text.setPosition(220, 450);


  sf::Texture background;
  background.loadFromFile("images/UI.png",
                          sf::IntRect(0, 0, this->screen_dimensions.getX(),
                          this->screen_dimensions.getY()));

  sf::Sprite bg_sprite;
  bg_sprite.setTexture(background);

  std::string name = "";
  Button name_entered(name, Vector(1260, 520), Vector(300, 100), sf::Color::White, sf::Color::Black, BUTTON_TEXT_SIZE, 10);
  name_entered.setCustomFont("fonts/MouldyCheese.ttf");

  sf::Text to_play;
  to_play.setFont(score_font);
  to_play.setString("Press enter to play");
  to_play.setCharacterSize(40);
  to_play.setFillColor(sf::Color::White);
  to_play.setPosition(1230, 650);

  Button menu("Back to Menu", Vector(1344, 840), Vector (300, 110),
    PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 8);


  // Screen loop
  while ((*this->window_ptr).isOpen()) {

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch ((*this->event_ptr).type) {

      case sf::Event::Closed:
        (*this->window_ptr).close();
        break;

      case sf::Event::KeyPressed:
        if ((*this->event_ptr).key.code == sf::Keyboard::BackSpace) {
          if (name.size() < 1) {
            break;
          }
          name.pop_back();
          name_entered.setString(name);
        }
        break;

      case sf::Event::TextEntered:
        if ((*this->event_ptr).text.unicode < 128 && (*this->event_ptr).text.unicode != 8 && (*this->event_ptr).text.unicode != 13) {
          name += static_cast<char>((*this->event_ptr).text.unicode);
          name_entered.setString(name);
        } else if ((*this->event_ptr).text.unicode == 13) {
          this->player_name = name;
          // Start timer here
          this->startGame();
          // End timer
          // Calculate score
          // this->showScoreScreen()
          return true;
        }
        break;

      case sf::Event::MouseMoved:
        if (menu.isMouseOver(*this->window_ptr)) {
          menu.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          menu.setBackToColor(PLAY_BUTTON_COLOR);
        }
        break;

      case sf::Event::MouseButtonPressed:
        if ((menu.isMouseOver(*this->window_ptr))) {
          std::cout << "Menu button pressed" << std::endl;
          // menu_button_pressed = true;
          return true;
        }
        break;
      }
    }

    // Display on the screen
    (*this->window_ptr).clear();
    (*this->window_ptr).draw(bg_sprite);
    (*this->window_ptr).draw(enter_name);
    (*this->window_ptr).draw(highscores_text);
    name_entered.drawButton(*this->window_ptr);
    (*this->window_ptr).draw(to_play);
    menu.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}

void UI::startGame() {
  this->game = Game(this->window_ptr, this->event_ptr, this->screen_dimensions);
}

void UI::pushHighScore() {
  int lowest_score = this->highscores.begin()->second;
  std::string key;

  for (auto& player : this->highscores) {
    if (player.second < lowest_score) {
      lowest_score = player.second;
      key = player.first;
    }
  }

  if (this->score >= lowest_score) {
    this->highscores.erase(key);
    this->highscores.insert({ this->player_name, this->score });

    std::vector <int> scores;
    for (auto& player : this->highscores) {
      scores.push_back(player.second);
    }

    // sorting the highscores from highest to lowest
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    std::map<std::string, int> new_highscores;
    for (int i = 0; i < scores.size(); i++) {
      for (auto& player : this->highscores) {
        if (player.second == scores[i]) {
          new_highscores.insert({ player.first, player.second });
        }
      }
    }

    this->highscores = new_highscores;

    std::ofstream names_file("highscores/names.txt");
    std::ofstream scores_file("highscores/scores.txt");

    for (auto& player : this->highscores) {
      names_file << player.first << "\n";
      scores_file << player.second << "\n";

      std::cout << player.first << " - " << player.second << std::endl;
    }
  }
}