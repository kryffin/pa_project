#ifndef VAR_INIT_H
#define VAR_INIT_H

/* var_init.c */
int init_palette (SDL_Color **palette);
int init_font (TTF_Font **font);
int init_window (SDL_Window **window);
int init_renderer (SDL_Renderer **renderer, SDL_Window *window);
int init_sdl (SDL_Window **window, SDL_Renderer **renderer);
int init_images (SDL_Surface **temp, SDL_Texture **player_tSprite, SDL_Texture **cursor, SDL_Texture **blocks_spritesheet, SDL_Texture **background, SDL_Renderer *renderer);
int init_projectiles (projectile_t *projectiles[100], SDL_Texture *img, int x, int y);
int init_variables (Uint32 **initTimer, FPSmanager **manager, SDL_Window **window, SDL_Renderer **renderer, intpoint_t **mouse_pos, SDL_Event **event, bool **jumped, bool **mouse_btn, int **i, TTF_Font **font, SDL_Color **palette, player_t **p, projectile_t  **projectiles, int **stepDelay, bool **quit, SDL_Surface **temp, SDL_Texture **player_tSprite, SDL_Texture **cursor, Uint32 **timeN_A, Uint32 **timeN_B, level_t **currLevel, SDL_Texture **blocks_spritesheet, SDL_Texture **background, player_t **enemies, projectile_t **enemyProjectiles);
void free_variables (SDL_Texture *player_tSprite, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font, int *i, projectile_t *projectiles, player_t *p, FPSmanager *manager, SDL_Color *colorPalette, SDL_Event *event, bool *quit, bool *jumped, intpoint_t *mouse_pos, bool *mouse_btn, Uint32 *timeN_A, Uint32 *timeN_B, level_t *currLevel, SDL_Texture *blocks_spritesheet, SDL_Texture *background, int *stepDelay, player_t *enemies, projectile_t  *enemyProjectiles);

#endif
