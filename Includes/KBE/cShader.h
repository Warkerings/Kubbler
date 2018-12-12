//file      cShader.h
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#ifndef INC_C_SHADER_H
#define INC_C_SHADER_H

#include <string>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <KBE/logger.h>

class cShader{
public:
    int Load(const char *VertexFile, const char *FragmentFile);
    void Use();
    void SetInt(const char *Name, int Value);
    void SetFloat(const char *Name, float Value);
private:
    unsigned int mID;
};

#endif//INC_C_SHADER_H
