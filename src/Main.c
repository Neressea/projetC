#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../header/Main.h"

int main(){

	

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE || SDL_DOUBLEBUF); // iniatializing screen
	SDL_WM_SetCaption("Jeu de la mort qui tue", NULL); // set name to this screen
	
	managing_event();

	SDL_Quit();

	return EXIT_SUCCESS;
}


void managing_event(){
	
	SDL_Surface *main_screen, *ennemy = NULL;
	SDL_Rect pennemy;
	

	main_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
	ennemy = SDL_LoadBMP("../images/sprites/ennemy.bmp");
	SDL_FillRect(main_screen, NULL, SDL_MapRGB(main_screen->format, 255, 255, 255));

	pennemy.x = main_screen->w / 2 - ennemy->w / 2;
	pennemy.y = main_screen->h / 2 - ennemy->h / 2;

	int bloque = 1;
	int key[4] = {0};

	SDL_Event event;

	SDL_EnableKeyRepeat(10, 10);

	while(bloque){
		SDL_WaitEvent(&event);
			switch(event.type){
				case SDL_QUIT:
					bloque = 0;
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym){	//openclassrooms.com/uploads/fr/ftp/mateo21/sdlkeysym.html
						case SDLK_ESCAPE:
        					break;
						case SDLK_UP:
							key[0] = 1;
						break;
						case SDLK_DOWN:
							key[1] = 1;
						break;
						case SDLK_LEFT:
							key[2] = 1;
						break;
						case SDLK_RIGHT:
							key[3] = 1;
						break;

						}
				break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym){
						case SDLK_ESCAPE:
        					break;
						case SDLK_UP:
							key[0] = 0;
						break;
						case SDLK_DOWN:
							key[1] = 0;
						break;
						case SDLK_LEFT:
							key[2] = 0;
						break;
						case SDLK_RIGHT:
							key[3] = 0;
						break;

						}
				break;
								
		}

	test_key(key, &pennemy);

	
	SDL_FillRect(main_screen, NULL, SDL_MapRGB(main_screen->format, 255, 255, 255));
	SDL_BlitSurface(ennemy,NULL, main_screen,&pennemy);
	SDL_Flip(main_screen);

	}


}

void test_key(int key[], SDL_Rect *position){
		
	if (key[0] && key[2]){
		position->y --;
		position->x --;
	}
	if (key[0] && key[3]){
		position->y --;
		position->x ++;
	}
	if (key[0] && !key[3] && !key[2]){
		position->y --;
	}
	
	if (key[1] && key[2]){
		position->y ++;
		position->x --;
	}
	if (key[1] && key[3]){
		position->y ++;
		position->x ++;
	}
	if (key[1] && !key[3] && !key[2]){
		position->y ++;
	}
	

	
	if (key[2] && !key[0] && !key[1]){
		position->x --;
	}
	if (key[3] && !key[0] && !key[1]){
		position->x ++;
	}


}


