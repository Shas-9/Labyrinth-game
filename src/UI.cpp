#include "UI.h"
#include "ScreenFactory.h"

#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define PLAY_BUTTON_COLOR sf::Color (22, 30, 43)
#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)

// TODO:
// needs to be responsive.. cant use macros for this
// maybe move to the utils class?
#define BUTTON_TEXT_SIZE int (30)
#define BUTTON_SIZE XVEC(Vector(0.2, 0.1))

// Default constructor
UI::UI() { UI(Vector(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)); }

// Overloaded constructor with width and height
UI::UI(int width, int height) { UI(Vector(width, height)); }

// Overloaded constructor with Vector
UI::UI(Vector screen_dimensions) {
  ScreenManager::getInstance().current_screen_i = 0;
  // this->fetchHighScores();

  this->screen_dimensions = screen_dimensions;
  UTIL_CLASS.setScreenDimensions(screen_dimensions);

  sf::RenderWindow window(sf::VideoMode(this->screen_dimensions.getX(),
    this->screen_dimensions.getY()),
    "CatQuest");

  this->window_ptr = &window;
  UTIL_CLASS.setWindowObject(this->window_ptr);

  // registerMainScreen()
  // registerTutorialScreen()
  // registerEnterNameScreen()
  // registerGameScreen()
  // registerPauseGameScreen()
  // registerQuitScreen()
  // registerConfirmationScreen()
  ScreenManager::getInstance().screens.push_back(ScreenFactory::mainScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::tutorialScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::highscoresScreen());
  
  sf::Event event;
  this->event_ptr = &event;

  // Screen loop
  while ((*this->window_ptr).isOpen()) {
    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      ScreenManager::getInstance().screens[ScreenManager::getInstance().current_screen_i].update(event);
    }

    // Rendering
    (*this->window_ptr).clear();
    ScreenManager::getInstance().screens[ScreenManager::getInstance().current_screen_i].render();
    (*this->window_ptr).display();
  }
}

// // Rendering the UI image
// void UI::renderUI() {
//   sf::Texture background;
//   background.loadFromFile("images/UI.png", sf::IntRect(0, 0, 1920, 1080));

//   sf::Text cat_title;
//   sf::Font cat_font;
//   cat_font.loadFromFile("fonts/cat_font.ttf");
//   cat_title.setFont(cat_font);
//   cat_title.setString("CatQuest");
//   cat_title.setCharacterSize(this->screen_dimensions.getX()/8);
//   cat_title.setFillColor(sf::Color::White);
//   Vector cat_title_pos = XVEC(Vector(0.2, 0.1));
//   cat_title.setPosition(cat_title_pos.getX(), cat_title_pos.getY());


//   sf::Sprite bg_sprite;
//   bg_sprite.setScale(this->screen_dimensions.getY()/1080, this->screen_dimensions.getY()/1080);
//   bg_sprite.setTexture(background);
//   (*this->window_ptr).draw(bg_sprite);
//   (*this->window_ptr).draw(cat_title);
// }

// // Fetching the highscores from the highscores folder
// void UI::fetchHighScores() {
//   std::ifstream names_file("highscores/names.txt");
//   std::ifstream scores_file("highscores/scores.txt");

//   std::string name;
//   std::string score;

//   int i = 0;

//   while (getline(names_file, name)) {
//     getline(scores_file, score);

//     this->highscores.insert({ std::stoi(score), name });
//     i++;
//   }

//   this->num_highscores = i + 1;
//   names_file.close();
//   scores_file.close();
// }

// // Displaying the tutorial screen
// bool UI::drawTutorial() {
//   std::string how_to_play;
//   how_to_play = ("Gameplay Instructions:\n\n"
//     "Use the 'W' 'A' 'S' 'D' keys to move around the screen. "
//     "Find the cat within the maze to win.\n"
//     "Avoid the spiders, they will decrease your health points. "
//     "If your health reaches 0, you lose.\n\n"
//     "Press the menu button to return to the menu.");

//   sf::Texture background;
//   background.loadFromFile("images/UI.png", sf::IntRect(0, 0, 1920, 1080));

//   sf::Sprite bg_sprite;
//   bg_sprite.setTexture(background);
//   bg_sprite.setScale(this->screen_dimensions.getY()/1080, this->screen_dimensions.getY()/1080);

//   Button game_instructions(how_to_play, XVEC(Vector(0.05, 0.2)), XVEC(Vector(0.8, 0.4)),
//     sf::Color::Transparent, sf::Color::White, this->screen_dimensions.getX()/60);

//   Button menu("Back to Menu", XVEC(Vector(0.6, 0.70)), XVEC(Vector(0.22, 0.09)),
//     PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);

//   // Screen loop
//   while ((*this->window_ptr).isOpen()) {

//     // Event loop
//     while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
//       switch ((*this->event_ptr).type) {
//       case sf::Event::Closed:
//         (*this->window_ptr).close();
//         break;

//       case sf::Event::MouseButtonPressed:
//         if ((menu.isMouseOver(*this->window_ptr))) {
//           std::cout << "Menu button pressed" << std::endl;
//           // menu_button_pressed = true;
//           return true;
//         }
//         break;

//       case sf::Event::MouseMoved:
//         if (menu.isMouseOver(*this->window_ptr)) {
//           // menu.setBackToColor(MOUSE_OVER_COLOR);
//         } else {
//           // menu.setBackToColor(PLAY_BUTTON_COLOR);
//         }
//         break;
//       }
//     }

//     // Display on the screen
//     (*this->window_ptr).clear();
//     (*this->window_ptr).draw(bg_sprite);
//     game_instructions.drawButton(*this->window_ptr);
//     menu.drawButton(*this->window_ptr);
//     (*this->window_ptr).display();
//   }
//   return true;
// }

// // Entering the name of the player screen
// bool UI::enterName() {
//   sf::Text enter_name;
//   sf::Font score_font;
//   score_font.loadFromFile("fonts/MouldyCheese.ttf");
//   enter_name.setFont(score_font);
//   enter_name.setString("Enter your name: ");
//   enter_name.setCharacterSize(40);
//   enter_name.setFillColor(sf::Color::White);
//   enter_name.setPosition(1250, 450);

//   sf::Text highscores_text;
//   highscores_text.setFont(score_font);
//   std::string highscores_string = "Highscores:\n\n";

//   int i = 1;
//   for (auto& player : this->highscores) {
//     highscores_string += std::to_string(i++) + ". " + player.second + " - " + std::to_string(player.first) + "s\n";
//   }

//   highscores_text.setString(highscores_string);
//   highscores_text.setCharacterSize(50);
//   highscores_text.setFillColor(sf::Color::White);
//   highscores_text.setPosition(220, 450);


//   sf::Texture background;
//   background.loadFromFile("images/UI.png",
//     sf::IntRect(0, 0, this->screen_dimensions.getX(),
//       this->screen_dimensions.getY()));

//   sf::Sprite bg_sprite;
//   bg_sprite.setTexture(background);

//   std::string name = "";
//   Button name_entered(name, Vector(1260, 520), Vector(300, 100), sf::Color::White, sf::Color::Black, BUTTON_TEXT_SIZE, 10);
//   name_entered.setCustomFont("fonts/MouldyCheese.ttf");

//   sf::Text to_play;
//   to_play.setFont(score_font);
//   to_play.setString("Press enter to play");
//   to_play.setCharacterSize(40);
//   to_play.setFillColor(sf::Color::White);
//   to_play.setPosition(1230, 650);

//   Button menu("Back to Menu", Vector(1344, 840), Vector(300, 110),
//     PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 8);


//   // Screen loop
//   while ((*this->window_ptr).isOpen()) {

//     // Event loop
//     while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
//       switch ((*this->event_ptr).type) {

//       case sf::Event::Closed:
//         (*this->window_ptr).close();
//         break;

//       case sf::Event::KeyPressed:
//         if ((*this->event_ptr).key.code == sf::Keyboard::BackSpace) {
//           if (name.size() < 1) {
//             break;
//           }
//           name.pop_back();
//           name_entered.setString(name);
//         }
//         break;

//       case sf::Event::TextEntered:
//         if (
//           (*this->event_ptr).text.unicode < 128 && (*this->event_ptr).text.unicode >= 32
//           ) {
//           name += static_cast<char>((*this->event_ptr).text.unicode);
//           name_entered.setString(name);
//         } else if ((*this->event_ptr).text.unicode == 13) {
//           this->player_name = name;
//           // Start timer here
//           this->startGame();
//           // End timer
//           // Calculate score
//           // this->showScoreScreen()
//           return true;
//         }
//         break;

//       case sf::Event::MouseMoved:
//         if (menu.isMouseOver(*this->window_ptr)) {
//           // menu.setBackToColor(MOUSE_OVER_COLOR);
//         } else {
//           // menu.setBackToColor(PLAY_BUTTON_COLOR);
//         }
//         break;

//       case sf::Event::MouseButtonPressed:
//         if ((menu.isMouseOver(*this->window_ptr))) {
//           std::cout << "Menu button pressed" << std::endl;
//           // menu_button_pressed = true;
//           return true;
//         }
//         break;
//       }
//     }

//     // Display on the screen
//     (*this->window_ptr).clear();
//     (*this->window_ptr).draw(bg_sprite);
//     (*this->window_ptr).draw(enter_name);
//     (*this->window_ptr).draw(highscores_text);
//     name_entered.drawButton(*this->window_ptr);
//     (*this->window_ptr).draw(to_play);
//     menu.drawButton(*this->window_ptr);
//     (*this->window_ptr).display();
//   }
//   return true;
// }

// void UI::startGame() {
//   sf::Clock* clock = new sf::Clock();
//   this->clock = clock;
//   this->game = Game(this->window_ptr, this->event_ptr, this->screen_dimensions, this->clock);
//   if (this->game.isGameWon()) {
//     this->score = this->game.getScore();
//     this->gameWinScreen();
//   } else {
//     this->gameOverScreen();
//   }
// }

// void UI::pushHighScore() {
//   int lowest_score = this->highscores.begin()->first;
//   int key;

//   for (auto& player : this->highscores) {
//     if (player.first < lowest_score) {
//       lowest_score = player.first;
//       key = player.first;
//     }
//   }

//   if (this->score <= lowest_score) {
//     this->highscores.erase(key);
//     this->highscores.insert({ this->score, this->player_name });

//     std::vector<int> scores;
//     for (auto& player : this->highscores) {
//       scores.push_back(player.first);
//     }

//     // Sorting the highscores from lowest to highest
//     std::sort(scores.begin(), scores.end());

//     // Create a new map to store the sorted highscores
//     std::map<int, std::string> new_highscores;
//     for (int i = 0; i < scores.size(); i++) {
//       for (auto& player : this->highscores) {
//         if (scores[i] == player.first) {
//           new_highscores.insert({ player.first, player.second });
//         }
//       }
//     }

//     this->highscores = new_highscores;

//     std::ofstream names_file("highscores/names.txt");
//     std::ofstream scores_file("highscores/scores.txt");

//     // Write the sorted highscores to the files
//     for (auto& player : new_highscores) {
//       names_file << player.first << "\n";
//       scores_file << player.second << "\n";
//     }
//   }
// }


// bool UI::gameOverScreen() {
//   sf::Texture texture;
//   texture.loadFromFile("images/UI.png");
//   sf::Sprite sprite;
//   sprite.setTexture(texture);

//   sf::Text game_over_text;
//   game_over_text.setString("Game Over");
//   game_over_text.setCharacterSize(130);
//   game_over_text.setFillColor(sf::Color::White);
//   game_over_text.setPosition(sf::Vector2f(650, 350));

//   sf::Font font;
//   font.loadFromFile("fonts/MouldyCheese.ttf");
//   game_over_text.setFont(font);

//   sf::Text prompt_text;
//   prompt_text.setString("You died without finding the cat");
//   prompt_text.setCharacterSize(46);
//   prompt_text.setFillColor(sf::Color::White);
//   prompt_text.setPosition(sf::Vector2f(630, 600));
//   prompt_text.setFont(font);

//   Button menu_button("Main Menu", Vector(1300, 800), BUTTON_SIZE, PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);

//   // Screen loop
//   while ((*this->window_ptr).isOpen()) {

//     //event loop
//     while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
//       switch ((*this->event_ptr).type) {
//       case sf::Event::Closed:
//         (*this->window_ptr).close();
//         break;

//       case sf::Event::MouseMoved:
//         if (menu_button.isMouseOver(*this->window_ptr)) {
//           // menu_button.setBackToColor(MOUSE_OVER_COLOR);
//         } else {
//           // menu_button.setBackToColor(PLAY_BUTTON_COLOR);
//         }
//         break;

//       case sf::Event::MouseButtonPressed:
//         if (menu_button.isMouseOver(*this->window_ptr)) {
//           std::cout << "Menu button pressed" << std::endl;
//           return true;
//         }
//         break;
//       }
//     }

//     (*this->window_ptr).clear();

//     (*this->window_ptr).draw(sprite);
//     (*this->window_ptr).draw(game_over_text);
//     menu_button.drawButton(*this->window_ptr);
//     (*this->window_ptr).draw(prompt_text);

//     (*this->window_ptr).display();
//   }
//   return true;
// }

// bool UI::gameWinScreen() {
//   sf::Texture texture;
//   sf::Sprite sprite;
//   texture.loadFromFile("images/UI.png");
//   sprite.setTexture(texture);

//   sf::Text game_win_text;
//   game_win_text.setString("Meow!");
//   game_win_text.setCharacterSize(180);
//   game_win_text.setFillColor(sf::Color::White);
//   game_win_text.setPosition(sf::Vector2f(650, 100));

//   sf::Font cat_font;
//   cat_font.loadFromFile("fonts/cat_font.ttf");
//   game_win_text.setFont(cat_font);

//   sf::Text prompt_text;
//   prompt_text.setString("You found the cat!");
//   prompt_text.setCharacterSize(48);
//   prompt_text.setFillColor(sf::Color::White);
//   prompt_text.setPosition(sf::Vector2f(100, 600));

//   sf::Font font;
//   font.loadFromFile("fonts/MouldyCheese.ttf");
//   prompt_text.setFont(font);

//   sf::Text time_text;
//   time_text.setString("Time: " + std::to_string((int)this->clock->getElapsedTime().asSeconds()) + "s");
//   time_text.setCharacterSize(46);
//   time_text.setFillColor(sf::Color::White);
//   time_text.setFont(font);
//   time_text.setPosition(sf::Vector2f(155, 700));

//   sf::Text new_highscore_text;
//   new_highscore_text.setString("New Highscore!");
//   new_highscore_text.setCharacterSize(70);
//   new_highscore_text.setFillColor(sf::Color::White);
//   new_highscore_text.setFont(font);
//   new_highscore_text.setPosition(sf::Vector2f(680, 340));

//   if (this->clock->getElapsedTime().asSeconds() < this->highscores.rbegin()->first) {
//     this->pushHighScore();
//   }

//   sf::Text highscores_text;
//   highscores_text.setFont(font);
//   std::string highscores_string = "Highscores:\n\n";

//   int i = 1;
//   for (auto& player : this->highscores) {
//     highscores_string += std::to_string(i++) + ". " + player.second + " - " + std::to_string(player.first) + "s\n";
//   }

//   highscores_text.setString(highscores_string);
//   highscores_text.setCharacterSize(44);
//   highscores_text.setFillColor(sf::Color::White);
//   highscores_text.setPosition(1380, 450);
//   highscores_text.setFont(font);

//   Button menu_button("Main Menu", Vector(1400, 850), BUTTON_SIZE, PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);

//   // Screen loop
//   while ((*this->window_ptr).isOpen()) {

//     //event loop
//     while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
//       switch ((*this->event_ptr).type) {
//       case sf::Event::Closed:
//         (*this->window_ptr).close();
//         break;

//       case sf::Event::MouseMoved:
//         if (menu_button.isMouseOver(*this->window_ptr)) {
//           // menu_button.setBackToColor(MOUSE_OVER_COLOR);
//         } else {
//           // menu_button.setBackToColor(PLAY_BUTTON_COLOR);
//         }
//         break;

//       case sf::Event::MouseButtonPressed:
//         if (menu_button.isMouseOver(*this->window_ptr)) {
//           std::cout << "Menu button pressed" << std::endl;
//           return true;
//         }
//         break;
//       }
//     }

//     (*this->window_ptr).clear();

//     (*this->window_ptr).draw(sprite);
//     (*this->window_ptr).draw(game_win_text);
//     menu_button.drawButton(*this->window_ptr);
//     (*this->window_ptr).draw(prompt_text);
//     (*this->window_ptr).draw(time_text);
//     (*this->window_ptr).draw(highscores_text);

//     if (this->clock->getElapsedTime().asSeconds() < this->highscores.rbegin()->first) {
//       (*this->window_ptr).draw(new_highscore_text);
//     }

//     (*this->window_ptr).display();

//   }
//   return true;
// }