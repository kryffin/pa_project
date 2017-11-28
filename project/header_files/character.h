#ifndef PLAYER_H
#define PLAYER_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include "2dpoint.h"
#include "vector.h"
#include "blocks.h"
#include "projectile.h"

/*************/
/* CONSTANTS */
/*************/

#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10

#define JUMP_HEIGHT -16
#define GRAVITY 2

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

#define ENEMY_SHOOT_DELAY 500

#define AIR_ACCELERATION 1.5

/**************/
/* STRUCTURES */
/**************/

enum CharacterDirection {
  Left,
  Right
};

enum CharacterState {
  Walking,
  Jumping,
  nouse,
  Attacking,
  Crouching
};

enum CharacterType {
  Player,
  Enemy,
  Boss
};

typedef struct Character {
  short int hp; //health points
  short int dir; //direction
  short int step; //step used for walking animation
  short int type; //type
  bool onGround; //is the character on a ground?
  short int state; //curent state

  int stepDelay; //used to delay between each step of the walking animation
  int shootDelay; //used to delay between each shot
  int changeVelDelay; //used to delay the automatic change of velocity
  floatpoint_t realPos; //real position
  intpoint_t screenPos; //screen position
  intpoint_t gridPos; //position on the level grid

  projectile_list_t projectiles; //list of projectiles

  vector_t vel; //velocity
  SDL_Rect spritePos; //position of the sprite in the sprite sheet
  SDL_Rect hitbox; //hitbox

} character_t;

typedef struct Character_List *character_list_t;
struct Character_List {
  character_t head;
  character_list_t next;
};

/*************/
/* FUNCTIONS */
/*************/

//create a new projectile and add it in the list
void shooting (bool mouse_btn, character_t *p, intpoint_t target);

//update the grid position
void character_update_grid_pos (character_t *character);

//update a list of projectiles
projectile_list_t update_projectiles (projectile_list_t projectiles, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], character_t *player, character_list_t enemies, bool playerShooting);

//check the collision between the projectile and the enemies
character_list_t bullet_collision (character_list_t enemies, projectile_t p, bool *destroy);

//make the character jump
void character_jumping (character_t *p);

//apply the gravity if the character is in the air
void character_gravity(character_t *p);

//update the positions and hitbox
void update_character (character_t *p, character_list_t *enemies, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], bool *quit);

//update the enemies' shots and directions
character_list_t update_enemies (character_list_t c, character_t *p, block_t [NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);

//update the step used for the walking animation
void character_update_step(character_t *p);

//update the character direction to look towards the target
void character_update_dir (character_t *p, intpoint_t target);

//apply the velocity on the character if possible
void character_apply_velocity (character_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);

//returns true if the character is alive, dead otherwise
bool is_alive(character_t p);

/* LIST */

//build a new character on the list
character_list_t character_list_build (character_t p, character_list_t pl);

//returns the head of the character list
character_t character_list_head (character_list_t p);

//returns the rest of the character list
character_list_t character_list_rest (character_list_t p);

//returns true if the character list is empty, false otherwise
bool character_list_is_empty (character_list_t p);

//returns an empty character list
character_list_t character_list_empty ();

//free the list of character as well as their projectiles
void character_list_free (character_list_t p);

/* SET */

//create a new character
character_t set_character (short int hp, floatpoint_t position, vector_t velocity, SDL_Rect posSprite, SDL_Rect hitbox, short int type);

//set the character's health points
void set_character_hp (character_t *p, short int hp);

//set the current direction
void set_character_dir (character_t *p, short int dir);

//set the step
void set_character_step (character_t *p, short int step);

//set the type
void set_character_type (character_t *p, short int type);

//set the character on ground or not
void set_character_on_ground (character_t *p, bool onGround);

//set the character's state
void set_character_state (character_t *p, short int state);

//set the delay of the step
void set_character_step_delay (character_t *p, int stepDelay);

//set the delay of shooting
void set_character_shoot_delay (character_t *p, int shootDelay);

//set the character's real position
void set_character_real_position (character_t *p, float x, float y);

//set the character's screen position
void set_character_screen_position (character_t *p, int x, int y);

//set the character's grid position
void set_character_grid_position (character_t *p, int x, int y);

//set the list of projectiles
void set_character_projectiles (character_t *p, projectile_list_t projectiles);

//set the character's velocity
void set_character_velocity (character_t *p, float x, float y);

//set the character sprite position on the spritesheet
void set_character_sprite_pos (character_t *p, SDL_Rect posSprite);

//set the character hitbox
void set_character_hitbox (character_t *p, SDL_Rect hitbox);

//apply the velocity for each enemies
void character_apply_velocity_ennemies (character_list_t *enemies, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], Uint32 time);
/* GET */

//get the character's health points
short int get_character_hp (character_t p);

//get the current direction
short int get_character_dir (character_t p);

//get the step
short int get_character_step (character_t p);

//get the type
short int get_character_type (character_t p);

//get the on ground boolean
bool get_character_on_ground (character_t p);

//get the character's state
short int get_character_state (character_t p);

//get the character's step delay
int get_character_step_delay (character_t p);

//get the character's shoot delay
int get_character_shoot_delay (character_t p);

//get the character's real position
floatpoint_t get_character_real_position (character_t p);

//get the character's position
intpoint_t get_character_screen_position (character_t p);

//get the character's grid position
intpoint_t get_character_grid_position (character_t p);

//get the list of projectiles
projectile_list_t get_character_projectiles (character_t p);

//get the character's x velocity
vector_t get_character_velocity (character_t p);

//get the character's sprite position on the sprite sheet
SDL_Rect get_character_sprite_pos (character_t p);

//get the character's hitbox
SDL_Rect get_character_hitbox (character_t p);

//return the size of the list
int character_list_size (character_list_t c);

#endif
