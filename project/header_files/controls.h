#ifndef CONTROLS_H
#define CONTROLS_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "character.h"
#include "game.h"

/*************/
/* CONSTANTS */
/*************/

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define JUMP_DURATION 50

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

#define CHARACTER_SPEED 5

#define RIFLE_SHOOT_DELAY 200
#define SHOTGUN_SHOOT_DELAY 200
#define BAZOOKA_SHOOT_DELAY 500

/**************/
/* STRUCTURES */
/**************/

enum Keys {
  KeyQ,
  KeyS,
  KeyD,
  KeyF,
  KeySpace,
  Key1,
  Key2,
  Key3
};

/*************/
/* FUNCTIONS */
/*************/

//update the controls of the keyboard and mouse
void update_controls (game_t *game);

//manages the keyboard inputs
void keyboard_control (game_t *game);

//call the update and control of the keyboard and mouse
void controls (game_t *game);

#endif
