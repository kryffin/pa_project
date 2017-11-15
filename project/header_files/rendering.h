#ifndef RENDERING_H
#define RENDERING_H

#include "game.h"

void render_cursor (game_t game);
void game_over (SDL_Renderer *renderer);
void rendering (game_t *game);
void render_foreground_level (game_t game);
void render_background_level (game_t game);
void render_projectiles (game_t game);
void render_player (player_t p, SDL_Renderer *renderer, intpoint_t mouse_pos);

#endif
