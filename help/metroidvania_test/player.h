#ifndef _PLAYER_H_
#define _PLAYER_H_

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
bool get_player_dashState (player p);
bool get_player_dJump (player p);
int get_player_jumpPoint (player p);
int get_player_highPoint (player p);
short int get_player_state (player p);
SDL_Rect get_player_pos (player p);
int get_player_vel_x (player p);
int get_player_vel_y (player p);
SDL_Surface get_player_img (player p);

#endif
