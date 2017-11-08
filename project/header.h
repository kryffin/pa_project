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
#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15
#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10
//paths
#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define PATH_TXT_FILE "./res/arena.txt"
#define PATH_YOU_DIED "./res/you_died.png"
//delays
#define PLAYER_SHOOT_DELAY 100
#define ENEMY_SHOOT_DELAY 500

#define DELAY_STEP 150 //delay for the step updating

#define JUMP_HEIGHT -24
#define GRAVITY 4

/* * * * * * Player Structure * * * * * */

typedef struct IntegerPoint {
  int x;
  int y;
} intpoint_t;

typedef struct FloatPoint_t {
  float x;
  float y;
} floatpoint_t;

typedef struct Vector {
  float x;
  float y;
} vector_t;

typedef struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction
  short int step; //step for the surrent sprite to use

  bool onGround; //is the player on a ground?
  int jumpPoint; //point from where you jumped
  int highPoint; //highest point of the jump (used for falling?)

  short int state; //curent state of the player_t
  floatpoint_t realPos; //position in float
  intpoint_t screenPos; //position in integer
  vector_t vel; //velocity for the player_t's movement
  SDL_Texture *img; //image used for displaying the player_t
  SDL_Rect spritePos; //position of the sprite in the sprite sheet
  SDL_Rect hitbox; //hitbox

} player_t;

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
  floatpoint_t realPos;

  vector_t dir; //direction
  intpoint_t screenPos; //screen position
  SDL_Rect hitbox; //hitbox
  SDL_Rect spritePos; //position in the sprite sheet

  SDL_Texture *img; //img used
} projectile;

/* blocks.h */

typedef struct Block {

  SDL_Rect hitbox; //hitbox of the block
  SDL_Rect spritesheet_pos; //position on the spritesheet

  unsigned short int type; //type of the block

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

/* blocks.c */
block set_block (SDL_Rect hitbox, SDL_Rect spritesheet_pos, unsigned short int type);
void set_block_hitbox (block *b, int x, int y, int w, int h);
void set_block_spritesheet_position (block *b, int x, int y, int w, int h);
void set_block_type (block *b, unsigned short int type);
SDL_Rect get_block_hitbox (block b);
SDL_Rect get_block_spritesheet_position (block b);
unsigned short int get_block_type (block b);

/* controls.c */
void update_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit, intpoint_t *mouse_pos, bool *mouse_btn);
void render_cursor (SDL_Texture *img, SDL_Renderer *renderer, intpoint_t mouse_pos);
void keyboard_control (player_t *p, SDL_Keycode *key, bool *jumped);
void controls (SDL_Event *event, bool *quit, player_t *p, bool *jumped, intpoint_t *mouse_pos, bool *mouse_btn, SDL_Keycode *key);

/* level.c */
void closest_out (player_t *player, int w, int h);
bool collision_intpoint (intpoint_t a, intpoint_t b);
bool colision (player_t player, block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], int *width, int *height);
void game_over (SDL_Renderer *renderer);
void rendering (player_t *player, player_t enemies[10], projectile bullets[100], projectile enemyProjectiles[100], SDL_Texture *cursor, level currLevel, intpoint_t *mouse_pos, SDL_Renderer *renderer);
void render_foreground_level (level l, SDL_Renderer *renderer);
void render_background_level (level l, SDL_Renderer *renderer);
level init_level (SDL_Texture *blocks_spritesheet, SDL_Texture *background, player_t *p, player_t enemies[10]);
level set_level (block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], SDL_Texture *blocks_spritesheet, SDL_Texture *background);
void set_level_block (level *l, int x, int y, block b);
void set_level_blocks_spritesheet (level *l, SDL_Texture *blocks_spritesheet);
void set_level_background (level *l, SDL_Texture *background);
block get_level_block (level l, int x, int y);
SDL_Texture *get_level_blocks_spritesheet (level l);
SDL_Texture *get_level_background (level l);

/* projectile.c */
void delete_projectile (projectile *p);
void shooting (bool mouse_btn, player_t p, projectile proj[100], intpoint_t mouse_pos);
void update_projectiles (projectile p[100]);
void render_projectile (projectile p[100], SDL_Renderer *renderer);
projectile set_projectile (float x, float y, vector_t dir, SDL_Rect hitbox, SDL_Rect spritePos, SDL_Texture *img);
void set_projectile_screen_position (projectile *p, int x, int y);
void set_projectile_real_position (projectile *p, float x, float y);
void set_projectile_direction (projectile *p, vector_t dir);
void set_projectile_hitbox (projectile *p, SDL_Rect hitbox);
void set_projectile_sprite_pos (projectile *p, SDL_Rect spritePos);
void set_projectile_image (projectile *p, SDL_Texture *img);
floatpoint_t get_projectile_real_position (projectile p);
intpoint_t get_projectile_screen_position (projectile p);
vector_t get_projectile_direction (projectile p);
SDL_Rect get_projectile_hitbox (projectile p);
SDL_Rect get_projectile_sprite_pos (projectile p);
SDL_Texture* get_projectile_image (projectile p);

/* player_t.c */
void player_jumping (player_t *p, Uint32 timeN_A, Uint32 timeN_B);
void player_gravity(player_t *p);

void update_player (player_t *p, bool *quit);
void update_enemy (player_t *p);
void render_player (player_t p, SDL_Renderer *renderer, intpoint_t mouse_pos);
void player_melee (player_t p, SDL_Renderer *renderer);
void player_update_step(player_t *p);
void player_update_dir (player_t *p, intpoint_t mouse_pos);
void player_apply_velocity (player_t *p, block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);
bool is_alive(player_t p);
player_t set_player (short int maxHealthPoints, floatpoint_t position, vector_t velocity, SDL_Texture *image, SDL_Rect posSprite, SDL_Rect hitbox);
void set_player_maxhp (player_t *p, short int maxhp);
void set_player_hp (player_t *p, short int hp);
void set_player_dir (player_t *p, short int dir);
void set_player_step (player_t *p, short int step);
void set_player_on_ground (player_t *p, bool onGround);
void set_player_jumpPoint (player_t *p, int jumpPoint);
void set_player_highPoint (player_t *p, int highPoint);
void set_player_state (player_t *p, short int state);
void set_player_real_position (player_t *p, float x, float y);
void set_player_screen_position (player_t *p, int x, int y);
void set_player_vel_x (player_t *p, float x);
void set_player_vel_y (player_t *p, float y);
void set_player_img (player_t *p, SDL_Texture *img);
void set_player_sprite_pos (player_t *p, SDL_Rect posSprite);
void set_player_hitbox (player_t *p, SDL_Rect hitbox);

short int get_player_maxhp (player_t p);
short int get_player_hp (player_t p);
short int get_player_dir (player_t p);
short int get_player_step (player_t p);
bool get_player_on_ground (player_t p);
int get_player_jumpPoint (player_t p);
int get_player_highPoint (player_t p);
short int get_player_state (player_t p);
floatpoint_t get_player_real_position (player_t p);
intpoint_t get_player_screen_position (player_t p);
vector_t get_player_velocity (player_t p);
SDL_Texture* get_player_img (player_t p);
SDL_Rect get_player_sprite_pos (player_t p);
SDL_Rect get_player_hitbox (player_t p);

/* var_init.c */
int init_palette (SDL_Color **palette);
int init_font (TTF_Font **font);
int init_window (SDL_Window **window);
int init_renderer (SDL_Renderer **renderer, SDL_Window *window);
int init_sdl (SDL_Window **window, SDL_Renderer **renderer);
int init_images (SDL_Surface **temp, SDL_Texture **player_tSprite, SDL_Texture **cursor, SDL_Texture **blocks_spritesheet, SDL_Texture **background, SDL_Renderer *renderer);
int init_projectiles (projectile *projectiles[100], SDL_Texture *img, int x, int y);
int init_variables (Uint32 **initTimer, FPSmanager **manager, SDL_Window **window, SDL_Renderer **renderer, intpoint_t **mouse_pos, SDL_Event **event, bool **jumped, bool **mouse_btn, int **i, TTF_Font **font, SDL_Color **palette, player_t **p, projectile **projectiles, int **stepDelay, bool **quit, SDL_Surface **temp, SDL_Texture **player_tSprite, SDL_Texture **cursor, Uint32 **timeN_A, Uint32 **timeN_B, level **currLevel, SDL_Texture **blocks_spritesheet, SDL_Texture **background, player_t **enemies, projectile **enemyProjectiles);
void free_variables (SDL_Texture *player_tSprite, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font, int *i, projectile *projectiles, player_t *p, FPSmanager *manager, SDL_Color *colorPalette, SDL_Event *event, bool *quit, bool *jumped, intpoint_t *mouse_pos, bool *mouse_btn, Uint32 *timeN_A, Uint32 *timeN_B, level *currLevel, SDL_Texture *blocks_spritesheet, SDL_Texture *background, int *stepDelay, player_t *enemies, projectile *enemyProjectiles);

/* menu.c */
void render_text(char *string, SDL_Rect pos, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);
int menu_controls(SDL_Event *event, intpoint_t *mouse_pos);
int main_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *player_tSprite);
bool mouse_hover_menu (intpoint_t mouse_pos, int targetx, int targety, int width, int height);
int option_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *player_tSprite);
int render_menu (bool *quit, TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *cursor);

/* vector.c */
vector_t normalize (vector_t v);
vector_t vector_direction (SDL_Rect a, SDL_Rect b);
float vector_length (vector_t v);
vector_t set_vector (float x, float y);
void set_vector_x (vector_t *v, float x);
void set_vector_y (vector_t *v, float y);
float get_vector_x (vector_t v);
float get_vector_y (vector_t v);

/* 2dpoint.c */
floatpoint_t set_floatpoint (float x, float y);
void set_floatpoint_x (floatpoint_t *p, float x);
void set_floatpoint_y (floatpoint_t *p, float y);
intpoint_t set_intpoint (int x, int y);
void set_intpoint_x (intpoint_t *p, int x);
void set_intpoint_y (intpoint_t *p, int y);
float get_floatpoint_x (floatpoint_t p);
float get_floatpoint_y (floatpoint_t p);
int get_intpoint_x (intpoint_t p);
int get_intpoint_y (intpoint_t p);

#endif
