#ifndef LEVEL_H
#define LEVEL_H

typedef struct Level {

  block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]; //all the blocks of the level

  SDL_Texture *blocks_spritesheet; //spritesheet of the blocks
  SDL_Texture *background; //background of the level

} level_t;

/* level.c */
void closest_out (player_t *player, int w, int h);
bool collision_intpoint (intpoint_t a, intpoint_t b);
bool collision (player_t player, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], int *width, int *height);
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
