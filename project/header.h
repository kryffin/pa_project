#ifndef _HEADER_H_
#define _HEADER_H_

/* INCLUDES */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* CONSTANTS */

//window
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30
#define SCREEN_BPP 32
#define SCREEN_FPS 30
#define FONT_SIZE 15
//img
#define IMG_WIDTH 32
#define IMG_HEIGHT 64
#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16
#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15
#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10
#define BULLET_SPEED_SG 5
//paths
#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define PATH_TXT_FILE1 "./res/arena2.txt"
#define PATH_TXT_FILE2 "./res/arena3.txt"
#define PATH_TXT_FILE3 "./res/arena4.txt"
#define PATH_TXT_FILE4 "./res/arena5.txt"
#define PATH_TXT_FILE5 "./res/arena6.txt"

#define DELAY_STEP 150 //delay for the step updating

//player
#define JUMP_HEIGHT -14
/* * * * * * Player Structure * * * * * */


typedef struct IntegerPoint {
  int x;
  int y;
} intpoint;

typedef struct FloatPoint {
  float x;
  float y;
} floatpoint;

typedef struct Vector {
  float x;
  float y;
} vector;

typedef struct AABB {
  floatpoint HG;
  floatpoint HD;
  floatpoint BG;
  floatpoint BD;
  vector size;
  floatpoint middle;
}AABB;


typedef struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction
  short int step; //step for the surrent sprite to use
  short int gunType; //type of the gun the player holds

  bool dJump; //is double jump available?
  int currLevel;
  int jumpPoint; //point from where you jumped
  int highPoint; //highest point of the jump (used for falling?)

  bool enableGravity;
  short int state; //curent state of the player
  floatpoint realPos; //position in float
  intpoint screenPos; //position in integer
  vector vel; //velocity for the player's movement
  SDL_Texture *img; //image used for displaying the player
  SDL_Rect spritePos; //position of the sprite in the sprite sheet
  SDL_Rect hitbox; //hitbox
} player;

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

/* * * * * * Projectile Structure * * * * * */
typedef struct Projectile {
  floatpoint realPos;

  vector dir; //direction
  intpoint screenPos; //screen position
  SDL_Rect hitbox; //hitbox
  SDL_Rect spritePos; //position in the sprite sheet

  SDL_Texture *img; //img used
} projectile;

/* blocks.h */

typedef struct Block {

  SDL_Rect hitbox; //hitbox of the block
  SDL_Rect spritesheet_pos; //position on the spritesheet
  unsigned short int type; //type of the block
  AABB box;

} block;

/* TYPE:
  0 : solid
  1 : walkable background
  2 : walkable foreground
  3 : blank
*/

typedef struct Level {

  block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]; //all the blocks of the level

  SDL_Texture *blocks_spritesheet; //spritesheet of the blocks
  SDL_Texture *background; //background of the level

} level;

typedef struct list_level *list_l;

struct list_level {
  level* head;
  list_l next;

};

/* blocks.c */
block set_block (SDL_Rect hitbox, SDL_Rect spritesheet_pos, unsigned short int type);
void set_block_hitbox (block *b, int x, int y, int w, int h);
void set_block_spritesheet_position (block *b, int x, int y, int w, int h);
void set_block_type (block *b, unsigned short int type);
SDL_Rect get_block_hitbox (block b);
SDL_Rect get_block_spritesheet_position (block b);
unsigned short int get_block_type (block b);

/* controls.c */
void update_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit, intpoint *mouse_pos, bool *mouse_btn);
void render_cursor (SDL_Texture *img, SDL_Renderer *renderer, intpoint mouse_pos);
void keyboard_control (player *p, SDL_Keycode *key, bool *jumped);
void controls (SDL_Event *event, bool *quit, player *p, bool *jumped, SDL_Renderer *renderer, intpoint *mouse_pos, bool *mouse_btn, SDL_Texture *cursor, SDL_Keycode *key);

/* level.c */
void rendering (player *player, projectile bullets[100], SDL_Texture *cursor, level currLevel, intpoint *mouse_pos, SDL_Renderer *renderer);
void render_foreground_level (level l, SDL_Renderer *renderer);
void render_background_level (level l, SDL_Renderer *renderer);
level init_level (SDL_Texture *blocks_spritesheet, SDL_Texture *background, player *p, int X);
level set_level (block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], SDL_Texture *blocks_spritesheet, SDL_Texture *background);
void set_level_block (level *l, int x, int y, block b);
void set_level_blocks_spritesheet (level *l, SDL_Texture *blocks_spritesheet);
void set_level_background (level *l, SDL_Texture *background);
block get_level_block (level l, int x, int y);
SDL_Texture *get_level_blocks_spritesheet (level l);
SDL_Texture *get_level_background (level l);

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

vector calcul_vector_p_m (vector dir, intpoint mouse_pos);

/* player.c */
//temporaire a enlever
floatpoint calcul_position (player p, float v_init, floatpoint pos_init, float angle, Uint32 timeN);

void player_jumping (player *p, Uint32 timeN_A, Uint32 timeN_B);
void player_gravity(player *p);


//////////////////////////////////
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

/* var_init.c */
int init_palette (SDL_Color **palette);
int init_font (TTF_Font **font);
int init_window (SDL_Window **window);
int init_renderer (SDL_Renderer **renderer, SDL_Window *window);
int init_sdl (SDL_Window **window, SDL_Renderer **renderer);
int init_images (SDL_Surface **temp, SDL_Texture **playerSprite, SDL_Texture **cursor, SDL_Texture **blocks_spritesheet, SDL_Texture **background, SDL_Renderer *renderer);
int init_projectiles (projectile *projectiles[100], SDL_Texture *img);
int init_variables (Uint32 **initTimer, FPSmanager **manager, SDL_Window **window, SDL_Renderer **renderer, intpoint **mouse_pos, SDL_Event **event, bool **jumped, bool **mouse_btn, int **i, TTF_Font **font, SDL_Color **palette, player **p, projectile **projectiles, int **stepDelay, bool **quit, SDL_Surface **temp, SDL_Texture **playerSprite, SDL_Texture **cursor, Uint32 **timeN_A, Uint32 **timeN_B, level **currLevel, SDL_Texture **blocks_spritesheet, SDL_Texture **background);
void free_variables (SDL_Surface *msgState, SDL_Surface *msgJump, SDL_Texture *playerSprite, SDL_Texture *tempTxt, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font, int *i, projectile *projectiles, player *p, FPSmanager *manager, SDL_Color *colorPalette, char *strState, char *strJump, SDL_Rect *posMsgState, SDL_Rect *posMsgJump, SDL_Event *event, bool *quit, bool *jumped, intpoint *mouse_pos, bool *mouse_btn, Uint32 *timeN_A, Uint32 *timeN_B, level *currLevel, SDL_Texture *blocks_spritesheet, SDL_Texture *background, int *stepDelay);

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

//aabb.c
floatpoint get_aabb_HG (AABB box);
floatpoint get_aabb_HD (AABB box);
floatpoint get_aabb_BG (AABB box);
floatpoint get_aabb_BD (AABB box);
floatpoint get_aabb_middle (AABB box);
vector get_aabb_size (AABB box);

void set_aabb_HG (AABB *box, floatpoint hg);
void set_aabb_HD (AABB *box, floatpoint hd);
void set_aabb_BG (AABB *box, floatpoint bg);
void set_aabb_BD (AABB *box, floatpoint bd);
void set_aabb_middle (AABB *box, floatpoint middlePoint);
void set_aabb_size (AABB *box, vector size);


void correct_position (player *p, level l, unsigned int i, unsigned int j, int x, int y);
bool check_collision_bb( SDL_Rect A, SDL_Rect B);
bool is_colision(player *p, level* l);
void player_colision (player *p, level* l);
bool point_dans_aabb (floatpoint realpos, AABB world);
void adjust_vector_collision(vector V, player *hero, AABB box, double eps);



//list_level.c
list_l list_l_empty();
list_l cons_list_l (level* lvl, list_l liste);
level* head_list_l (list_l liste);
list_l next_list_l (list_l liste);
bool is_empty_list_l (list_l L);
#endif
