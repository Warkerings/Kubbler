//file      cTexture.h
//date      10-12-2018
//project   Kubbler
//author    Warkerings

#ifndef INC_C_TEXTURE_H
#define INC_C_TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <KBE/logger.h>

class cTexture {
public:
    cTexture();
    ~cTexture();
    int Load(const char *FileName);
    void Use();
private:
    unsigned int mID;
    int mWidth, mHeight, mChannels;
};

#endif//INC_C_TEXTURE_H
