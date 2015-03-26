#ifndef main_h 
#include "../header/Map.h"
#define main_h
#define SPEED 1
#define SCREEN_H 640
#define SCREEN_W 480
#define PX_H 50
#define PX_W 50
#define NB_SPRITES_H 24

int main();
void managing_event();
void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void test_key(int key [], SDL_Rect *position);
void destroy_texture(int taille, SDL_Texture *tableau[]);

#endif
