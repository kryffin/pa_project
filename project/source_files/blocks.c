/*

blocks.c : contain every functions for the blocks

*/

#include "../header_files/blocks.h"

/* SET */

//returns a new block
block_t set_block (SDL_Rect hitbox, SDL_Rect spritesheet_pos, unsigned short int type) {

  block_t b;
  set_block_hitbox(&b, hitbox.x, hitbox.y, hitbox.w, hitbox.h);
  set_block_spritesheet_position(&b, spritesheet_pos.x, spritesheet_pos.y, spritesheet_pos.w, spritesheet_pos.h);
  set_block_type(&b, type);

  return b;
}

//change the hitbox of a block
void set_block_hitbox (block_t *b, int x, int y, int w, int h) {
  b->hitbox.x = x;
  b->hitbox.y = y;
  b->hitbox.w = w;
  b->hitbox.h = h;

  return;
}

//change the position of the sprite sheet used to render the block
void set_block_spritesheet_position (block_t *b, int x, int y, int w, int h) {
  b->spritesheet_pos.x = x;
  b->spritesheet_pos.y = y;
  b->spritesheet_pos.w = w;
  b->spritesheet_pos.h = h;

  return;
}

//change the type of a block
void set_block_type (block_t *b, unsigned short int type) {
  b->type = type;

  return;
}

/* GET */

//returns the hitbox of a block
SDL_Rect get_block_hitbox (block_t b) {

  return b.hitbox;
}

//returns the position on the sprite sheet of a block
SDL_Rect get_block_spritesheet_position (block_t b) {

  return b.spritesheet_pos;
}

//returns the type of a block
unsigned short int get_block_type (block_t b) {

  return b.type;
}
