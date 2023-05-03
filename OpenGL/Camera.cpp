#include "Camera.h"

Camera::Camera(vec3 eye, vec3 position, vec3 up) {
    this->eye = eye;
    this->position = position;
    this->up = up;
    currentMode = SIDE;
    projection = perspective(60.0, 2.0, 1.0, 200.0);
}

mat4 Camera::getViewMatrix() {
    mat4 view = lookAt(eye, position, up);
    return view;
}

mat4 Camera::getProjectionMatrix() {
    return projection; // translate(mat4(1.0f), vec3(20, -50, 0))
}

void Camera::setCameraMode(CameraMode mode) {
    currentMode = mode;
}

void Camera::changeEyePos(CameraMode direction, float time) {
    if (time <= 1 && time >= 0)
        eye = getEye(currentMode) + time * (getEye(direction) - getEye(currentMode));
}

vec3 Camera::getEye(CameraMode mode) {
    const vec3 frontEye = vec3(800, -150, 0);
    const vec3 sideEye = vec3(0, 0, 500);
    const vec3 orthoEye = vec3(0, 0, 500);

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

void Camera::changeProjection(CameraMode mode, float time) {
    if (time <= 1 && time >= 0)
        projection = getProjection(currentMode) + time * (getProjection(mode) - getProjection(currentMode));
}

mat4 Camera::getProjection(CameraMode mode) {
    //mat4 camMove = translate(mat4(1.0f), vec3(20, -50, 0));
    switch (mode)
    {
    case FRONT:
        return perspective(60.0, 2.0, 1.0, 1000.0);
    case SIDE:
        return perspective(60.0, 2.0, 1.0, 700.0);
    case ORTHO:
        return ortho(0.0, 1000.0, 0.0, 500.0, -200.0, 1000.0);
    default:
        return perspective(60.0, 2.0, 1.0, 700.0);
    }
}