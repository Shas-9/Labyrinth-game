#ifndef CAMERA_INCLUDE
#define CAMERA_INCLUDE

#include "Vector.h"

class Camera {
  Vector current_camera_pos;
  Vector target_camera_pos;
  double target_custom_zoom;
  double current_custom_zoom;
  double resolution_zoom;
public:
  Camera();
  Camera(Vector current, Vector target, double zoom);
  void setTargetPos(Vector target);
  void updatePos(bool smooth);
  void updateZoom(bool smooth);
  double getZoom();
  void multZoom(double zoom);
  Vector getCurrentPos();
  
  Vector convertPos(Vector pos);
};

#endif