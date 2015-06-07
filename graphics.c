/**
 * @file graphics.c
 * @description This file handles all the graphics.
 * @author David Yoon
 * @date 12/11/12
 * @version 1.0
 */

#include "graphics.h"

/**
 * @description This initializes the screen and sprites.
 * @param in The Game Data
 * @return 0 is good.
 */

char initVideo(struct Game *in)
{
        SDL_Init(SDL_INIT_EVERYTHING);//Initialize SDL
	in->vid.fullscreen = 0;//Windowed
        in->vid.screenHeight = SCREEN_HEIGHT;//Set initial height.
        in->vid.screenWidth = SCREEN_WIDTH;//Set initial width.
        in->vid.screen = SDL_SetVideoMode(SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SCREEN_BPP,
					  SDL_HWSURFACE| SDL_RESIZABLE);//Create screen
        if(!in->vid.screen)//if screen init fails.
                return 1;
	//Initialize mouse
	in->mouse.pos.x = in->mouse.pos.y = 0;
	in->mouse.pos.w = in->mouse.pos.h = 16;
	//Initialize Buttons
	in->play[0].pos.x = in->play[1].pos.x = 0;
	in->play[0].pos.y = in->play[1].pos.y = in->vid.screenHeight-32;
	in->play[0].pos.h = in->play[1].pos.h = 
		in->play[0].pos.w = in->play[1].pos.w = 32;
		
	in->modes[0].pos.x = in->modes[1].pos.x = 64;
	in->modes[0].pos.y = in->modes[1].pos.y = in->vid.screenHeight-32;
	in->modes[0].pos.h = in->modes[1].pos.h = 
	in->modes[0].pos.w = in->modes[1].pos.w = 32;
		
	if(!(in->play[1].sprite = IMG_Load("play.png")))
		return 1;
	if(!(in->play[0].sprite = IMG_Load("pause.png")))
		return 1;
	if(!(in->modes[1].sprite = IMG_Load("torus.png")))
		return 1;
	if(!(in->modes[0].sprite = IMG_Load("hedge.png")))
		return 1;
	if(!(in->mouse.sprite = IMG_Load("cursor.png")))
		return 1;
	//Do not render the white in the mouse sprite.
	SDL_SetColorKey(in->mouse.sprite, SDL_SRCCOLORKEY, SDL_MapRGB(in->mouse.sprite->format,0xFF,0xFF,0xFF));
	//Set the FPS to 120.
	in->vid.fps = 120;
        return 0;
}
/**
 * @description This draws the whole program
 * @param in The Game Data
 * @return void
 */
void render(struct Game *in)
{
	SDL_FillRect(in->vid.screen,NULL,SDL_MapRGB(in->vid.screen->format,0,0,0));
        int j, k;
        for(j = 0; j < in->field.height; j++){
                for(k = 0; k < in->field.width; k++) {
                        SDL_FillRect(in->vid.screen,
                                     &in->field.Colony[in->frame][j][k].box,
                                     SDL_MapRGB(in->vid.screen->format,
                                                0xFF*in->field.Colony[in->frame][j][k].alive,
                                                0xFF*in->field.Colony[in->frame][j][k].alive,
                                                0xFF*in->field.Colony[in->frame][j][k].alive));
                }
	}
	
	SDL_BlitSurface(in->play[in->paused].sprite,
			NULL,
		 in->vid.screen,
		 &in->play[0].pos);
	SDL_BlitSurface(in->modes[in->mode].sprite,
			NULL,
		 in->vid.screen,
		 &in->modes[0].pos);
	
	SDL_BlitSurface(in->mouse.sprite,
			NULL,
		 in->vid.screen,
		 &in->mouse.pos);
	if(!in->paused && ! in->step)
		in->frame = !in->frame;
	SDL_Flip(in->vid.screen);
	if((SDL_GetTicks()-in->vid.time)<1000/in->vid.fps)
		SDL_Delay((1000/in->vid.fps)-(SDL_GetTicks()-in->vid.time));
}
