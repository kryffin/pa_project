#include <SDL2/SDL.h>

#include "../header_files/blocks.h"

/* SET */

block_t set_block (SDL_Rect hitbox, SDL_Rect spritesheet_pos, unsigned short int type) {

  block_t b;
  set_block_hitbox(&b, hitbox.x, hitbox.y, hitbox.w, hitbox.h);
  set_block_spritesheet_position(&b, spritesheet_pos.x, spritesheet_pos.y, spritesheet_pos.w, spritesheet_pos.h);
  set_block_type(&b, type);

  return b;
}

void set_block_hitbox (block_t *b, int x, int y, int w, int h) {
  b->hitbox.x = x;
  b->hitbox.y = y;
  b->hitbox.w = w;
  b->hitbox.h = h;

  return;
}

void set_block_spritesheet_position (block_t *b, int x, int y, int w, int h) {
  b->spritesheet_pos.x = x;
  b->spritesheet_pos.y = y;
  b->spritesheet_pos.w = w;
  b->spritesheet_pos.h = h;

  return;
}

void set_block_type (block_t *b, unsigned short int type) {
  b->type = type;

  return;
}

/* GET */

SDL_Rect get_block_hitbox (block_t b) {

  return b.hitbox;
}

SDL_Rect get_block_spritesheet_position (block_t b) {

  return b.spritesheet_pos;
}

unsigned short int get_block_type (block_t b) {

  return b.type;
}
