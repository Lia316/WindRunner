#include "Camera.h"

Camera::Camera() {
    eye = vec3(0, 0, 400);
    position = vec3(0.0f, 0.0f, 0.0f);
    up = vec3(0.0f, 1.0f, 0.0f);
    cameraPos = vec3(0.0f);

    currentMode = SIDE;
    projectionViewMatrix = mat4(1.0f);
    changeView(SIDE, 1);
}

mat4 Camera::getProjectionViewMatrix() {
    return projectionViewMatrix;
}

vec3 Camera::getPosition() {
    return eye;
}

void Camera::setCameraMode(CameraMode mode) {
    currentMode = mode;
}

mat4 Camera::getCamera(CameraMode mode) {
    const vec3 frontEye = vec3(-500, 150, 0);
    const vec3 sideEye = vec3(0, 0, 400);
    const vec3 orthoEye = vec3(0, 0, 200);

    const vec3 frontPos = vec3(0, 100, 0);

    switch (mode) {
    case FRONT:
        eye = frontEye; 
        return  lookAt(frontEye, frontPos, up);
    case SIDE:
        eye = sideEye;
        return  lookAt(sideEye, position, up);
    case ORTHO:
        eye = orthoEye;
        return  lookAt(orthoEye, position, up);
    default:
        eye = sideEye;
        return  lookAt(sideEye, position, up);
    }
}

mat4 Camera::getProjection(CameraMode mode) {
    switch (mode) {
    case FRONT:
        return perspective(45.0, 2.0, 1.0, 2000.0);
    case SIDE:
        return perspective(45.0, 2.0, 1.0, 600.0);
    case ORTHO:
        return ortho(-500.0f, 500.0f, -300.0f, 200.0f, -200.0f, 500.0f);
    default:
        return perspective(45.0, 2.0, 1.0, 600.0);
    }
}

vec3 Camera::getTransform(CameraMode mode) {
    switch (mode) {
    case FRONT:
        return vec3(-200, -100, 0);
    case SIDE:
        return vec3(-200, -200, 0);
    case ORTHO:
        return vec3(-200, -250, 0);
    default:
        return vec3(-200, -200, 0);
    }
}

// rotate mode 1 <-> 2 by keyframe interpolation
void Camera::changeView(CameraMode mode, float time) {
    if (time > 1 || time <= 0) return;
       
    mat4 view = getCamera(currentMode) + time * (getCamera(mode) - getCamera(currentMode));
    mat4 transform = time * translate(mat4(1.0f), getTransform(mode));
    mat4 projection = getProjection(currentMode) + time * (getProjection(mode) - getProjection(currentMode));
    
    cameraPos = eye - getTransform(mode);
    projectionViewMatrix = projection * transform * view;
}