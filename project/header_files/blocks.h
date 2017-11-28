#ifndef BLOCKS_H
#define BLOCKS_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>

/**************/
/* STRUCTURES */
/**************/

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

/*************/
/* FUNCTIONS */
/*************/

/* SET */

//returns a new block
block_t set_block(SDL_Rect hitbox, SDL_Rect spritesheet_pos, unsigned short int type);

//change the hitbox of a block
void set_block_hitbox (block_t *b, int x, int y, int w, int h);

//change the position of the sprite sheet used to render the block
void set_block_spritesheet_position (block_t *b, int x, int y, int w, int h);

//change the type of a block
void set_block_type (block_t *b, unsigned short int type);

/* GET*/

//returns the hitbox of a block
SDL_Rect get_block_hitbox (block_t b);

//returns the position on the sprite sheet of a block
SDL_Rect get_block_spritesheet_position (block_t b);

//returns the type of a block
unsigned short int get_block_type (block_t b);

#endif
