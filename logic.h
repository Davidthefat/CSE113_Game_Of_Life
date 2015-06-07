/**
 * @file logic.h
 * @description This file handles all the logic of the game.
 * @author David Yoon
 * @date 
 * @version 1.0
 */
#ifndef LOGIC_H
#define LOGIC_H

#include "const.h"
#include "SDL/SDL.h"

void initGame(struct Game *in);
void logic(struct Game *in);
#endif