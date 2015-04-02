#include "../header/Spell.h"

int screen_h1 = SCREEN_H;
int screen_w1 = SCREEN_W;


/*void compute_attack(SDL_Rect *pattack[], int *f, int key[]){

	if(key[4]){
		if (*f == 0 && pattack[0]->y >= screen_h1){
			pattack[0]->y = screen_h1 / 2 - PXH_H / 2;
		}
		else if(*f == 3){
			pattack[1]->y = screen_h1 / 2 - PXH_H / 2;
		}
		else if(*f == 6){
			pattack[2]->x = screen_w1 / 2 - PXH_W / 2;
		}
	}

	
	

}

void blit_attack(SDL_Rect *pattack[], SDL_Renderer *rendu, SDL_Texture *tableau[]){
	
	if(pattack[0]->y < screen_h1){
		SDL_RenderCopy(rendu, tableau[0], NULL, pattack[0]);
		SDL_RenderPresent(rendu);
		pattack[0]->y += SPEED;
	}

	if(pattack[1]->y > 0){
		SDL_RenderCopy(rendu, tableau[0], NULL, pattack[1]);
		SDL_RenderPresent(rendu);
		pattack[1]->y -= SPEED;
	}

	if(pattack[2]->x > 0){
		SDL_RenderCopy(rendu, tableau[0], NULL, pattack[2]);
		SDL_RenderPresent(rendu);
		pattack[2]->x -= SPEED;
	}

}

void init_attack(SDL_Rect *pattack[]){
	int i;

	for (i=0; i < NB_SPRITES_A ;i++){
		pattack[i] = malloc(sizeof(SDL_Rect));

		pattack[i]->h = PXH_H;
		pattack[i]->w = PXH_W;
	}
	
	pattack[0]->x = screen_w1 /2 - PXH_W / 2;
	pattack[0]->y = screen_h1;
	pattack[1]->x = screen_w1 /2 - PXH_W / 2;
	pattack[1]->y = 0;
	pattack[2]->x = 0;
	pattack[2]->y = screen_h1 /2 - PXH_H / 2;
	

}*/

Spell* createSpell(TypeSpell *type, int direction, int x, int y){
	Spell *c = (Spell*) malloc(sizeof(Spell));
	c->type = type;
	c->direction = direction;
	c->time = SDL_GetTicks();
	c->pspell = malloc(sizeof(SDL_Rect));
	c->pspell->h = PX_H;
	c->pspell->w = PX_W;
	c->pspell->x = x;
	c->pspell->y = y;

	return c;

}

void updateSpell(ListSpell *current_list){
	
	deleteSpell(current_list);

	ListSpell *cursor = current_list->nextSpell;

	int current_direction = 0;

	while(cursor != NULL){

		current_direction = cursor->currentSpell->direction;		

		if (current_direction == 0){
			cursor->currentSpell->pspell->y ++;
		}
	}
}

void deleteSpell(ListSpell *current_list){
	
	ListSpell *cursor = current_list->nextSpell;
	
	while(cursor != NULL){
		if (SDL_GetTicks() - cursor->currentSpell->time > LIFEEXPANC){
			current_list->nextSpell = cursor->nextSpell;
			free(cursor);
			cursor = current_list;
		}
		
		cursor = cursor->nextSpell;		

	}
}

void lanceattack(ListSpell *current_list, int f, TypeSpell *current_type, int key[]){
	if (key[4]){
		
		Spell *new = createSpell(current_type, f, screen_w1 /2- PXH_W / 2,screen_h1 /2 - PXH_H / 2);			
		ListSpell * newlist = malloc(sizeof(ListSpell));
		newlist->currentSpell = new;
		newlist->nextSpell = NULL;
		current_list->nextSpell = newlist;

	}
}

TypeSpell *init_typeSpell(int attack, int ammo, int rate){
	TypeSpell *t= malloc(sizeof(TypeSpell));

	t->attack = attack;
	t->ammo = ammo;
	t->rate = rate;

	return t;
}


