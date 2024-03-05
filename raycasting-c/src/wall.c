#include "wall.h"

void changeColorIntensity(color_t* color, float factor) {
    color_t a = (*color & 0xFF000000);
    color_t r = (*color & 0x00FF0000) * factor;
    color_t g = (*color & 0x0000FF00) * factor;
    color_t b = (*color & 0x000000FF) * factor;

    *color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void renderWallProjection() {
    for (int x = 0; x < NUM_RAYS; x++) {
        float perpDistance = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);
        float wallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        int wallTopY = (WINDOW_HEIGHT / 2) - (wallHeight / 2);
        wallTopY = wallTopY < 0 ? 0 : wallTopY;

        int wallBottomY = (WINDOW_HEIGHT / 2) + (wallHeight / 2);
        wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;

        // draw the ceiling
        for (int y = 0; y < wallTopY; y++)
            drawPixel(x, y, 0xFF444444);

        int textureOffsetX;
        if (rays[x].wasHitVertical)
            textureOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
        else
            textureOffsetX = (int)rays[x].wallHitX % TILE_SIZE;

        // get the correct texture id number from the map content
        int texNum = rays[x].texture - 1;

        int textureWidth =  upng_get_width(getTexture(texNum));
        int textureHeight = upng_get_height(getTexture(texNum));

        // render the wall from wallTopPixel to wallBottomPixel
        for (int y = wallTopY; y < wallBottomY; y++) {
            int distanceFromTop = y + (wallHeight / 2) - (WINDOW_HEIGHT / 2);
            int textureOffsetY = distanceFromTop * ((float)textureHeight / wallHeight);

            // set the color of the wall based on the color from the texture
            color_t* wallTextureBuffer = (color_t*) upng_get_buffer(getTexture(texNum));
            color_t texelColor = wallTextureBuffer[(textureWidth * textureOffsetY) + textureOffsetX];
            if (rays[x].wasHitVertical) { 
                changeColorIntensity(&texelColor, 0.75);
            }
            drawPixel(x, y, texelColor);
        }

        // draw the floor
        for (int y = wallBottomY; y < WINDOW_HEIGHT; y++)
            drawPixel(x, y, 0xFF888888);
    }
}
