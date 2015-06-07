/**
 * @file input.h
 * @description This file handles human input.
 * @author David Yoon
 * @date 
 * @version 1.0
 */
#ifndef INPUT_H
#define INPUT_H

#include "const.h"
#include "SDL/SDL_events.h"
#include "SDL/SDL_keyboard.h"
#include "SDL/SDL_mouse.h"

char checkCollision(int x, int y, SDL_Rect *test);
void handleInput(struct Game *in);
void reset(struct Game *in);

#endif