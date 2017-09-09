#include "header.h"

/* BLITTING */

//blit a block on the screen
void block_blit (block b, SDL_Surface *surface, SDL_Surface *screen) {
  //give the block's size to the surface
  surface = SDL_CreateRGBSurface(0, get_block_width(b), get_block_height(b), 32, 0, 0, 0, 0);

  //fill the surface with the block's color
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, get_block_color_r(b), get_block_color_g(b), get_block_color_b(b)));

  //blit the surface
  SDL_BlitSurface(surface, NULL, screen, &b.pos);
}

/* SET */

//create a new block
block set_block (unsigned int width, unsigned int height, short int type, SDL_Rect position, SDL_Color color) {
  block b;
  b.w = width;
  b.h = height;
  b.type = type;
  b.pos = position;
  b.col = color;

  return b;
}

//copy a target block b into block c
block set_block_copy (block b) {
  block c;
  c.w = get_block_width(b);
  c.h = get_block_height(b);
  c.type = get_block_type(b);
  c.pos = get_block_position(b);
  c.col = b.col;

  return c;
}

/* GET */

//get the width
int get_block_width (block b) {
  return b.w;
}

//get the height
int get_block_height (block b) {
  return b.h;
}

//get the type (0 : solid | 1 : phantom | 2 : damaging (solid))
short int get_block_type (block b) {
  return b.type;
}

//get the position
SDL_Rect get_block_position (block b) {
  return b.pos;
}

//get the color
SDL_Color get_block_color (block b) {
  return b.col;
}

//specific color canals

//red canal
int get_block_color_r (block b) {
  return b.col.r;
}

//green canal
int get_block_color_g (block b) {
  return b.col.g;
}

//blue canal
int get_block_color_b (block b) {
  return b.col.b;
}

//alpha canal
/*int get_block_color_a (block b) {
  return b.col.a;
} no a canal apparently*/
