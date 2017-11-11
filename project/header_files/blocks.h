#ifndef BLOCKS_H
#define BLOCKS_H

enum BlockType {
  Solid,
  Background,
  Foreground,
  Blank
};

typedef struct Block {

  SDL_Rect hitbox; //hitbox of the block
  SDL_Rect spritesheet_pos; //position on the spritesheet

  unsigned short int type; //type of the block

} block_t;

/* blocks.c */
block_t set_block(SDL_Rect hitbox, SDL_Rect spritesheet_pos, unsigned short int type);
void set_block_hitbox (block_t *b, int x, int y, int w, int h);
void set_block_spritesheet_position (block_t *b, int x, int y, int w, int h);
void set_block_type (block_t *b, unsigned short int type);
SDL_Rect get_block_hitbox (block_t b);
SDL_Rect get_block_spritesheet_position (block_t b);
unsigned short int get_block_type (block_t b);

#endif
