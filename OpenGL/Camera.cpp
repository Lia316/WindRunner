#include "Camera.h"

Camera::Camera(vec3 eye, vec3 position, vec3 up) {
    this->eye = eye;
    this->position = position;
    this->up = up;
    currentMode = SIDE;
}

mat4 Camera::getViewMatrix() {
    mat4 view = lookAt(eye, position, up);
    return view;
}

void Camera::setCameraMode(CameraMode mode) {
    currentMode = mode;
}

void Camera::changeEyePos(CameraMode direction, float time) {
    if (time <= 1 && time >= 0)
        eye = getEye(currentMode) + time * (getEye(direction) - getEye(currentMode));
}

vec3 Camera::getEye(CameraMode mode) {
    switch (mode)
    {
    case FRONT:
        return frontEye;
    case SIDE:
        return sideEye;
    case ORTHO:
        return orthoEye;
    default:
        return sideEye;
    }
}