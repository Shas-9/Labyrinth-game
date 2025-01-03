#ifndef CAMERA_INCLUDE
#define CAMERA_INCLUDE

#include "Vector.h"

class Camera {
  Vector current_camera_pos;
  Vector target_camera_pos;
  double custom_zoom;
  double resolution_zoom;
public:
  Camera();
  Camera(Vector current, Vector target, double zoom);
  void setTargetPos(Vector target);
  void update(bool smooth);
  double getZoom();
  Vector getCurrentPos();
  
  Vector convertPos(Vector pos);
};

#endif