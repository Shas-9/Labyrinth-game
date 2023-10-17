#include "../src/Utility.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>

// Test the loadGroundTexture method to ensure it loads the ground texture.
Test(utility_suite, test_load_ground_texture) {
  Utility utility;
  utility.loadGroundTexture();
  sf::Texture* ground_texture = utility.getGroundTexture();

  cr_assert_not_null(ground_texture, "Ground texture is not loaded.");
}

// Test the loadIronSpiderTexture method to ensure it loads the Iron Spider texture.
Test(utility_suite, test_load_iron_spider_texture) {
  Utility utility;
  utility.loadIronSpiderTexture();
  sf::Texture* iron_spider_texture = utility.getIronSpiderTexture();

  cr_assert_not_null(iron_spider_texture, "Iron Spider texture is not loaded.");
}

// Test the loadPlayerTexture method to ensure it loads the player texture.
Test(utility_suite, test_load_player_texture) {
  Utility utility;
  utility.loadPlayerTexture();
  sf::Texture* player_texture = utility.getPlayerTexture();

  cr_assert_not_null(player_texture, "Player texture is not loaded.");
}

// Test the loadObstacleTexture method to ensure it loads the obstacle texture.
Test(utility_suite, test_load_obstacle_texture) {
  Utility utility;
  utility.loadObstacleTexture();
  sf::Texture* obstacle_texture = utility.getObstacleTexture();

  cr_assert_not_null(obstacle_texture, "Obstacle texture is not loaded.");
}

// Test the loadPotionTexture method to ensure it loads the potion texture.
Test(utility_suite, test_load_potion_texture) {
  Utility utility;
  utility.loadPotionTexture();
  sf::Texture* potion_texture = utility.getPotionTexture();

  cr_assert_not_null(potion_texture, "Potion texture is not loaded.");
}

// Test the getPlayerWalkingFrames method to ensure it generates walking frames for the player.
Test(utility_suite, test_get_player_walking_frames) {
  Utility utility;
  Vector dimensions(64, 64);
  int scale = 2;
  vector<vector<sf::IntRect*>> walking_frames = utility.getPlayerWalkingFrames(dimensions, scale);

  cr_assert(walking_frames.size() == 4, "Invalid number of walking frames categories.");
  cr_assert(walking_frames[0].size() == 4, "Invalid number of left walking frames.");
  cr_assert(walking_frames[1].size() == 4, "Invalid number of right walking frames.");
  cr_assert(walking_frames[2].size() == 4, "Invalid number of back walking frames.");
  cr_assert(walking_frames[3].size() == 4, "Invalid number of front walking frames.");
}

// Test the getIronSpiderWalkingFrames method to ensure it generates walking frames for the Iron Spider.
Test(utility_suite, test_get_iron_spider_walking_frames) {
  Utility utility;
  Vector dimensions(64, 64);
  int scale = 2;
  vector<vector<sf::IntRect*>> walking_frames = utility.getIronSpiderWalkingFrames(dimensions, scale);

  cr_assert(walking_frames.size() == 4, "Invalid number of walking frames categories.");
  cr_assert(walking_frames[0].size() == 4, "Invalid number of left walking frames.");
  cr_assert(walking_frames[1].size() == 4, "Invalid number of right walking frames.");
  cr_assert(walking_frames[2].size() == 4, "Invalid number of back walking frames.");
  cr_assert(walking_frames[3].size() == 4, "Invalid number of front walking frames.");
}

// // Test the frames_handler method to ensure it updates sprite frames correctly.
// Test(utility_suite, test_frames_handler) {
//   Utility utility;
//   sf::Sprite sprite;
//   int current_frames_index = 0;
//   int current_animation_frame = 0;
//   vector<vector<sf::IntRect*>> walking_frames(4, vector<sf::IntRect*>(4));
//   bool moving_left = false;
//   bool moving_right = false;
//   bool moving_up = false;
//   bool moving_down = false;
//   int speed_factor = 1;

//   utility.frames_handler(&sprite, &current_frames_index, &current_animation_frame, walking_frames,
//                         moving_left, moving_right, moving_up, moving_down, speed_factor);

//   cr_assert(sprite.getTextureRect() == *walking_frames[0][0], "Sprite frames are not updated correctly.");
// }
