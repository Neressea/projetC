#ifndef main_h 
#include "../header/Map.h"
#define main_h
#define SPEED 4
#define SPEED_TRAME 15
#define SCREEN_W 640
#define SCREEN_H 480
#define PX_H 50
#define PX_W 50
#define PXH_H 100
#define PXH_W 70
#define NB_SPRITES_H 24
#define NB_SPRITES_A 9
#define FPS 10

int main();
void managing_event();
void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void test_key(int key[], SDL_Rect *position);
void destroy_texture(int taille, SDL_Texture *tableau[]);
SDL_Texture* update_heros(int key[], SDL_Texture *tableau[], int *trame, int *f);
void compute_tram(int *j, int *trame);
int text_move(int *trame);
void attack_heros(SDL_Rect *pattack,int *f, SDL_Renderer *rendu, SDL_Texture *tableau[], int key[]);

#endif
