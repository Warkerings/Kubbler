//file      logger.h
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#ifndef INC_LOGGER_H
#define INC_LOGGER_H

#include <iostream>

void LogInfo(const char *Text);
void LogError(const char *Text);
void LogError(const char *Text, const char *Error);

#endif//INC_LOGGER_H
