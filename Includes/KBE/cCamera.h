//
// Created by User on 2018-12-15.
//

#ifndef KUBBLER_CCAMERA_H
#define KUBBLER_CCAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CAMERA_DIRECTION {
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_LEFT,
    CAM_RIGHT
};

class cCamera {
public:
    cCamera();
    void Move(CAMERA_DIRECTION Direction, float Delta);
    void Look(float offsetX, float offsetY);
    glm::mat4 GetViewMatrix();
private:
    glm::vec3 mPosition, mFront, mUp, mRight, mWorldUp;
    float mSpeed, mYaw, mPitch;
};

#endif //KUBBLER_CCAMERA_H
