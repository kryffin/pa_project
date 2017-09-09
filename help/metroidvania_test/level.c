/*********************************/
/*********************************/
/************** WIP **************/
/*********************************/
/*********************************/

#include "header.h"

/* BLITTING */

void level_blit (level l, SDL_Surface *screen) {
  //short int i;

  //filling the background
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, l.col.r, l.col.g, l.col.b));

  //updating the blocks
  //WIP

  //updating the player
  //WIP

  //updating the enemies
  //WIP

  //updating the items
  //WIP

  SDL_Flip(screen);
}
