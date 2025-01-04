#include "Camera.h"
#include "singleton/ScreenManager.h"

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

Camera::Camera(): Camera(Vector(0, 0), Vector(0, 0), 1) {}
Camera::Camera(Vector current, Vector target, double zoom) : target_camera_pos(target), current_camera_pos(current), target_custom_zoom(zoom), current_custom_zoom(zoom) { this->resolution_zoom = SCREEN_Y / 1080; }

void Camera::updatePos(bool smooth) {
  // smooth camera movement
  if (smooth) {
    Vector new_cam_pos = Vector::getMid(this->current_camera_pos, this->target_camera_pos, 10);
    this->current_camera_pos = new_cam_pos;
  }

  // instant caera movement
  else this->current_camera_pos = this->target_camera_pos;
}

void Camera::updateZoom(bool smooth) {
  // smooth camera movement
  if (smooth) {
    this->current_custom_zoom -= (this->current_custom_zoom - this->target_custom_zoom)/10;
  }

  // instant caera movement
  else this->current_custom_zoom = this->target_custom_zoom;
}

void Camera::setTargetPos(Vector target) { this->target_camera_pos = target; }
Vector Camera::getCurrentPos() { return this->current_camera_pos; }

double Camera::getZoom() { return this->resolution_zoom * this->current_custom_zoom; }
void Camera::multZoom(double zoom) { this->target_custom_zoom *= zoom; }

Vector Camera::convertPos(Vector pos) {
  return Vector(pos.x * this->getZoom() - this->getCurrentPos().x * this->getZoom() + SCREEN_X/2, pos.y * this->getZoom() - this->getCurrentPos().y * this->getZoom() + SCREEN_Y/2);
}