#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

// where to position camera based on world
enum CameraMode {
    FRONT=1,
    SIDE =2,
    ORTHO = 3
};

class Camera {
private:
    vec3 eye;
    vec3 position;
    vec3 up;
    vec3 cameraPos;
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 projectionViewMatrix;
    CameraMode currentMode;

    mat4 getCamera(CameraMode mode);
    mat4 getProjection(CameraMode mode);
    vec3 getTransform(CameraMode mode);

public:
    Camera();
    mat4 getViewMatrix() { return viewMatrix; }
    mat4 getProjectionMatrix() { return projectionMatrix; }
    mat4 getProjectionViewMatrix();
    vec3 getPosition();
    void changeView(CameraMode mode, float time);
    void setCameraMode(CameraMode mode);
};