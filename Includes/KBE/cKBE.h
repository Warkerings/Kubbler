//file      cEngine.h
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#ifndef INC_C_ENGINE_H
#define INC_C_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <KBE/logger.h>
#include <KBE/cShader.h>
#include <KBE/cTexture.h>
#include <stb/stb_image.h>

class KBE{
public:
    KBE();
    ~KBE();
    int Init(int Width, int Height, bool FullScreen);
    int Run();
    void Release();
private:
    GLFWwindow *mWindow;
    int mWinWidth, mWinHeight;
    bool mFullScreen;
    cShader mShaders;
    cTexture mTextures;
};

#endif//INC_C_ENGINE_H
