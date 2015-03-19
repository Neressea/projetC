#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


int main(){

	int bloque = 1;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE || SDL_DOUBLEBUF); // iniatializing screen
	SDL_WM_SetCaption("Jeu de la mort qui tue", NULL); // set name to this screen

	first_screen();
	
	while(bloque){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				bloque = 0;
			break;
		}

        }


	SDL_Quit();

	return EXIT_SUCCESS;
}

void first_screen(){

	SDL_Surface *main_screen,*wall = NULL;

	main_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
	SDL_FillRect(main_screen, NULL, SDL_MapRGB(main_screen->format, 17, 206, 112));

	SDL_Flip(main_screen);
	
}
