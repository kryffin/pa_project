#ifndef RENDERING_H
#define RENDERING_H

#include "game.h"

void render_cursor (game_t game);
void game_over (SDL_Renderer *renderer);
void rendering (game_t *game);
void render_foreground_level (game_t game);
void render_background_level (game_t game);
void render_projectiles (projectile_list_t projectiles, SDL_Renderer *renderer, SDL_Texture *img);
void render_characters (game_t game, character_list_t c);
void render_character (character_t p, SDL_Renderer *renderer, SDL_Texture *img);

#endif
