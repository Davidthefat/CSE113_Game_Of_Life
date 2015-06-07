/**
 * @file graphics.h
 * @description This file handles all the rendering.
 * @author David Yoon
 * @date 
 * @version 1.0
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "const.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_timer.h"

char initVideo(struct Game *in);
void render(struct Game *in);

#endif