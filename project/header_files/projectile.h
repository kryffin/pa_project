#ifndef PROJECTILE_H
#define PROJECTILE_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "2dpoint.h"
#include "vector.h"
#include "blocks.h"

/*************/
/* CONSTANTS */
/*************/

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30

#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

/**************/
/* STRUCTURES */
/**************/

enum BulletType {
  Bullet,
  Buckshot,
  Missile
};

typedef struct Projectile {
  floatpoint_t realPos; //real position
  SDL_Rect hitbox; //hitbox

  short int bulletType; //used to update the projectile

  vector_t dir; //direction
  SDL_Rect spritePos; //position in the sprite sheet

} projectile_t ;

typedef struct Projectile_List *projectile_list_t;
struct Projectile_List {

  projectile_t head;
  projectile_list_t next;

};

/*************/
/* FUNCTIONS */
/*************/

/* LIST */

//build a new projectile on the list
projectile_list_t projectile_list_build (projectile_t p, projectile_list_t pl);

//returns the head of the list
projectile_t projectile_list_head (projectile_list_t p);

//returns the rest of the projectile list
projectile_list_t projectile_list_rest (projectile_list_t p);

//check if the list is empty
bool projectile_list_is_empty (projectile_list_t p);

//returns an empty list
projectile_list_t projectile_list_empty ();

//free a list
void projectile_list_free (projectile_list_t p);

/* SET */

//create a new projectile
projectile_t set_projectile (floatpoint_t pos, vector_t dir, short int bulletType, SDL_Rect spritePos);

//set the real position
void set_projectile_real_position (projectile_t *p, floatpoint_t pos);

//set the direction
void set_projectile_direction (projectile_t *p, vector_t dir);

//set the type
void set_projectile_bullet_type(projectile_t *p, short int bulletType);

//set the hitbox
void set_projectile_hitbox (projectile_t *p, SDL_Rect hitbox);

//set the sprite position on the sprite sheet
void set_projectile_sprite_pos (projectile_t *p, SDL_Rect spritePos);

/* GET */

//get the real position
floatpoint_t get_projectile_real_position (projectile_t p);

//get the direction
vector_t get_projectile_direction (projectile_t p);

//get the type
short int get_projectile_bullet_type (projectile_t p);

//get the hitbox
SDL_Rect get_projectile_hitbox (projectile_t p);

//get the sprite position on the sprite sheet
SDL_Rect get_projectile_sprite_pos (projectile_t p);

#endif
