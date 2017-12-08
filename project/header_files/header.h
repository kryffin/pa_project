
#ifndef HEADER_H
#define HEADER_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "2dpoint.h"
#include "blocks.h"
#include "vector.h"
#include "character.h"
#include "projectile.h"
#include "level.h"
#include "menu.h"
#include "controls.h"
#include "game.h"

/*************/
/* CONSTANTS */
/*************/

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30

#define PLAYER_SHOOT_DELAY 100
#define DELAY_STEP 150

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

#endif
