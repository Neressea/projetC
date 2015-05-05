#include "../header/Main.h"

int screen_h = SCREEN_H;
int screen_w = SCREEN_W;

int main(){
	
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL_IMG : %s\n", SDL_GetError()); // managing IMG loading error 
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL_TTF : %s\n", SDL_GetError()); // managing TTF loading error 
		exit(EXIT_FAILURE);
	}

	SDL_Window *main_screen = SDL_CreateWindow("Jeu de la mort qui tue",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_W,SCREEN_H, SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);
	SDL_Renderer *rendu = SDL_CreateRenderer(main_screen, -1, SDL_RENDERER_SOFTWARE);

	SDL_Rect *title = malloc(sizeof(SDL_Rect));
	SDL_Color textColor = { 255, 255, 255, 255 }; 
	SDL_Event event;

	TTF_Font* font = TTF_OpenFont("./images/polices/AmaticSC-Regular.ttf",100);
    	SDL_Surface *Surface_Title = TTF_RenderText_Solid (font, "The Game", textColor);
	SDL_Surface *Surface_Tsubtitle = TTF_RenderText_Solid (font, "Appuyez sur une touche", textColor);
	SDL_Texture* Text_title = SDL_CreateTextureFromSurface(rendu, Surface_Title);
	SDL_Texture* Text_subtitle = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle);

	int screen = 0;
	int test = 0;
	

	while(screen == 0){
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN){
			screen = 1;
		}

		title->h = 400;
		title->w = 400;	
		title->x = screen_w/2 - title->w/2;
		title->y = screen_h/2 - title->h/2 - 100;

		SDL_RenderClear(rendu);

		SDL_RenderCopy(rendu, Text_title, NULL, title );

		title->h = 100;
		title->w = 300;	
		title->x = screen_w/2 - title->w/2;
		title->y = screen_h/2 - title->h/2 + 100;

		

		if(SDL_GetTicks() - test>50){
			if(SDL_GetTicks()- test>300){
				test = SDL_GetTicks();
			}
			SDL_RenderCopy(rendu, Text_subtitle, NULL, title );	
		}else{
	
		}

		SDL_RenderPresent(rendu);

	
	}

	managing_event(main_screen,rendu);

	free(title);
	TTF_CloseFont(font);	
	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void managing_event(SDL_Window * main_screen, SDL_Renderer *rendu){

	SDL_Texture *texture_heros[NB_SPRITES_H + NB_SPRITES_A] = {NULL};
	SDL_Texture *texture_ennemy[NB_SPRITES_H] = {NULL};	
	SDL_Texture *texture_attack[NB_TYP_SPELL*NB_SPRITES_A] = {NULL};
	SDL_Texture *texture_type[NB_TYP_SPELL] = {NULL};
	SDL_Texture *current_texture = NULL;
	SDL_Rect *pattack = NULL;
	Map *map = malloc(sizeof(Map));
	ListSpell *liste_spell = init_listspell();
	
	TypeSpell **tab_typeSpell = malloc(NB_TYP_SPELL*sizeof(TypeSpell));
	tab_typeSpell[0] = init_typeSpell(100,0,500,-1);
	tab_typeSpell[1] = init_typeSpell(100,1,500,20);
	TypeSpell *current_type = tab_typeSpell[0];
	
	Move *move = malloc(sizeof(Move));
	SDL_Texture** texture_chara[] = {texture_heros, texture_ennemy};

	int quit = 0;
	int key[7] = {0};
	int direction = 0;
	int limit = 0;
	int test = 0;

	SDL_SetRenderDrawColor(rendu, 0, 255, 255, 255);
	SDL_RenderClear(rendu);
	
	init_texture(rendu, texture_heros);
	init_texture_ennemy(rendu, texture_ennemy);
	init_texture_attack(rendu, texture_attack);
	init_type_attack(rendu, texture_type);
	
	current_texture = texture_heros[0];

	if (current_texture == NULL){
		fprintf(stderr, "Erreur d'initialisation de sprite courant : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	load(rendu, map, "./maps/map1");
	
	pattack = malloc(sizeof(SDL_Rect));

	pattack->h = PX_H;
	pattack->w = PX_W;
	pattack->x = 10;
	pattack->y = screen_h- PX_W - 10;	

	SDL_Event event;
		
	SDL_ShowCursor(SDL_DISABLE);
	
	while(quit == 0){

		SDL_PollEvent(&event);
			switch(event.type){
				case SDL_QUIT:
					quit = 1;
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym){	//openclassrooms.com/uploads/fr/ftp/mateo21/sdlkeysym.html
						case SDLK_ESCAPE:
							quit = 1;
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
						case SDLK_SPACE:
							key[4] = 1;
						break;
						case SDLK_a:
							key[5] = 1;
						break;
						case SDLK_z:
							key[6] = 1;
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
						case SDLK_SPACE:
							key[4] = 0;
						break;
						case SDLK_a:
							key[5] = 0;
						break;
						case SDLK_z:
							key[6] = 0;
						break;
						}
				break;
							
			}


	SDL_RenderClear(rendu);

	SDL_GetWindowSize(main_screen,&screen_w,&screen_h);

	showMap(main_screen, rendu, map);
	showCharacters(rendu, map->characters, map->corner, texture_chara, key, &direction);
	
	changeTypeSpell(key, tab_typeSpell,&current_type);
	lanceattack(liste_spell, &direction, current_type, key);
	
	move->x = 0;
	move->y = 0;
	moveMap(main_screen, map, key, move);

	updateSpell(liste_spell, move, main_screen);
	
	Blit_attack(liste_spell,rendu, texture_attack);
	
	
	SDL_RenderCopy(rendu, texture_type[current_type->id], NULL, pattack);	
	SDL_RenderPresent(rendu);

	//We manage the FPS
	
	test = SDL_GetTicks();	

	if (limit > test){
		if (limit > test + FPS){
			SDL_Delay(FPS);
		}
		else {
			SDL_Delay(limit - test);
		}
	}

		limit = SDL_GetTicks() + FPS;
	
		if (current_texture == NULL){
			fprintf(stderr, "Erreur de récupération des textures : %s\n", SDL_GetError()); // managing SDL loading error 
			exit(EXIT_FAILURE);
		}

	}
	
	SDL_DestroyTexture(current_texture);
	destroy_texture(NB_SPRITES_H, texture_heros);
	destroyMap(map);
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(main_screen);
	
}

void test_key(int key[], SDL_Rect *position){
		
	if (key[0] && key[2]){
		position->y -= SPEED;
		position->x -= SPEED;
	}
	if (key[0] && key[3]){
		position->y -= SPEED;
		position->x += SPEED;
	}
	if (key[0] && !key[3] && !key[2]){
		position->y -= SPEED;
	}
	
	if (key[1] && key[2]){
		position->y += SPEED;
		position->x -= SPEED;
	}
	if (key[1] && key[3]){
		position->y += SPEED;
		position->x += SPEED;
	}
	if (key[1] && !key[3] && !key[2]){
		position->y += SPEED;
	}
		
	if (key[2] && !key[0] && !key[1]){
		position->x -= SPEED;
	}
	if (key[3] && !key[0] && !key[1]){
		position->x += SPEED;
	}

}

void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]){
	tableau[0] = IMG_LoadTexture(rendu, "./images/sprites/heros0.png");
	tableau[1] = IMG_LoadTexture(rendu, "./images/sprites/heros1.png");
	tableau[2] = IMG_LoadTexture(rendu, "./images/sprites/heros2.png");
	tableau[3] = IMG_LoadTexture(rendu, "./images/sprites/heros3.png");
	tableau[4] = IMG_LoadTexture(rendu, "./images/sprites/heros4.png");
	tableau[5] = IMG_LoadTexture(rendu, "./images/sprites/heros5.png");
	tableau[6] = IMG_LoadTexture(rendu, "./images/sprites/heros6.png");
	tableau[7] = IMG_LoadTexture(rendu, "./images/sprites/heros7.png");
	tableau[8] = IMG_LoadTexture(rendu, "./images/sprites/heros8.png");
	tableau[9] = IMG_LoadTexture(rendu, "./images/sprites/heros9.png");
	tableau[10] = IMG_LoadTexture(rendu, "./images/sprites/heros10.png");
	tableau[11] = IMG_LoadTexture(rendu, "./images/sprites/heros11.png");
	tableau[12] = IMG_LoadTexture(rendu, "./images/sprites/heros12.png");
	tableau[13] = IMG_LoadTexture(rendu, "./images/sprites/heros13.png");
	tableau[14] = IMG_LoadTexture(rendu, "./images/sprites/heros14.png");
	tableau[15] = IMG_LoadTexture(rendu, "./images/sprites/heros15.png");
	tableau[16] = IMG_LoadTexture(rendu, "./images/sprites/heros16.png");
	tableau[17] = IMG_LoadTexture(rendu, "./images/sprites/heros17.png");
	tableau[18] = IMG_LoadTexture(rendu, "./images/sprites/heros18.png");
	tableau[19] = IMG_LoadTexture(rendu, "./images/sprites/heros19.png");
	tableau[20] = IMG_LoadTexture(rendu, "./images/sprites/heros20.png");
	tableau[21] = IMG_LoadTexture(rendu, "./images/sprites/heros21.png");
	tableau[22] = IMG_LoadTexture(rendu, "./images/sprites/heros22.png");
	tableau[23] = IMG_LoadTexture(rendu, "./images/sprites/heros23.png");
	tableau[24] = IMG_LoadTexture(rendu, "./images/sprites/heros24.png");
	tableau[25] = IMG_LoadTexture(rendu, "./images/sprites/heros25.png");
	tableau[26] = IMG_LoadTexture(rendu, "./images/sprites/heros26.png");
	tableau[27] = IMG_LoadTexture(rendu, "./images/sprites/heros27.png");
	tableau[28] = IMG_LoadTexture(rendu, "./images/sprites/heros28.png");
	tableau[29] = IMG_LoadTexture(rendu, "./images/sprites/heros29.png");
	tableau[30] = IMG_LoadTexture(rendu, "./images/sprites/heros30.png");
	tableau[31] = IMG_LoadTexture(rendu, "./images/sprites/heros31.png");
}

void init_texture_ennemy(SDL_Renderer *rendu, SDL_Texture *tabl[]){
	tabl[0] = IMG_LoadTexture(rendu, "./images/sprites/monstre0.png");
}

void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tabl[]){
	tabl[0] = IMG_LoadTexture(rendu, "./images/sprites/attck0_fireball.png");
	tabl[1] = IMG_LoadTexture(rendu, "./images/sprites/attck1_fireball.png");
	tabl[2] = IMG_LoadTexture(rendu, "./images/sprites/attck2_fireball.png");
	tabl[3] = IMG_LoadTexture(rendu, "./images/sprites/attck3_fireball.png");
	tabl[4] = IMG_LoadTexture(rendu, "./images/sprites/attck4_fireball.png");
	tabl[5] = IMG_LoadTexture(rendu, "./images/sprites/attck5_fireball.png");
	tabl[6] = IMG_LoadTexture(rendu, "./images/sprites/attck6_fireball.png");
	tabl[7] = IMG_LoadTexture(rendu, "./images/sprites/attck7_fireball.png");
	tabl[8] = IMG_LoadTexture(rendu, "./images/sprites/attck0_frost.png");
	tabl[9] = IMG_LoadTexture(rendu, "./images/sprites/attck1_frost.png");
	tabl[10] = IMG_LoadTexture(rendu, "./images/sprites/attck2_frost.png");
	tabl[11] = IMG_LoadTexture(rendu, "./images/sprites/attck3_frost.png");
	tabl[12] = IMG_LoadTexture(rendu, "./images/sprites/attck4_frost.png");
	tabl[13] = IMG_LoadTexture(rendu, "./images/sprites/attck5_frost.png");
	tabl[14] = IMG_LoadTexture(rendu, "./images/sprites/attck6_frost.png");
	tabl[15] = IMG_LoadTexture(rendu, "./images/sprites/attck7_frost.png");

}

void init_type_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]){
	tableau[0] = IMG_LoadTexture(rendu, "./images/sprites/typespell0.png");
	tableau[1] = IMG_LoadTexture(rendu, "./images/sprites/typespell1.png");
}

void destroy_texture(int taille, SDL_Texture *tableau[]){
	int i;

	for (i = 0; i < taille; i++){
		SDL_DestroyTexture(tableau[i]);
	}

}

void changeTypeSpell (int key[], TypeSpell **tab_typeSpell, TypeSpell **current_type){
	int i;

	for (i = 5 ; i < NB_TYP_SPELL + 5; i ++){
		if (key[i] == 1){			
			*current_type = tab_typeSpell[i-5];
		}
	}
}


