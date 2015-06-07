/**
 * @file logic.c
 * @description This file handles all the logic of the game.
 * @author David Yoon
 * @date 12/11/12
 * @version 1.0
 */
#include "logic.h"
/**
 * @description This initializes the cells and game modes.
 * @param in The Game Data
 * @return void
 */
void initGame(struct Game *in)
{
	int j, k;
	float h, w;
	in->mode = TORUS;
	in->resize = 0;
	in->running = 1;
	in->paused = 1;
	in->step = 0;
	in->frame = 0;
	
	in->field.height = MAXHEIGHT/2;
	in->field.width = MAXWIDTH/2;
	
	if(in->field.height <= 0 || in->field.width <= 0)
		return (void)printf("ERROR! Invalid screen resolution!");
	h = (float)(in->vid.screenHeight-32) / in->field.height;
	w = (float)in->vid.screenWidth / in->field.width;
	
	for(j = 0; j < MAXHEIGHT; j++)
		for(k = 0; k < MAXWIDTH; k++){
			in->field.Colony[0][j][k].box.x = w*k;
			in->field.Colony[0][j][k].box.y = h*j;
			in->field.Colony[0][j][k].box.h = h;
			in->field.Colony[0][j][k].box.w = w;
			//in->field.Colony[0][j][k].alive = (j%2)^(k%2);
			in->field.Colony[0][j][k].alive = 0;
			
			in->field.Colony[1][j][k].box.x = w*k;
			in->field.Colony[1][j][k].box.y = h*j;
			in->field.Colony[1][j][k].box.h = h;
			in->field.Colony[1][j][k].box.w = w;
			//in->field.Colony[1][j][k].alive = !(j%2)^(k%2);
			in->field.Colony[1][j][k].alive = 0;
		}
}

/**
 * @description This resizes the playing field
 * @param in The Game Data
 * @return void
 */
void resize(struct Game *in)
{
	int j, k;
	float h = (float)(in->vid.screenHeight-32) / in->field.height;
	float w = (float)in->vid.screenWidth / in->field.width;
	for(j = 0; j < in->field.height; j++)
		for(k = 0; k < in->field.width; k++){
			in->field.Colony[0][j][k].box.x = w*k;
			in->field.Colony[0][j][k].box.y = h*j;
			in->field.Colony[0][j][k].box.h = h;
			in->field.Colony[0][j][k].box.w = w;
			
			in->field.Colony[1][j][k].box.x = w*k;
			in->field.Colony[1][j][k].box.y = h*j;
			in->field.Colony[1][j][k].box.h = h;
			in->field.Colony[1][j][k].box.w = w;
		}
		
		in->play[0].pos.x = in->play[1].pos.x = 0;
		in->play[0].pos.y = in->play[1].pos.y = in->vid.screenHeight-32;
		in->play[0].pos.h = in->play[1].pos.h = 
		in->play[0].pos.w = in->play[1].pos.w = 32;
		
		in->modes[0].pos.x = in->modes[1].pos.x = 64;
		in->modes[0].pos.y = in->modes[1].pos.y = in->vid.screenHeight-32;
		in->modes[0].pos.h = in->modes[1].pos.h = 
		in->modes[0].pos.w = in->modes[1].pos.w = 32;
}
/**
 * @description This handles logic
 * @param in The Game Data
 * @return void
 */
void logic(struct Game *in)
{
	if(in->resize){
		resize(in);
		in->resize = 0;
	}
	if(!in->paused){
		int num = 0;
		int j, k;
		int h = in->field.height;
		int w =in->field.width;
		for(j = 0; j < h; j++){
			for(k = 0; k < w; k++) {
				if(in->mode == TORUS){
					num+=in->field.Colony[in->frame][j+1>h-1?0:j+1][k].alive;
					num+=in->field.Colony[in->frame][j-1<0?h-1:j-1][k].alive;
					num+=in->field.Colony[in->frame][j][k+1>w-1?0:k+1].alive;
					num+=in->field.Colony[in->frame][j][k-1<0?w-1:k-1].alive;
					num+=in->field.Colony[in->frame][j+1>h-1?0:j+1][k+1>w-1?0:k+1].alive;
					num+=in->field.Colony[in->frame][j+1>h-1?0:j+1][k-1<0?w-1:k-1].alive;
					num+=in->field.Colony[in->frame][j-1<0?h-1:j-1][k+1>w-1?0:k+1].alive;
					num+=in->field.Colony[in->frame][j-1<0?h-1:j-1][k-1<0?w-1:k-1].alive;
				}
				else if(in->mode == HEDGE){
					num+=((j+1)>(h-1))?0:in->field.Colony[in->frame][j+1][k].alive;
					num+=((j-1)<0)?0:in->field.Colony[in->frame][j-1][k].alive;
					num+=((k+1)>(w-1))?0:in->field.Colony[in->frame][j][k+1].alive;
					num+=((k-1)<0)?0:in->field.Colony[in->frame][j][k-1].alive;
					num+=((j+1>h-1)||(k+1>w-1))?0:in->field.Colony[in->frame][j+1][k+1].alive;
					num+=((j-1<0)||(k+1>w-1))?0:in->field.Colony[in->frame][j-1][k+1].alive;
					num+=((j+1>h-1)||(k-1<0))?0:in->field.Colony[in->frame][j+1][k-1].alive;
					num+=((j-1<0)||(k-1<0))?0:in->field.Colony[in->frame][j-1][k-1].alive;
				}
				if(in->field.Colony[in->frame][j][k].alive)
					if(num>3||num<2)
						in->field.Colony[!in->frame][j][k].alive=0;
					else
						in->field.Colony[!in->frame][j][k].alive=1;
				else if(!in->field.Colony[in->frame][j][k].alive)
					if(num == 3)
						in->field.Colony[!in->frame][j][k].alive=1;
				else
					in->field.Colony[!in->frame][j][k].alive=0;
				num = 0;
			}
		}
	}
}