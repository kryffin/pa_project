#ifndef CONTROLS_H
#define CONTROLS_H

//#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "player.h"

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define JUMP_DURATION 50

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

/* controls.c */
void update_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit, intpoint_t *mouse_pos, bool *mouse_btn);
void render_cursor (SDL_Texture *img, SDL_Renderer *renderer, intpoint_t mouse_pos);
void keyboard_control (player_t *p, SDL_Keycode *key, bool *jumped, Uint32 *timeN_A);
void controls (SDL_Event *event, bool *quit, player_t *p, bool *jumped, intpoint_t *mouse_pos, bool *mouse_btn, SDL_Keycode *key, Uint32 *timeN_A);

#endif
