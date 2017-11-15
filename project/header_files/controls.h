#ifndef CONTROLS_H
#define CONTROLS_H

//#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "player.h"
#include "game.h"

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define JUMP_DURATION 50

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

/* controls.c */
void update_controls (game_t *game);
void keyboard_control (game_t *game);
void controls (game_t *game);

#endif
