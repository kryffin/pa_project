#ifndef _MENU_H_
#define _MENU_H_

#include "header.h"

int menu_controls(SDL_Event *event, int *mousex, int *mousey);
int menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer);

#endif
