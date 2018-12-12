//file      cTexture.cpp
//date      10-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cTexture.h>

cTexture::cTexture() {
    mID = 0;
    mWidth = 0;
    mHeight = 0;
    mChannels = 0;
}

cTexture::~cTexture() {
    if(mID >= 1)
        glDeleteTextures(1, &mID);
}

void cTexture::Use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mID);
}

int cTexture::Load(const char *FileName) {
    LogInfo("Loading texture...");
    
    glGenTextures(1, &mID);
    glBindTexture(GL_TEXTURE_2D, mID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    unsigned char *data = stbi_load(FileName, &mWidth, &mHeight, &mChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        LogError("Can't load texture", FileName);
    }
    stbi_image_free(data);
}
