#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "controls.h"
#include "game.h"
#include "rendering.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30

#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define PATH_TXT_FILE "./res/arena.txt"
#define PATH_YOU_DIED "./res/you_died.png"

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

/* menu.c */
int menu_controls(game_t *game);
int main_menu_display (game_t *game);
bool mouse_hover_menu (intpoint_t mouse_pos, int targetx, int targety, int width, int height);
int option_menu_display (game_t *game);
int render_menu (game_t *game);

#endif
