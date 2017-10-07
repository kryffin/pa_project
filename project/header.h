#ifndef _HEADER_H_
#define _HEADER_H_

/* INCLUDES */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <stdbool.h>
#include <math.h>

/* CONSTANTS */

//window
#define SCREEN_BPP 32
#define SCREEN_FPS 30
#define FONT_SIZE 15
//img
#define IMG_WIDTH 32
#define IMG_HEIGHT 64
//paths
#define PATH_SPRITES "./res/spritesheet.bmp"
#define PATH_FONT "./res/font.ttf"
//physics
#define COEF_A 0.25
#define COEF_B 0.
#define COEF_C 100.
#define C_VEL_L -3
#define C_VEL_R 3
#define G 0.008 //m.s^-2
#define GRAVITY 5
#define ANGLE_SAUT 45

struct Vector {
  float x;
  float y;
};

typedef struct Vector vector;

struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction

  bool dJump; //is double jump available?


  short int state; //curent state of the player
  //newton
  SDL_Rect posAbs; //position of the origin (top left) (absolute)
  vector posRel; //position of the sprite in the new repere
  vector vel; //velocity for the player's movement
  // vector centreMass; //centre de la masse du l'entité
  vector jumpPoint; //point from where you jumped
  vector highPoint; //highest point of the jump (used for falling?)

  SDL_Texture *img; //image used for displaying the player
  SDL_Rect spritePos; //sprite position in the sprite in the sheet
};

typedef struct Player player;

/* DIR
  -1 : left
  1 : right
*/

/* STATE
  0 : walking / normal
  1 : jumping
  2 : double-jumping
  3 : attacking
  4 : crouching
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
void update_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit);
void control (player *p, SDL_Keycode *key, bool *jumped, SDL_Renderer *renderer, SDL_Rect *display);

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

void player_blit (player p, SDL_Texture *img, SDL_Renderer *renderer);
void player_melee (player p, SDL_Renderer *renderer);
void player_apply_velocity (player *p, Uint32* timeN_A, Uint32* timeN_B);
void player_jumping_v2 (player *p, Uint32 timeN_A, Uint32 timeN_B);
void player_gravity (player* p);
void player_colision (player *p, SDL_Rect* display);
player set_player (short int maxHealthPoints, short int healthPoints, short int direction, bool doubleJump, SDL_Rect position, SDL_Rect velocity, SDL_Texture *image, SDL_Rect posSprite);
player set_player_copy (player p);
void set_player_maxhp (player *p, short int maxhp);
void set_player_hp (player *p, short int hp);
void set_player_dir (player *p, short int dir);
void set_player_dJump (player *p, bool dJump);
void set_player_jumpPoint (player *p, vector jumpPoint);
void set_player_highPoint (player *p, vector highPoint);
void set_player_state (player *p, short int state);
void set_player_posAbs (player *p, int posA_x, int posA_y, int posA_w, int posA_h);
void set_player_posRel (player *p, int posR_x, int posR_y);
void set_player_vel_x (player *p, int vel_x);
void set_player_vel_y (player *p, int vel_y);
void set_player_img (player *p, SDL_Texture *img);
void set_player_sprite_pos (player *p, SDL_Rect posSprite);
//void set_player_absolute_pos (player*p, SDL_Rect absPos);
short int get_player_maxhp (player p);
short int get_player_hp (player p);
short int get_player_dir (player p);
bool get_player_dJump (player p);
vector get_player_jumpPoint (player p);
vector get_player_highPoint (player p);
short int get_player_state (player p);
SDL_Rect get_player_posAbs (player p);
vector get_player_posRel (player p);
vector calcul_position (player p, float v_init, vector pos_init, float angle, unsigned short int time);
int get_player_vel_x (player p);
int get_player_vel_y (player p);
SDL_Texture* get_player_img (player p);
SDL_Rect get_player_sprite_pos (player p);
//SDL_Rect get_player_absolute_pos (player p);
int menu_controls(SDL_Event *event, int *mousex, int *mousey);
int main_menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer, int *mousex, int *mousey, SDL_Rect *display);
bool mouse_hover_menu (int mousex, int mousey, int targetx, int targety, int width, int height);
int option_menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer, int *mousex, int *mousey, SDL_Rect *display);

#endif
