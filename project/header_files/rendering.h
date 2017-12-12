#ifndef RENDERING_H
#define RENDERING_H

/************/
/* INCLUDES */
/************/

#include "game.h"

/*************/
/* CONSTANTS */
/*************/

#define PATH_YOU_DIED "./res/you_died.png"

/*************/
/* FUNCTIONS */
/*************/

//display a transition between levels
void next_level_transition (game_t *game);

//render the melee attacks
void character_melee (character_t p, SDL_Renderer *renderer, SDL_Texture *img);

//render the cursor
void render_cursor (game_t game);

//render the death screen
void game_over (game_t g);

//render the foreground level
void render_foreground_level (game_t game);

//render the background level as well as the background image
void render_background_level (game_t game);

//render the projectiles of a projectile list
void render_projectiles (projectile_list_t projectiles, SDL_Renderer *renderer, SDL_Texture *img);

//render a character
void render_character (character_t p, SDL_Renderer *renderer, SDL_Texture *img);

//calls every functions to render
void rendering (game_t *game);

#endif
