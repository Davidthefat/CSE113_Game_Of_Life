/**
 * @file const.h
 * @description This file holds all the data used in the program
 * @author David Yoon
 * @date 12/11/12
 * @version 1.0
 */

#ifndef CONST_H
#define CONST_H

#define MAXHEIGHT 256
#define MAXWIDTH 256
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define SCREEN_BPP 32
#define TORUS 1
#define HEDGE 0
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

struct Game{
	struct Video{
		int screenHeight;
		int screenWidth;
		int fps;
		int time;
		char fullscreen;
		SDL_Surface *screen;
	}vid;
	struct Life{
		struct LifeForm{
			char alive;
			SDL_Rect box;
		}Colony[2][MAXHEIGHT][MAXWIDTH];
		unsigned char height;
		unsigned char width;
	}field;
	struct Button{
		SDL_Rect pos;
		SDL_Surface *sprite;
	}play[2],modes[2];
	SDL_Event event;
	struct Mouse{
		SDL_Rect pos;
		SDL_Surface *sprite;
	}mouse;
	char resize;
	char mode;
	char running;
	char paused;
	char step;
	char frame;
};

#endif