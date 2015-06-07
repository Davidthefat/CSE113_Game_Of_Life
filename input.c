/**
 * @file input.c
 * @description This file handles all the human input.
 * @author David Yoon
 * @date 12/11/12
 * @version 1.0
 */
#include "input.h"
/**
 * @description This checks collisions
 * @param x x coordinate
 * @param y y coordinate
 * @param test rectangle to test
 * @return 1 is collision; 0 none.
 */
char checkCollision(int x, int y, SDL_Rect *test)
{
	return x<(test->x+test->w)&&y<(test->y+test->h)
		&&x>test->x&&y>test->y;
}
/**
 * @description This handles, window, mouse and keyboard input
 * @param in The Game Data
 * @return void
 */
void handleInput(struct Game *in)
{
	int clickX;
	int clickY;
	if(SDL_PollEvent(&in->event)){
		if(in->event.type == SDL_VIDEORESIZE){
			in->vid.screen = SDL_SetVideoMode(in->event.resize.w,
							  in->event.resize.h,
				     SCREEN_BPP,
				     SDL_HWSURFACE| SDL_RESIZABLE);
			in->vid.screenHeight = in->event.resize.h;
			in->vid.screenWidth = in->event.resize.w;
			resize(in);
		}
		if(in->event.type == SDL_KEYDOWN)
			switch(in->event.key.keysym.sym){
				case SDLK_ESCAPE:
					in->running = 0;
					break;
				case SDLK_SPACE:
					in->paused = !in->paused;
					printf(in->paused?"PAUSE\n":"PLAY\n");
					break;
				case SDLK_TAB:
					in->mode = !in->mode;
					printf(in->mode==TORUS?"Torus\n":"Hedge\n");
					break;
				case SDLK_BACKSPACE:
					reset(in);
					break;
				case SDLK_F11:
					if(in->vid.fullscreen){
						in->vid.screen = SDL_SetVideoMode(in->vid.screenWidth,
										  in->vid.screenHeight,
										SCREEN_BPP,
								SDL_HWSURFACE| SDL_RESIZABLE);
						in->vid.fullscreen = 0;
					}
					else{
						in->vid.screen = SDL_SetVideoMode(in->vid.screenWidth,
										  in->vid.screenHeight,
										SCREEN_BPP,
						SDL_HWSURFACE | SDL_FULLSCREEN| SDL_RESIZABLE);
						in->vid.fullscreen = 1;
					}
					break;
				case SDLK_PAGEDOWN:
					if(in->field.height>1&&in->field.width>1){
						in->field.height--;
						in->field.width--;
						printf("Resolution:\t%dx%d\n", in->field.width,in->field.height);
						in->resize = 1;
					}
					break;
				case SDLK_PAGEUP:
					if(in->field.height<MAXHEIGHT&&in->field.width<MAXWIDTH){
						in->field.height++;
						in->field.width++;
						printf("Resolution:\t%dx%d\n", in->field.width,in->field.height);
						in->resize = 1;
					}
					break;
				case SDLK_s:
					in->step = !in->step;
					printf(in->step?"Stepping Mode\n":"Continuous Mode\n");
					break;
				case SDLK_n:
					if(!in->paused && in->step){
						in->frame = !in->frame;
						printf("Step\n");
					}
					break;
				default:
					break;
			}
		if(in->event.type == SDL_QUIT)
			in->running = 0;
		if(in->event.type == SDL_MOUSEMOTION){
			in->mouse.pos.x = in->event.motion.x;
			in->mouse.pos.y = in->event.motion.y;
			//printf("Mouse:\t%d,%d\n", in->mouse.pos.x, in->mouse.pos.y);
		}
		if(in->event.type == SDL_MOUSEBUTTONDOWN){
			if(in->event.button.button == SDL_BUTTON_LEFT){
				clickX = in->event.button.x;
				clickY = in->event.button.y;
				int j, k;
				//printf("Cursor:\t%d,%d\n", clickX, clickY);
				if(clickY<(in->vid.screenHeight-32)){
					j = (float)clickY*in->field.height/(in->vid.screenHeight-32);
					k = (float)clickX*in->field.width/in->vid.screenWidth;
					printf("Cursor:\t%d,%d\n", k, j);
					in->field.Colony[0][j][k].alive = !in->field.Colony[0][j][k].alive;
					in->field.Colony[1][j][k].alive = !in->field.Colony[1][j][k].alive;
				}
				else{
					if(checkCollision(clickX, clickY,&in->play[0].pos)){
						in->paused=!in->paused;
						printf(in->paused?"PAUSE\n":"PLAY\n");
					}
					if(checkCollision(clickX, clickY,&in->modes[0].pos)){
						in->mode=!in->mode;
						printf(in->mode==TORUS?"Torus\n":"Hedge\n");
					}
				}
			}
		}
	}
}
/**
 * @description This sets all cells to dead
 * @param in The Game Data
 * @return void
 */
void reset(struct Game *in)
{
	int j, k;
	for(j = 0; j < in->field.height; j++){
		for(k = 0; k < in->field.width; k++) {
			in->field.Colony[0][j][k].alive = 0;
			in->field.Colony[1][j][k].alive = 0;
		}
	}
}