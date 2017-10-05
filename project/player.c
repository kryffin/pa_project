#include "header.h"

/* renderTING */

void player_render (player p, SDL_Texture *img, SDL_Renderer *renderer, SDL_Rect mouse_pos) {

  SDL_Rect *temp = NULL;
  temp = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  temp->w = 32;
  temp->h = 64;

  if (get_player_dir(p) == 1) {
    //player facing right

    switch (get_player_state(p)) {

      //stand-by/walking
      case 0:

        if (get_player_vel_x(p) == 0 && get_player_vel_y(p) == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 0;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          switch (get_player_step(p)) {

            case 0:
              temp->x = 32;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            case 1:
              temp->x = 0;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            case 2:
              temp->x = 64;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            case 3:
              temp->x = 0;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            default:
              break;

          }

        }

        break;

      //jumping or double-jumping
      case 1:
      case 2:

      temp->x = 96;
      temp->y = 0;
      set_player_sprite_pos(&p, *temp);

        break;

      //attacking
      case 3:

      temp->x = 64;
      temp->y = 128;
      set_player_sprite_pos(&p, *temp);

        break;

      //crouching
      case 4:

        temp->x = 128;
        temp->y = 0;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  } else {
    //player facing left

    switch (get_player_state(p)) {

      //stand-by/walking
      case 0:

        if (get_player_vel_x(p) == 0 && get_player_vel_y(p) == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 64;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          switch (get_player_step(p)) {

            case 0:
              temp->x = 32;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            case 1:
              temp->x = 0;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            case 2:
              temp->x = 64;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            case 3:
              temp->x = 0;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            default:
              break;

          }

        }

        break;

      //jumping or double-jumping
      case 1:
      case 2:

      temp->x = 96;
      temp->y = 64;
      set_player_sprite_pos(&p, *temp);

        break;

      //attacking
      case 3:

      temp->x = 96;
      temp->y = 128;
      set_player_sprite_pos(&p, *temp);

        break;

      //crouching
      case 4:

        temp->x = 128;
        temp->y = 64;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  }

  SDL_RenderCopy(renderer, p.img, &(p.spritePos), &(p.pos));

  free(temp);
}

/* BEHAVIOR */

void player_melee (player p, SDL_Renderer *renderer) {

  SDL_Rect *target = NULL;
  target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  *target = get_player_pos(p);

  SDL_Rect *effect = NULL;
  effect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  effect->y = 128;
  effect->w = 32;
  effect->h = 64;

  if (get_player_dir(p) == 0) {
    //facing left
    target->x -= IMG_WIDTH;
    effect->x = 32;

  } else {
    //facing right
    target->x += IMG_WIDTH;
    effect->x = 0;

  }

  SDL_RenderCopy(renderer, p.img, effect, target);

  free(target);
  free(effect);

}

void player_update_step (player *p) {

  if(get_player_vel_x(*p) != 0) {

    set_player_step(p, get_player_step(*p) + 1);

    if(get_player_step(*p) == 4) {

      set_player_step(p, 0);

    }

  }

}

void player_update_dir (player *p, SDL_Rect mouse_pos) {

  if(get_player_pos(*p).x + (IMG_WIDTH / 2) < mouse_pos.x) {
    set_player_dir(p, 1); //right
  } else {
    set_player_dir(p, 0); //left
  }

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
      set_player_pos(p, get_player_pos(*p).x, get_player_pos(*p).y - (get_player_jumpPoint(*p) - IMG_HEIGHT) * 1, get_player_pos(*p).w, get_player_pos(*p).h);
    } else {
      //jumping ends
      set_player_highPoint(p, get_player_pos(*p).y);
      set_player_state(p, 0);
    }
  }
}

/* SET */

//create a new player
player set_player (short int maxHealthPoints, short int healthPoints, short int direction, bool doubleJump, SDL_Rect position, SDL_Rect velocity, SDL_Texture *image, SDL_Rect posSprite) {
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
  set_player_sprite_pos(&p, posSprite);

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

//set the step
void set_player_step (player *p, short int step) {
  p->step = step;
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

//set the player sprite position on the spritesheet
void set_player_sprite_pos (player *p, SDL_Rect posSprite) {
  p->spritePos = posSprite;
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

//get the step
short int get_player_step (player p) {
  return p.step;
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

//get the player's sprite position on the sprite sheet
SDL_Rect get_player_sprite_pos (player p) {
  return p.spritePos;
}
