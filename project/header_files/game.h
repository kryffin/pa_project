#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include "2dpoint.h"
#include "vector.h"
#include "player.h"
#include "projectile.h"
#include "level.h"

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

typedef struct Game {
  FPSmanager *manager;
  SDL_Window *window;
  SDL_Renderer *renderer;

  //texture of the cursor
  SDL_Texture *cursor;

  //mouse position
  intpoint_t mouse_pos;

  //array for the keys pressed
  SDL_Keycode keys[SDL_NUM_SCANCODES];

  //event running the controls
  SDL_Event *event;

  //actual state of the mouse button
  bool mouse_btn;

  //font used in the game
  TTF_Font *font;

  //palette of 15 colors
  SDL_Color *colorPalette;

  //the main player_t
  player_t player;
  player_t enemies[10];

  //projectiles of the player_t : array of 100
  projectile_t playerProjectiles[100];
  projectile_t enemyProjectiles[100];

  //variable running the main loop and quitting the game if desired
  bool quit;

  level_t currLevel;

} game_t;

game_t *create_game ();
void init_palette2 (game_t *game);

#endif
