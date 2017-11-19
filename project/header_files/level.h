#ifndef LEVEL_H
#define LEVEL_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "character.h"
#include "blocks.h"

/*************/
/* CONSTANTS */
/*************/

#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define PATH_TXT_FILE "./res/arena.txt"
#define PATH_YOU_DIED "./res/you_died.png"

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

/**************/
/* STRUCTURES */
/**************/

typedef struct Level {

  block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]; //all the blocks of the level

  SDL_Texture *blocks_spritesheet; //spritesheet of the blocks
  SDL_Texture *background; //background of the level

} level_t;

/*************/
/* FUNCTIONS */
/*************/

//read the txt file to complete the block array, create the enemies and place the player
level_t init_level (char *blocks, char *path_background, character_t *p, character_list_t *enemies, SDL_Renderer *renderer);

/* SET */

//create a new level
level_t set_level (block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], SDL_Texture *blocks_spritesheet, SDL_Texture *background);

//change one block
void set_level_block(level_t *l, int x, int y,  block_t b);

//change the sprite sheet
void set_level_blocks_spritesheet (level_t *l, SDL_Texture *blocks_spritesheet);

//set a new background
void set_level_background (level_t *l, SDL_Texture *background);

/* GET */

//get the block at a specific position
block_t get_level_block (level_t l, int x, int y);

//get the sprite sheet
SDL_Texture *get_level_blocks_spritesheet (level_t l);

//get the background
SDL_Texture *get_level_background (level_t l);

#endif
