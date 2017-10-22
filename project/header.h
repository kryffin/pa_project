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
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30
#define FONT_SIZE 15
//img
#define IMG_WIDTH 32
#define IMG_HEIGHT 64
#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15
#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
//paths
#define PATH_SPRITES "./res/spritesheet.bmp"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.bmp"

#define DELAY_STEP 150 //delay for the step updating

//physics
#define JUMP_HEIGHT -10.
/* * * * * * Player Structure * * * * * */

struct IntegerPoint {
  int x;
  int y;
};

typedef struct IntegerPoint intpoint;

struct FloatPoint {
  float x;
  float y;
};

typedef struct FloatPoint floatpoint;

struct Vector {
  float x;
  float y;
};

typedef struct Vector vector;

struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction
  short int step; //step for the surrent sprite to use

  bool dJump; //is double jump available?
  int jumpPoint; //point from where you jumped
  int highPoint; //highest point of the jump (used for falling?)

  short int state; //curent state of the player
  floatpoint realPos; //position in float
  intpoint screenPos; //position in integer
  vector vel; //velocity for the player's movement
  SDL_Texture *img; //image used for displaying the player
  SDL_Rect spritePos; //position of the sprite in the sprite sheet
  SDL_Rect hitbox; //hitbox
};

typedef struct Player player;

/* * * * * * Projectile Structure * * * * * */

struct Projectile {
  floatpoint realPos;

  vector dir; //direction
  intpoint screenPos; //screen position
  SDL_Rect hitbox; //hitbox
  SDL_Rect spritePos; //position in the sprite sheet

  SDL_Texture *img; //img used
};

typedef struct Projectile projectile;

/* DIR
  0 : left
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

void block_render (block b, SDL_Surface *surface, SDL_Surface *screen);
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
void update_keyboard_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit);
void render_cursor (SDL_Texture *img, SDL_Renderer *renderer, intpoint mouse_pos);
void update_mouse_controls (SDL_Event *event, intpoint *mouse_pos, bool *mouse_btn);
void keyboard_control (player *p, SDL_Keycode *key, bool *jumped, SDL_Renderer *renderer);
void controls (SDL_Event *event, bool *quit, player *p, bool *jumped, SDL_Renderer *renderer, intpoint *mouse_pos, bool *mouse_btn, SDL_Texture *cursor, SDL_Keycode *key);

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

void level_render (level l, SDL_Surface *screen);

/* projectile.c */
void delete_projectile (projectile *p);
void shooting (bool mouse_btn, player p, projectile proj[100], intpoint mouse_pos);
void update_projectiles (projectile p[100]);
void render_projectile (projectile p[100], SDL_Renderer *renderer);
projectile set_projectile (float x, float y, vector dir, SDL_Rect hitbox, SDL_Rect spritePos, SDL_Texture *img);
void set_projectile_screen_position (projectile *p, int x, int y);
void set_projectile_real_position (projectile *p, float x, float y);
void set_projectile_direction (projectile *p, vector dir);
void set_projectile_hitbox (projectile *p, SDL_Rect hitbox);
void set_projectile_sprite_pos (projectile *p, SDL_Rect spritePos);
void set_projectile_image (projectile *p, SDL_Texture *img);
floatpoint get_projectile_real_position (projectile p);
intpoint get_projectile_screen_position (projectile p);
vector get_projectile_direction (projectile p);
SDL_Rect get_projectile_hitbox (projectile p);
SDL_Rect get_projectile_sprite_pos (projectile p);
SDL_Texture* get_projectile_image (projectile p);

/* player.h */

floatpoint calcul_position (player p, float v_x, float v_y, float timeN);
float player_jumping_y (player p, Uint32 timeN);
float player_jumping_x (player p, Uint32 timeN);
void player_jumping (player *p, Uint32 timeN_A,Uint32 timeN_B);
void player_gravity(player *p);
void player_colision (player *p);


void update_player (player *p);
void render_player (player p, SDL_Renderer *renderer, intpoint mouse_pos);
void player_melee (player p, SDL_Renderer *renderer);
void player_update_step(player *p);
void player_update_dir (player *p, intpoint mouse_pos);
void player_apply_velocity (player *p);
player set_player (short int maxHealthPoints, floatpoint position, vector velocity, SDL_Texture *image, SDL_Rect posSprite, SDL_Rect hitbox);
void set_player_maxhp (player *p, short int maxhp);
void set_player_hp (player *p, short int hp);
void set_player_dir (player *p, short int dir);
void set_player_step (player *p, short int step);
void set_player_dJump (player *p, bool dJump);
void set_player_jumpPoint (player *p, int jumpPoint);
void set_player_highPoint (player *p, int highPoint);
void set_player_state (player *p, short int state);
void set_player_real_position (player *p, float x, float y);
void set_player_screen_position (player *p, int x, int y);
void set_player_vel_x (player *p, float x);
void set_player_vel_y (player *p, float y);
void set_player_img (player *p, SDL_Texture *img);
void set_player_sprite_pos (player *p, SDL_Rect posSprite);
void set_player_hitbox (player *p, SDL_Rect hitbox);

short int get_player_maxhp (player p);
short int get_player_hp (player p);
short int get_player_dir (player p);
short int get_player_step (player p);
bool get_player_dJump (player p);
int get_player_jumpPoint (player p);
int get_player_highPoint (player p);
short int get_player_state (player p);
floatpoint get_player_real_position (player p);
intpoint get_player_screen_position (player p);
vector get_player_velocity (player p);
SDL_Texture* get_player_img (player p);
SDL_Rect get_player_sprite_pos (player p);
SDL_Rect get_player_hitbox (player p);
bool is_colision (player *p);

/* var_init.c */

int init_palette (SDL_Color **palette);
int init_font (TTF_Font **font);
int init_window (SDL_Window **window);
int init_renderer (SDL_Renderer **renderer, SDL_Window *window);
int init_sdl (SDL_Window **window, SDL_Renderer **renderer);
int init_images (SDL_Surface **temp, SDL_Texture **playerSprite, SDL_Texture **cursor, SDL_Renderer *renderer);
int init_projectiles (projectile *projectiles[100], SDL_Texture *img);
int init_variables (Uint32 **initTimer, FPSmanager **manager, SDL_Window **window, SDL_Renderer **renderer, intpoint **mouse_pos, SDL_Event **event, bool **jumped, bool **mouse_btn, int **i, TTF_Font **font, SDL_Color **palette, player **p, projectile **projectiles, int **stepDelay, bool **quit, SDL_Surface **temp, SDL_Texture **playerSprite, SDL_Texture **cursor, Uint32 **timeN_A, Uint32 **timeN_B);
void free_variables (SDL_Surface *msgState, SDL_Surface *msgJump, SDL_Texture *playerSprite, SDL_Texture *tempTxt, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font, int *i, projectile *projectiles, player *p, FPSmanager *manager, SDL_Color *colorPalette, char *strState, char *strJump, SDL_Rect *posMsgState, SDL_Rect *posMsgJump, SDL_Event *event, bool *quit, bool *jumped, intpoint *mouse_pos, bool *mouse_btn);

/* menu.c */

int menu_controls(SDL_Event *event, intpoint *mouse_pos);
int main_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint *mouse_pos, SDL_Texture *playerSprite);
bool mouse_hover_menu (intpoint mouse_pos, int targetx, int targety, int width, int height);
int option_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint *mouse_pos, SDL_Texture *playerSprite);
int render_menu (bool *quit, TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint *mouse_pos, SDL_Texture *cursor);

/* vector.c */

vector normalize (vector v);
vector vector_direction (SDL_Rect a, SDL_Rect b);
float vector_length (vector v);
vector set_vector (float x, float y);
void set_vector_x (vector *v, float x);
void set_vector_y (vector *v, float y);
float get_vector_x (vector v);
float get_vector_y (vector v);

/* 2dpoint.c */

floatpoint set_floatpoint (float x, float y);
void set_floatpoint_x (floatpoint *p, float x);
void set_floatpoint_y (floatpoint *p, float y);
intpoint set_intpoint (int x, int y);
void set_intpoint_x (intpoint *p, int x);
void set_intpoint_y (intpoint *p, int y);
float get_floatpoint_x (floatpoint p);
float get_floatpoint_y (floatpoint p);
int get_intpoint_x (intpoint p);
int get_intpoint_y (intpoint p);

#endif
