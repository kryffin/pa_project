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
#include "music.h"

/*************/
/* CONSTANTS */
/*************/

#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_MENU_MUSIC "./res/menu.mp3"
#define PATH_RIFLE_SOUND_EFFECT "./res/rifle.wav"
#define PATH_SHOTGUN_SOUND_EFFECT "./res/shotgun.wav"
#define PATH_MISSILE_SOUND_EFFECT "./res/missile.wav"

#define FONT_SIZE 15

#define NB_MAX_KEYS 8

#define PLAYER_BASE_HP 10

/**************/
/* STRUCTURES */
/**************/


typedef struct Game {
  FPSmanager *manager; //manages the fps
  SDL_Window *window; //game window
  SDL_Renderer *renderer; //renderer of the window

  bool mouse_btn; //actual state of the mouse button
  intpoint_t mouse_pos; //mouse position
  bool keys[NB_MAX_KEYS]; //array for the keys pressed
  SDL_Texture *cursor; //cursor's image

  SDL_Event *event; //event running the controls

  TTF_Font *font; //font used in the game

  SDL_Color *colorPalette; //palette of 15 colors

  character_t player; //player

  SDL_Texture *spriteSheet; //sprite sheet

  bool quit; //variable running the main loop and quitting the game if desired

  bool openMenu; //if we want to leave the game and open the menu

  level_list_t currLevel; //current level in which we are playing, hopefully a list one day

  Mix_Music *menuMusic; //music used in the menu

  musicbox_t musicBox; //box containing music and sound effects

} game_t;

/*************/
/* FUNCTIONS */
/*************/

//create a new game
void create_game (game_t *g);

//reset the player and enemies of the game
void reset_game(game_t *game);

//reset the keys
void reset_keys (game_t *game);

//initialize the palatte of colors
void init_palette2 (game_t *game);

//free a game
void free_game (game_t *g);

//exit the game
void exit_game (game_t *g);

#endif
