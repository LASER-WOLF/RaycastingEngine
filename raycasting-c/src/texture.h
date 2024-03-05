#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "defs.h"
#include "upng.h"

#define NUM_TEXTURES 14

upng_t* getTexture(int textureIndex);

void loadTextures();
void freeTextures();

#endif
