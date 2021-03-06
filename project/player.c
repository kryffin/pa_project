#include "header.h"

/* BLITTING */

void player_blit (player p, SDL_Texture *img_l, SDL_Texture *img_r, SDL_Renderer *renderer, SDL_Rect desRec) {
  if (get_player_dir(p) == 0) {
    //if the player is facing left
    set_player_img(&p, img_l);
  } else {
    //if the player is facing right
    set_player_img(&p, img_r);
  }

  SDL_RenderCopy(renderer, p.img, NULL, &(p.pos));
}

/* BEHAVIOR */

void player_melee (player p, SDL_Renderer *renderer) {

  SDL_Rect *target = NULL;
  target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  *target = get_player_pos(p);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  if (get_player_dir(p) == 0) {
    //facing left
    target->x -= IMG_WIDTH;

  } else {
    //facing right
    target->x += IMG_WIDTH;

  }

  SDL_RenderFillRect(renderer, target);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  free(target);

}

void player_apply_velocity (player *p) {
  set_player_pos(p, get_player_pos(*p).x + get_player_vel_x(*p), get_player_pos(*p).y + get_player_vel_y(*p), get_player_pos(*p).w, get_player_pos(*p).h);
  return;
}

void player_jumping (player *p) {
  if (get_player_state(*p) == 1 || get_player_state(*p) == 2) {
    if (get_player_pos(*p).y > get_player_jumpPoint(*p) - IMG_HEIGHT) {
      //currently jumping
      /*pos.y -= (pos.y - (jumpPoint - IMG_HEIGHT)) * 0.3;*/
      set_player_pos(p, get_player_pos(*p).x, get_player_pos(*p).y - (get_player_jumpPoint(*p) - IMG_HEIGHT) * 0.3, get_player_pos(*p).w, get_player_pos(*p).h);
    } else {
      //jumping ends
      set_player_highPoint(p, get_player_pos(*p).y);
      set_player_state(p, 0);
    }
  }
}

/* SET */

//create a new player
player set_player (short int maxHealthPoints, short int healthPoints, short int direction, bool doubleJump, SDL_Rect position, SDL_Rect velocity, SDL_Texture *image) {
  player p;
  set_player_maxhp(&p, maxHealthPoints);
  set_player_hp(&p, healthPoints);
  set_player_dir(&p, direction);
  set_player_dJump(&p, doubleJump);
  set_player_jumpPoint(&p, 0);
  set_player_highPoint(&p, 0);
  set_player_state(&p, 0);
  set_player_pos(&p, position.x, position.y, position.w, position.h);
  set_player_vel_x(&p, velocity.x);
  set_player_vel_y(&p, velocity.y);
  set_player_img(&p, image);

  return p;
}

//copy a target player p into player q
player set_player_copy (player p) {
  player *q = (player*)malloc(sizeof(player));
  set_player_maxhp(q, get_player_maxhp(p));
  set_player_hp(q, get_player_hp(p));
  set_player_dir(q, get_player_dir(p));
  set_player_dJump(q, get_player_dJump(p));
  set_player_vel_x(q, get_player_vel_x(p));
  set_player_vel_y(q, get_player_vel_y(p));
  set_player_img(q, get_player_img(p));

  return *q;
}

//set the player's max health points
void set_player_maxhp (player *p, short int maxhp) {
  p->maxhp = maxhp;
  return;
}

//set the player's health points
void set_player_hp (player *p, short int hp) {
  p->hp = hp;
  return;
}

//set the current direction
void set_player_dir (player *p, short int dir) {
  p->dir = dir;
  return;
}

//set the player's ability to double jump
void set_player_dJump (player *p, bool dJump) {
  p->dJump = dJump;
  return;
}

//set the player's jump point
void set_player_jumpPoint (player *p, int jumpPoint) {
  p->jumpPoint = jumpPoint;
  return;
}

//set the player's high point
void set_player_highPoint (player *p, int highPoint) {
  p->highPoint = highPoint;
  return;
}

//set the player's state
void set_player_state (player *p, short int state) {
  p->state = state;
  return;
}

//set the player's position
void set_player_pos (player *p, int pos_x, int pos_y, int pos_w, int pos_h) {
  p->pos.x = pos_x;
  p->pos.y = pos_y;
  p->pos.w = pos_w;
  p->pos.h = pos_h;
  return;
}

//set the player's x velocity
void set_player_vel_x (player *p, int vel_x) {
  p->vel.x = vel_x;
  return;
}

//set the player's y velocity
void set_player_vel_y (player *p, int vel_y) {
  p->vel.y = vel_y;
  return;
}

//set the player's image
void set_player_img (player *p, SDL_Texture *img) {
  p->img = img;
  return;
}

/* GET */

//get the player's max health points
short int get_player_maxhp (player p) {
  return p.maxhp;
}

//get the player's health points
short int get_player_hp (player p) {
  return p.hp;
}

//get the current direction
short int get_player_dir (player p) {
  return p.dir;
}

//get the player's ability to double jump
bool get_player_dJump (player p) {
  return p.dJump;
}

//get the player's jump point
int get_player_jumpPoint (player p) {
  return p.jumpPoint;
}

//get the player's high point
int get_player_highPoint (player p) {
  return p.highPoint;
}

//get the player's state
short int get_player_state (player p) {
  return p.state;
}

//get the player's position
SDL_Rect get_player_pos (player p) {
  return p.pos;
}

//get the player's x velocity
int get_player_vel_x (player p) {
  return p.vel.x;
}

//get the player's y velocity
int get_player_vel_y (player p) {
  return p.vel.y;
}

//get the player's image
SDL_Texture* get_player_img (player p) {
  return p.img;
}
