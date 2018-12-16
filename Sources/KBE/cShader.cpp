//file      cShader.cpp
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cShader.h>

void cShader::Use() {
    glUseProgram(mID);
}

int cShader::Load(const char *VertexFile, const char *FragmentFile) {
    std::ifstream VertexStream, FragmentStream;
    std::string VertexSource, FragmentSource;
    std::stringstream VertexBuffer, FragmentBuffer;
    
    LogInfo("Loading shaders...");
    VertexStream.open(VertexFile);
    if(VertexStream.is_open()){
        VertexBuffer << VertexStream.rdbuf();
        VertexStream.close();
        VertexSource = VertexBuffer.str();
    }else{
        LogError("Can't load vertex shader");
        return 1;
    }
    
    FragmentStream.open(FragmentFile);
    if(FragmentStream.is_open()){
        FragmentBuffer << FragmentStream.rdbuf();
        FragmentStream.close();
        FragmentSource = FragmentBuffer.str();
    }else{
        LogError("Can't load fragment shader");
        return 1;
    }
    
    const char *VertexCode = VertexSource.c_str();
    const char *FragmentCode = FragmentSource.c_str();
    unsigned int VertexID, FragmentID;
    int success;
    char infoLog[512];
    
    LogInfo("Compiling shaders...");
    VertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexID, 1, &VertexCode, nullptr);
    glCompileShader(VertexID);
    glGetShaderiv(VertexID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(VertexID, 512, nullptr, infoLog);
        LogError("Can't compile vertex shader", infoLog);
        glDeleteShader(VertexID);
        return 1;
    }
    
    FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentID, 1, &FragmentCode, nullptr);
    glCompileShader(FragmentID);
    glGetShaderiv(FragmentID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(FragmentID, 512, nullptr, infoLog);
        LogError("Can't compile fragment shader", infoLog);
        glDeleteShader(VertexID);
        glDeleteShader(FragmentID);
        return 1;
    }
    
    mID = glCreateProgram();
    glAttachShader(mID, VertexID);
    glAttachShader(mID, FragmentID);
    glLinkProgram(mID);
    glGetProgramiv(mID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(mID, 512, nullptr, infoLog);
        LogError("Can't link shader program", infoLog);
        glDeleteShader(VertexID);
        glDeleteShader(FragmentID);
        glDeleteProgram(mID);
        return 1;
    }
    
    glDeleteShader(VertexID);
    glDeleteShader(FragmentID);
    
    return 0;
}

void cShader::SetInt(const char *Name, int Value) {
    glUniform1i(glGetUniformLocation(mID, Name), Value);
}

void cShader::SetFloat(const char *Name, float Value) {
    glUniform1f(glGetUniformLocation(mID, Name), Value);
}

void cShader::SetMat4(const char *Name, glm::mat4 Mat) {
    glUniformMatrix4fv(glGetUniformLocation(mID, Name), 1, GL_FALSE, &Mat[0][0]);
}
