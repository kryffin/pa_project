#ifndef _HEADER_H_
#define _HEADER_H_

#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define SCREEN_BPP 32

/* ANT */

struct Ant {
  short int dir; //direction
  SDL_Rect pos; //position
} ;

typedef struct Ant ant;

/* DIRECTIONS
0 : UP
1 : RIGHT
2 : DOWN
3 : LEFT
*/

/* PROTOTYPES */

void turn_right (ant *a);
void turn_left (ant *a);
void move (ant *a);
void color_palette (SDL_Surface *surface, Uint32 *colors[]);
void draw (SDL_Surface *surface, SDL_MouseButtonEvent mouse, Uint32 pixel);
Uint32 get_pixel_color (SDL_Surface *surface, int x, int y);
void put_pixel_color (SDL_Surface *surface, int x, int y, Uint32 pixel);
void behavior (ant *a, SDL_Surface *surface, Uint32 palette[]);

#endif
