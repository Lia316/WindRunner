#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

// where to position camera based on world
enum CameraMode {
    FRONT,
    SIDE,
    ORTHO
};

class Camera {
private:
    vec3 eye;
    vec3 position;
    vec3 up;

    const vec3 frontEye = vec3(-300, 150, 0);
    const vec3 sideEye = vec3(0, 0, 500);
    const vec3 orthoEye = vec3(0, 0, 5);
    CameraMode currentMode;

    vec3 getEye(CameraMode mode);

public:
    Camera(vec3 eye = vec3(0, 0, 500), vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f));
    mat4 getViewMatrix();
    void changeEyePos(CameraMode direction, float time);
    void setCameraMode(CameraMode mode);
};