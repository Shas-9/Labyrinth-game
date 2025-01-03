#include "Camera.h"
#include "singleton/ScreenManager.h"

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

Camera::Camera(): Camera(Vector(0, 0), Vector(0, 0), 1) {}
Camera::Camera(Vector current, Vector target, double zoom) : target_camera_pos(target), current_camera_pos(current), custom_zoom(zoom) { this->resolution_zoom = SCREEN_Y / 1080; }

void Camera::update(bool smooth) {
  // smooth camera movement
  if (smooth) {
    Vector new_cam_pos = Vector::getMid(this->current_camera_pos, this->target_camera_pos, 50);
    this->current_camera_pos = new_cam_pos;
  }

  // instant caera movement
  else this->current_camera_pos = this->target_camera_pos;
}

void Camera::setTargetPos(Vector target) { this->target_camera_pos = target; }
double Camera::getZoom() { return this->resolution_zoom * this->custom_zoom; }
Vector Camera::getCurrentPos() { return this->current_camera_pos; }

Vector Camera::convertPos(Vector pos) {
  return Vector(pos.x * this->getZoom() - this->getCurrentPos().x * this->getZoom() + SCREEN_X/2, pos.y * this->getZoom() - this->getCurrentPos().y * this->getZoom() + SCREEN_Y/2);
}