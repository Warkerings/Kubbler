//file      cChunk.cpp
//date      15-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cChunk.h>

cChunk::cChunk() {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            mData[i][j].SetType(BLOCK_GRASS);
        }
    }
}

void cChunk::Draw() {
    mData[0][0].Draw();
}
