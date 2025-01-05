#include "AnimController.h"

AnimController::AnimController() {}

void AnimController::updateFrame(int animation_speed, std::string mode) {
  if (mode == "repeat") {
    this->current_frame_progress += animation_speed;
    if (this->current_frame_progress >= this->frames_numbers[this->current_row] * 1000) this->current_frame_progress = 0;
  }

  if (mode == "once") {
    this->current_frame_progress += animation_speed;
    if (this->current_frame_progress >= this->frames_numbers[this->current_row] * 1000) this->current_frame_progress = this->frames_numbers[this->current_row] * 1000;
  }
  
  Vector frame_dim = this->frames_dimensions[this->current_row];
  
  int x_offset = frame_dim.x * (this->current_frame_progress / 1000);
  int y_offset = 0;
  for (int i = 0; i < this->current_row; i++) y_offset += this->frames_dimensions[i].y;

  // this->rectSourceSprite->setSize(x_offset, y_offset, frame_dim.x, frame_dim.y);
  this->texture_rect = sf::IntRect(x_offset, y_offset, frame_dim.x, frame_dim.y);
}

void AnimController::setActivity(std::string activity) {
  this->current_row = this->activities_map[activity];
  this->current_frame_progress = 0;
}

void AnimController::addRow(Vector frames_dimension, int frames_number, std::string activity_name) {
  this->frames_numbers.push_back(frames_number);
  this->frames_dimensions.push_back(frames_dimension);
  this->activities_map[activity_name] += this->frames_numbers.size() - 1;
}

sf::IntRect AnimController::getTextureRect() {
  return this->texture_rect;
}