#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "controls.h"

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
void render_text(char *string, SDL_Rect pos, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);
int menu_controls(SDL_Event *event, intpoint_t *mouse_pos);
int main_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *player_tSprite);
bool mouse_hover_menu (intpoint_t mouse_pos, int targetx, int targety, int width, int height);
int option_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *player_tSprite);
int render_menu (bool *quit, TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *cursor);

#endif
