#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include "2dpoint.h"
#include "vector.h"
#include "blocks.h"
#include "projectile.h"

#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10

#define JUMP_HEIGHT -16

#define GRAVITY 2

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

#define ENEMY_SHOOT_DELAY 500

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
  short int hp; //current health points
  short int dir; //current direction+-
  short int step; //step for the surrent sprite to use

  int xGrid;
  int yGrid;

  bool onGround; //is the character on a ground?
  int jumpPoint; //point from where you jumped
  int highPoint; //highest point of the jump (used for falling?)

  projectile_list_t projectiles;

  //delay used between each step in the character animation
  int stepDelay;

  int shootDelay;

  int jumpDelay;

  short int state; //curent state of the character_t
  floatpoint_t realPos; //position in float
  intpoint_t screenPos; //position in integer
  vector_t vel; //velocity for the character_t's movement
  SDL_Rect spritePos; //position of the sprite in the sprite sheet
  SDL_Rect hitbox; //hitbox

  short int type;

} character_t;

typedef struct Character_List *character_list_t;
struct Character_List {
  character_t head;
  character_list_t next;
};

/* character_t.c */
void shooting (bool mouse_btn, character_t *p, intpoint_t target);

void character_update_grid_pos (character_t *character);
void character_jumping (character_t *p);
void character_gravity(character_t *p);
void update_character (character_t *p, bool *quit);
character_list_t update_enemies (character_list_t c, character_t p, block_t [NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);
void character_melee (character_t p, SDL_Renderer *renderer, SDL_Texture *img);
void character_update_step(character_t *p);
void character_update_dir (character_t *p, intpoint_t mouse_pos);
void character_apply_velocity (character_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);
bool is_alive(character_t p);

character_list_t character_list_build (character_t p, character_list_t pl);
character_t character_list_head (character_list_t p);
character_list_t character_list_rest (character_list_t p);
bool character_list_is_empty (character_list_t p);
character_list_t character_list_empty ();
void character_list_free (character_list_t p);

character_t set_character (short int hp, floatpoint_t position, vector_t velocity, SDL_Rect posSprite, SDL_Rect hitbox, short int type);
void set_character_maxhp (character_t *p, short int maxhp);
void set_character_hp (character_t *p, short int hp);
void set_character_dir (character_t *p, short int dir);
void set_character_step (character_t *p, short int step);
void set_character_on_ground (character_t *p, bool onGround);
void set_character_jumpPoint (character_t *p, int jumpPoint);
void set_character_highPoint (character_t *p, int highPoint);
void set_character_state (character_t *p, short int state);
void set_character_real_position (character_t *p, float x, float y);
void set_character_screen_position (character_t *p, int x, int y);
void set_character_vel_x (character_t *p, float x);
void set_character_vel_y (character_t *p, float y);
void set_character_sprite_pos (character_t *p, SDL_Rect posSprite);
void set_character_hitbox (character_t *p, SDL_Rect hitbox);
short int get_character_maxhp (character_t p);
short int get_character_hp (character_t p);
short int get_character_dir (character_t p);
short int get_character_step (character_t p);
bool get_character_on_ground (character_t p);
int get_character_jumpPoint (character_t p);
int get_character_highPoint (character_t p);
short int get_character_state (character_t p);
floatpoint_t get_character_real_position (character_t p);
intpoint_t get_character_screen_position (character_t p);
vector_t get_character_velocity (character_t p);
SDL_Rect get_character_sprite_pos (character_t p);
SDL_Rect get_character_hitbox (character_t p);

#endif
