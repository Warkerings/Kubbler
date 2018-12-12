//file      logger.cpp
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/logger.h>

void LogInfo(const char *Text){
    std::cout << "[INFO] " << Text << std::endl;
}

void LogError(const char *Text){
    std::cout << "[ERROR] " << Text << std::endl;
}

void LogError(const char *Text, const char *Error){
    std::cout << "[ERROR] " << Text << " : " << Error << std::endl;
}
