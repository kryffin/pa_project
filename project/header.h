#ifndef _HEADER_H_
#define _HEADER_H_

/* INCLUDES */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <stdbool.h>

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
//paths
#define PATH_SPRITES "./res/spritesheet.bmp"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.bmp"

#define DELAY_STEP 150 //delay for the step updating

/* * * * * * Player Structure * * * * * */

struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction
  short int step; //step for the surrent sprite to use

  bool dJump; //is double jump available?
  int jumpPoint; //point from where you jumped
  int highPoint; //highest point of the jump (used for falling?)

  short int state; //curent state of the player
  SDL_Rect pos; //position of the origin (top left)
  SDL_Rect vel; //velocity for the player's movement
  SDL_Texture *img; //image used for displaying the player
  SDL_Rect spritePos;
};

typedef struct Player player;

/* * * * * * Projectile Structure * * * * * */

struct Projectile {
  float realPosX; //real x position
  float realPosY; //real y position

  SDL_Rect dir; //direction (vector)
  SDL_Rect pos; //screen position

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
void render_cursor (SDL_Texture *img, SDL_Renderer *renderer, SDL_Rect mouse_pos);
void update_mouse_controls (SDL_Event *event, SDL_Rect *mouse_pos, bool *mouse_btn);
void keyboard_control (player *p, SDL_Keycode *key, bool *jumped, SDL_Renderer *renderer);
void controls (SDL_Event *event, bool *quit, player *p, bool *jumped, SDL_Renderer *renderer, SDL_Rect *mouse_pos, bool *mouse_btn, SDL_Texture *cursor, SDL_Keycode *key);

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

void init_projectile (bool mouse_btn, player p, SDL_Texture *spriteSheet, projectile proj[100], SDL_Rect mouse_pos);
void render_projectile (projectile p[100], SDL_Renderer *renderer);
projectile set_projectile (float realPosX, float realPosY, SDL_Rect dir, SDL_Rect pos, SDL_Texture *img);
void set_projectile_real_position_x (projectile *p, float realPosX);
void set_projectile_real_position_y (projectile *p, float realPosY);
void set_projectile_direction (projectile *p, SDL_Rect dir);
void set_projectile_position (projectile *p, SDL_Rect pos);
void set_projectile_image (projectile *p, SDL_Texture *img);
float get_projectile_real_position_x (projectile p);
float get_projectile_real_position_y (projectile p);
SDL_Rect get_projectile_direction (projectile p);
SDL_Rect get_projectile_position (projectile p);
SDL_Texture* get_projectile_image (projectile p);

/* player.h */

void render_player (player p, SDL_Renderer *renderer, SDL_Rect mouse_pos);
void player_melee (player p, SDL_Renderer *renderer);
void player_update_step(player *p);
void player_update_dir (player *p, SDL_Rect mouse_pos);
void player_apply_velocity (player *p);
void player_jumping (player *p);
player set_player (short int maxHealthPoints, short int healthPoints, short int direction, bool doubleJump, SDL_Rect position, SDL_Rect velocity, SDL_Texture *image, SDL_Rect posSprite);
player set_player_copy (player p);
void set_player_maxhp (player *p, short int maxhp);
void set_player_hp (player *p, short int hp);
void set_player_dir (player *p, short int dir);
void set_player_step (player *p, short int step);
void set_player_dJump (player *p, bool dJump);
void set_player_jumpPoint (player *p, int jumpPoint);
void set_player_highPoint (player *p, int highPoint);
void set_player_state (player *p, short int state);
void set_player_pos (player *p, int pos_x, int pos_y, int pos_w, int pos_h);
void set_player_vel_x (player *p, int vel_x);
void set_player_vel_y (player *p, int vel_y);
void set_player_img (player *p, SDL_Texture *img);
void set_player_sprite_pos (player *p, SDL_Rect posSprite);
short int get_player_maxhp (player p);
short int get_player_hp (player p);
short int get_player_dir (player p);
short int get_player_step (player p);
bool get_player_dJump (player p);
int get_player_jumpPoint (player p);
int get_player_highPoint (player p);
short int get_player_state (player p);
SDL_Rect get_player_pos (player p);
int get_player_vel_x (player p);
int get_player_vel_y (player p);
SDL_Texture* get_player_img (player p);
SDL_Rect get_player_sprite_pos (player p);

int init_palette (SDL_Color **palette);
int init_font (TTF_Font **font);
int init_window (SDL_Window **window);
int init_renderer (SDL_Renderer **renderer, SDL_Window *window);
int init_sdl (SDL_Window **window, SDL_Renderer **renderer);
int init_images (SDL_Surface **temp, SDL_Texture **playerSprite, SDL_Texture **cursor, SDL_Renderer *renderer);
int init_variables (Uint32 **initTimer, FPSmanager **manager, SDL_Window **window, SDL_Renderer **renderer, SDL_Rect **mouse_pos, SDL_Event **event, bool **jumped, bool **mouse_btn, int **i, TTF_Font **font, SDL_Color **palette, player **p, projectile **projectiles, int **stepDelay, bool **quit, SDL_Surface **temp, SDL_Texture **playerSprite, SDL_Texture **cursor);
void free_variables (SDL_Surface *msgState, SDL_Surface *msgJump, SDL_Texture *playerSprite, SDL_Texture *tempTxt, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font, int *i, projectile *projectiles, player *p, FPSmanager *manager, SDL_Color *colorPalette, char *strState, char *strJump, SDL_Rect *posMsgState, SDL_Rect *posMsgJump, SDL_Event *event, bool *quit, bool *jumped, SDL_Rect *mouse_pos, bool *mouse_btn);

int menu_controls(SDL_Event *event, SDL_Rect *mouse_pos);
int main_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, SDL_Rect *mouse_pos, SDL_Texture *playerSprite);
bool mouse_hover_menu (SDL_Rect mouse_pos, int targetx, int targety, int width, int height);
int option_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, SDL_Rect *mouse_pos, SDL_Texture *playerSprite);
int render_menu (bool *quit, TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, SDL_Rect *mouse_pos, SDL_Texture *cursor);

#endif
