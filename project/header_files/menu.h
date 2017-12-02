#ifndef MENU_H
#define MENU_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "controls.h"
#include "game.h"
#include "rendering.h"

/*************/
/* CONSTANTS */
/*************/

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30

#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"

#define PATH_ARENA_MUSIC "./res/arena.mp3"
#define PATH_LEVEL1_MUSIC "./res/level1.mp3"
#define PATH_LEVEL2_MUSIC "./res/level2.mp3"
#define PATH_LEVEL3_MUSIC "./res/level3.mp3"

#define PATH_BACKGROUND "./res/menubackground.jpg"
#define PATH_BACKGROUND_LEVEL_1 "./res/background1.jpg"
#define PATH_BACKGROUND_LEVEL_2 "./res/background2.png"
#define PATH_BACKGROUND_LEVEL_3 "./res/background3.jpg"
#define PATH_BACKGROUND_ARENA "./res/arena.jpg"

#define PATH_TXT_LEVEL_1 "./res/level1.txt"
#define PATH_TXT_LEVEL_2 "./res/level2.txt"
#define PATH_TXT_LEVEL_3 "./res/level3.txt"
#define PATH_TXT_ARENA "./res/arena.txt"

#define PATH_YOU_DIED "./res/you_died.png"

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

/*************/
/* FUNCTIONS */
/*************/

//manages the menu
void menu (game_t *g);

//function returning the state of the mouse
int menu_controls(game_t *game);

//returns true if the mouse is hovering the target
bool mouse_hover_menu (intpoint_t mouse_pos, int targetx, int targety, int width, int height);

//display of the main menu
int main_menu_display (game_t *game);

//loop managing the menus
int render_menu (game_t *game);

#endif
