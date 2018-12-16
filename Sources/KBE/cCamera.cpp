//file      cCamera.cpp
//date      15-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cCamera.h>


cCamera::cCamera() {
    mYaw = -90.0f;
    mPitch = 0.0f;
    mWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mPosition   = glm::vec3(1.0f, 1.0f, 5.0f);
    glm::vec3 frontBuffer;
    frontBuffer.x = cosf(glm::radians(mYaw)) * cosf(glm::radians(mPitch));
    frontBuffer.y = sinf(glm::radians(mPitch));
    frontBuffer.z = sinf(glm::radians(mYaw)) * cosf(glm::radians(mPitch));
    mFront = glm::normalize(frontBuffer);
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

void cCamera::Move(CAMERA_DIRECTION Direction, float Delta) {
    mSpeed = 1.0f * Delta;
    switch (Direction){
        case CAM_FORWARD:
            mPosition += mFront * mSpeed;
        case CAM_BACKWARD:
            mPosition -= mFront * mSpeed;
        case CAM_RIGHT:
            mPosition += mRight * mSpeed;
        case CAM_LEFT:
            mPosition -= mRight * mSpeed;
    }
    mPosition.y = 0.0f;
}

void cCamera::Look(float offsetX, float offsetY) {
    mYaw += glm::mod(offsetX + offsetX, 360.0f);
    mPitch += offsetY;
    
    if(mPitch > 89.0f)
        mPitch = 89.0f;
    if(mPitch < -89.0f)
        mPitch = -89.0f;
    
    glm::vec3 frontBuffer;
    frontBuffer.x = cosf(glm::radians(mYaw)) * cosf(glm::radians(mPitch));
    frontBuffer.y = sinf(glm::radians(mPitch));
    frontBuffer.z = sinf(glm::radians(mYaw)) * cosf(glm::radians(mPitch));
    mFront = glm::normalize(frontBuffer);
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

glm::mat4 cCamera::GetViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}
