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
    mat4 projection;

    CameraMode currentMode;

    vec3 getEye(CameraMode mode);
    mat4 getProjection(CameraMode mode);

public:
    Camera(vec3 eye = vec3(0, 0, 500), vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f));
    mat4 getViewMatrix();
    mat4 getProjectionMatrix();
    void changeEyePos(CameraMode direction, float time);
    void changeProjection(CameraMode mode, float time);
    void setCameraMode(CameraMode mode);
};