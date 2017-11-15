#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "player.h"
#include "blocks.h"
#include "controls.h"

#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define PATH_TXT_FILE "./res/arena.txt"
#define PATH_YOU_DIED "./res/you_died.png"

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

typedef struct Level {

  block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]; //all the blocks of the level

  SDL_Texture *blocks_spritesheet; //spritesheet of the blocks
  SDL_Texture *background; //background of the level

} level_t;

/* level.c */
void game_over (SDL_Renderer *renderer);
void rendering (player_t *player, player_t enemies[10], projectile_t bullets[100], projectile_t enemyProjectiles[100], SDL_Texture *cursor, level_t currLevel, intpoint_t *mouse_pos, SDL_Renderer *renderer);
void render_foreground_level (level_t l, SDL_Renderer *renderer);
void render_background_level (level_t l, SDL_Renderer *renderer);
level_t init_level (SDL_Texture *blocks_spritesheet, SDL_Texture *background, player_t *p, player_t enemies[10]);
level_t set_level (block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], SDL_Texture *blocks_spritesheet, SDL_Texture *background);
void set_level_block(level_t *l, int x, int y,  block_t b);
void set_level_blocks_spritesheet (level_t *l, SDL_Texture *blocks_spritesheet);
void set_level_background (level_t *l, SDL_Texture *background);
block_t get_level_block (level_t l, int x, int y);
SDL_Texture *get_level_blocks_spritesheet (level_t l);
SDL_Texture *get_level_background (level_t l);

#endif
