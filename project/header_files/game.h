#ifndef GAME_H
#define GAME_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include "2dpoint.h"
#include "vector.h"
#include "character.h"
#include "projectile.h"
#include "level.h"

/*************/
/* CONSTANTS */
/*************/

#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define SCREEN_FPS 30
#define FONT_SIZE 15

#define IMG_WIDTH 32
#define IMG_HEIGHT 64
#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16

/**************/
/* STRUCTURES */
/**************/


typedef struct Game {
  FPSmanager *manager; //manages the fps
  SDL_Window *window; //game window
  SDL_Renderer *renderer; //renderer of the window

  bool mouse_btn; //actual state of the mouse button
  intpoint_t mouse_pos; //mouse position
  SDL_Keycode keys[SDL_NUM_SCANCODES]; //array for the keys pressed
  SDL_Texture *cursor; //cursor's image

  SDL_Event *event; //event running the controls

  TTF_Font *font; //font used in the game

  SDL_Color *colorPalette; //palette of 15 colors

  character_t player; //player
  character_list_t enemies; //list of enemies

  SDL_Texture *spriteSheet; //sprite sheet

  bool quit; //variable running the main loop and quitting the game if desired

  level_t currLevel; //current level in which we are playing, hopefully a list one day

} game_t;

/*************/
/* FUNCTIONS */
/*************/

//create a new game
game_t *create_game ();

//initialize the palatte of colors
void init_palette2 (game_t *game);

#endif
