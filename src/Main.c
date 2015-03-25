#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../header/Main.h"

int main(){

	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}
	
	managing_event();

	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}


void managing_event(){
		

	SDL_Window *main_screen = NULL;
	SDL_Renderer *rendu = NULL;
	SDL_Texture *texture_ennemy = NULL;
	SDL_Rect pennemy;
	SDL_Rect SrcR;
	
	main_screen = SDL_CreateWindow("Jeu de la mort qui tue",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,600,600, SDL_WINDOW_SHOWN); 			 // iniatializing screen
	rendu = SDL_CreateRenderer(main_screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(rendu, 0, 255, 255, 255);
	SDL_RenderClear(rendu);
	
	texture_ennemy = IMG_LoadTexture(rendu, "./images/sprites/tower.bmp");

	SDL_ShowCursor(SDL_DISABLE);

	if (texture_ennemy == NULL){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}
	
	pennemy.h = 200;
	pennemy.w = 200;
	pennemy.x = 0;
	pennemy.y = 0;

	SrcR.x = 0;
  	SrcR.y = 0;
	SrcR.h = 200;
	SrcR.h = 200;

	int quit = 0;
	int key[4] = {0};

	SDL_Event event;
		
	
	while(quit == 0){
		SDL_WaitEvent(&event);
			switch(event.type){
				case SDL_QUIT:
					quit = 1;
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

	

	SDL_RenderClear(rendu);
	SDL_RenderCopy(rendu, texture_ennemy, &SrcR, &pennemy);	
	SDL_RenderPresent(rendu);

	test_key(key, &pennemy);	

	SDL_Delay(1);

		if (texture_ennemy == NULL){
			fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
			exit(EXIT_FAILURE);
		}

	}
	
	SDL_DestroyTexture(texture_ennemy);
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(main_screen);
	
	
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


