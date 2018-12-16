//file      cEngine.h
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#ifndef INC_C_ENGINE_H
#define INC_C_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <KBE/logger.h>
#include <KBE/cCamera.h>
#include <KBE/cShader.h>
#include <KBE/cTexture.h>
#include <KBE/cChunk.h>
#include <KBE/cBlock.h>
#include <stb/stb_image.h>

class KBE{
public:
    KBE();
    ~KBE();
    int Init(int Width, int Height, bool FullScreen);
    int Run();
    void Release();
    void ProcessInput();
    void ProcessCursor(double cursorX, double cursorY);
    void ProcessResize(int width, int height);
private:
    GLFWwindow *mWindow;
    int mWinWidth, mWinHeight;
    bool mFullScreen;
    float mDeltaTime, mLastFrame, mCurrentTime;
    float mLastX, mLastY;
    float mOffsetX, mOffsetY;
    bool mFirstLoop;
    cCamera mCamera;
    cShader mShaders;
    cTexture mTextures;
    cChunk *mChunk;
    //Redirections of callbacks
    static void CallBackWindowSize(GLFWwindow *window, int width, int height){
        KBE *me = (KBE*)glfwGetWindowUserPointer(window);
        me->ProcessResize(width, height);
    }
    static void CallBackCursor(GLFWwindow *window, double cursorX, double cursorY){
        KBE *me = (KBE*)glfwGetWindowUserPointer(window);
        me->ProcessCursor(cursorX, cursorY);
    };
};

#endif//INC_C_ENGINE_H
