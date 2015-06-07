/**
 * @file main.c
 * @description This file handles the flow of the game; this calls all the other functions.
 * @author David Yoon
 * @date 12/11/12
 * @version 1.0
 */

#include "const.h"
#include "graphics.h"
#include "input.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @description Main loop of the program.
 * @param argc number of command line arguments.
 * @param argv arguments.
 */

int main(int argc, char **argv)
{
	int c;
	struct Game game;
	if(initVideo(&game)) //if video fails to initialize.
		return -1;
	initGame(&game); //intitialize game parameters.
	SDL_ShowCursor(0); //do not show system cursor.
	while ((c = getopt (argc, argv, "w:h:a:s:g:H")) != -1)
		switch (c)
		{
			case 'w':
				game.vid.screenWidth = atoi(optarg);
				if(game.vid.screenWidth<game.field.width)
					game.vid.screenWidth = game.field.width;
				break;
			case 'h':
				game.vid.screenHeight = atoi(optarg);
				if(game.vid.screenHeight<game.field.height)
					game.vid.screenHeight = game.field.height;
				break;
			case 'a':
				game.field.height = atoi(optarg);
				break;
			case 's':
				game.field.width = atoi(optarg);
				break;
			case 'g':
				printf("%s\n", optarg);
				if(optarg == "TORUS")
					game.mode = TORUS;
				else if(optarg == "HEDGE")
					game.mode = HEDGE;
				else
					game.mode = TORUS;
				break;
			case 'H':
				printf("H: Help\nw: Screen Width\nh: Screen Height\na: Field Height\ns: Field Width\ng: HEDGE or TORUS\n");
				printf("Keys:\nSpace: Play/Pause\nS: Toggle Stepping Mode\nN: While in Stepping Mode, Step\nTab: Toggle Torus/Hedge\n");
				printf("Page Up: Increase Resolution\nPage Down: Decrease Resolution\nBackspace: Clear Screen\nF11: Toggle Fullscreen\nEsc: Exit\n");
				break;
			default:
				printf("Invalid Input\n");
				break;
		}
		resize(&game);//Resize the playing field
		game.vid.screen = SDL_SetVideoMode(game.vid.screenWidth,
						   game.vid.screenHeight,
				     SCREEN_BPP,
				     SDL_HWSURFACE| SDL_RESIZABLE);
	while(game.running)
	{
		handleInput(&game);
		game.vid.time = SDL_GetTicks(); //Used to regulate FPS.
		logic(&game); //Handle logic of the game
		render(&game); //Draw the pixels.
	}
	//Clean up SDL Surfaces.
	SDL_FreeSurface(game.play[0].sprite);
	SDL_FreeSurface(game.play[1].sprite);
	SDL_FreeSurface(game.modes[0].sprite);
	SDL_FreeSurface(game.modes[1].sprite);
	SDL_FreeSurface(game.mouse.sprite);
	SDL_FreeSurface(game.vid.screen);
	//Quit SDL
	SDL_Quit();
	return 0;
}