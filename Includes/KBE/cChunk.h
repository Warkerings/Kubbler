//file      cChunk.h
//date      15-12-2018
//project   Kubbler
//author    Warkerings

#ifndef INC_C_CHUNK_H
#define INC_C_CHUNK_H

#include <KBE/cBlock.h>

class cChunk {
public:
    cChunk();
    void Draw();
private:
    cBlock mData[16][16];
};

#endif//INC_C_CHUNK_H
