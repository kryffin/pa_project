#ifndef PLAYER_H
#define PLAYER_H

enum PlayerDirection {
  Left,
  Right
};

enum PlayerState {
  Walking,
  Jumping,
  nouse,
  Attacking,
  Crouching
};

typedef struct Player {
  short int maxhp; //max health points
  short int hp; //current health points
  short int dir; //current direction+-
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

/* player_t.c */
void player_jumping (player_t *p);
void player_gravity(player_t *p);
void update_player (player_t *p, bool *quit);
void update_enemy (player_t *p);
void render_player (player_t p, SDL_Renderer *renderer, intpoint_t mouse_pos);
void player_melee (player_t p, SDL_Renderer *renderer);
void player_update_step(player_t *p);
void player_update_dir (player_t *p, intpoint_t mouse_pos);
void player_apply_velocity (player_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]);
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

#endif
