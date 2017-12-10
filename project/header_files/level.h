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
#include "music.h"

/**************/
/* STRUCTURES */
/**************/

typedef struct Level {

  block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]; //all the blocks of the level

  character_list_t enemies; //list of enemies

  SDL_Texture *blocks_spritesheet; //spritesheet of the blocks
  SDL_Texture *background; //background of the level

  Mix_Music *levelMusic; //music to play in the background

} level_t;

typedef struct Level_List *level_list_t;
struct Level_List {
  level_t head;
  level_list_t next;
};

/*************/
/* FUNCTIONS */
/*************/

//free the head of a level list
void free_level (level_list_t l);

//go to next level if enemies are all dead
level_list_t next_level (level_list_t l);

//set the level music
void set_level_music (level_t *l, char *path);

//read the txt file to complete the block array, create the enemies and place the player
level_t init_level (char *blocks, char *path_background, char *path_file, char *path_music, character_t *p, SDL_Renderer *renderer);

/* LIST */

//build a new level on the list
level_list_t level_list_build (level_t l, level_list_t ll);

//returns the head of the list
level_t level_list_head (level_list_t l);

//returns the rest of the list
level_list_t level_list_rest (level_list_t l);

//returns if the list is empty or not
bool level_list_is_empty (level_list_t l);

//returns an empty list
level_list_t level_list_empty ();

//copy the list of level
level_list_t level_list_copy (level_list_t l);

//free the entire list
void level_list_free (level_list_t l);

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
