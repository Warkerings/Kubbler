//file      cBlock.cpp
//date      12-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cBlock.h>

cBlock::cBlock() {
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void cBlock::Draw() {
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cBlock::SetType(BLOCK_TYPE Type) {
    mType = Type;
}
