#ifndef _HEADER_H_
#define _HEADER_H_

/* INCLUDES */

#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>

/* CONSTANTS */

//window
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define FONT_SIZE 15
//img
#define IMG_WIDTH 105 //160 original
#define IMG_HEIGHT 130 //160 original
//paths
#define PATH_IMG_L "./res/sprite_l_2.bmp"
#define PATH_IMG_R "./res/sprite_r_2.bmp"
#define PATH_FONT "./res/font.ttf"

struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction

  bool dash; //is dash available?
  short int dashState; //current state of the dash (used to proceed through the dash)

  bool dJump; //is double jump available?
  int jumpPoint; //point from where you jumped
  int highPoint; //highest point of the jump (used for falling?)

  short int state; //curent state of the player
  SDL_Rect pos; //position of the origin (top left)
  SDL_Rect vel; //velocity for the player's movement
  SDL_Surface *img; //image used for displaying the player
};

typedef struct Player player;

/* DIR
  0 : left
  1 : right
*/

/* STATE
  0 : walking / normal
  1 : jumping
  2 : double-jumping
  3 : dashing
*/

/* blocks.h */

struct Block {
  int w; //width
  int h; //height
  short int type; //type of the block
  SDL_Rect pos; //position of the origin (top left)
  SDL_Color col; //color of the Block (use surface if img)
};

/* TYPES ::
  0 : solid
  1 : phantom
  2 : damaging (solid)
*/

typedef struct Block block;

void block_blit (block b, SDL_Surface *surface, SDL_Surface *screen);
block set_block (unsigned int width, unsigned int height, short int type, SDL_Rect position, SDL_Color color);
block set_block_copy (block b);
int get_block_width (block b);
int get_block_height (block b);
short int get_block_type (block b);
SDL_Rect get_block_position (block b);
SDL_Color get_block_color (block b);
int get_block_color_r (block b);
int get_block_color_g (block b);
int get_block_color_b (block b);
int get_block_color_a (block b);

/* controls.h */

void control (SDL_Event event, player *p, bool *exit);

/* level.h */

struct Level {
  SDL_Color col; //background color of the level (change to SDL_Surface for an image)

  short int nbBlocks; //number of used blocks
  block blocks[10]; //10 blocks to make a level (temporary)

  /* player p; //the player (player : WIP) */

  /*short int nbEnemies; //number of existing enemies
  enemy enemies[10]; //10 enemies max on a level (temporary) (enemy : WIP) */

  /*short int nbItems; //number of existing items
  item items[10]; //10 items max o a level (temporary) (item : WIP) */
};

typedef struct Level level;

void level_blit (level l, SDL_Surface *screen);

/* player.h */

void player_blit (player p, SDL_Surface *img_l, SDL_Surface *img_r, SDL_Surface *screen);
void player_apply_velocity (player *p);
void player_dashing (player *p);
void player_jumping (player *p);
player set_player (short int maxHealthPoints, short int healthPoints, short int direction, bool dash, bool doubleJump, SDL_Rect position, SDL_Rect velocity, SDL_Surface *image);
player set_player_copy (player p);
void set_player_maxhp (player *p, short int maxhp);
void set_player_hp (player *p, short int hp);
void set_player_dir (player *p, short int dir);
void set_player_dash (player *p, bool dash);
void set_player_dashState (player *p, short int dashState);
void set_player_dJump (player *p, bool dJump);
void set_player_jumpPoint (player *p, int jumpPoint);
void set_player_highPoint (player *p, int highPoint);
void set_player_state (player *p, short int state);
void set_player_pos (player *p, int pos_x, int pos_y);
void set_player_vel_x (player *p, int vel_x);
void set_player_vel_y (player *p, int vel_y);
void set_player_img (player *p, SDL_Surface *img);
short int get_player_maxhp (player p);
short int get_player_hp (player p);
short int get_player_dir (player p);
bool get_player_dash (player p);
short int get_player_dashState (player p);
bool get_player_dJump (player p);
int get_player_jumpPoint (player p);
int get_player_highPoint (player p);
short int get_player_state (player p);
SDL_Rect get_player_pos (player p);
int get_player_vel_x (player p);
int get_player_vel_y (player p);
SDL_Surface* get_player_img (player p);

#endif
