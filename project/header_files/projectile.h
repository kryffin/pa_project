#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "vector.h"
#include "blocks.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30

#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

typedef struct Projectile {
  floatpoint_t realPos;

  vector_t dir; //direction
  intpoint_t screenPos; //screen position
  SDL_Rect hitbox; //hitbox
  SDL_Rect spritePos; //position in the sprite sheet

} projectile_t ;

typedef struct Projectile_List *projectile_list_t;
struct Projectile_List {

  projectile_t head;
  projectile_list_t next;

};

/* projectile.c */
projectile_list_t update_projectiles (projectile_list_t projectiles, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);
projectile_list_t projectile_list_build (projectile_t p, projectile_list_t pl);
projectile_t projectile_list_head (projectile_list_t p);
projectile_list_t projectile_list_rest (projectile_list_t p);
bool projectile_list_is_empty (projectile_list_t p);
projectile_list_t projectile_list_empty ();
void projectile_list_free (projectile_list_t p);

projectile_t set_projectile (floatpoint_t pos, vector_t dir, SDL_Rect hitbox, SDL_Rect spritePos);
void set_projectile_screen_position (projectile_t *p, int x, int y);
void set_projectile_real_position (projectile_t *p, floatpoint_t pos);
void set_projectile_direction (projectile_t *p, vector_t dir);
void set_projectile_hitbox (projectile_t *p, SDL_Rect hitbox);
void set_projectile_sprite_pos (projectile_t *p, SDL_Rect spritePos);
floatpoint_t get_projectile_real_position (projectile_t p);
intpoint_t get_projectile_screen_position (projectile_t p);
vector_t get_projectile_direction (projectile_t p);
SDL_Rect get_projectile_hitbox (projectile_t p);
SDL_Rect get_projectile_sprite_pos (projectile_t p);

#endif
