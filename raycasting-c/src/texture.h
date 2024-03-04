#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "defs.h"
#include "upng.h"

typedef struct {
    upng_t* upngTexture;
    int width;
    int height;
    uint32_t* texture_buffer;
} texture_t;

texture_t getWallTexture(int textureIndex);

void loadWallTextures();
void freeWallTextures();

#endif
