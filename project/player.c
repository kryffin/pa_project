#include "header.h"

/* renderTING */

void update_player (player *p) {

  set_player_screen_position(p, (int)get_player_real_position(*p).x, (int)get_player_real_position(*p).y);

  SDL_Rect temp;
  temp.x = get_player_screen_position(*p).x;
  temp.y = get_player_screen_position(*p).y;
  temp.w = get_player_hitbox(*p).w;
  temp.h = get_player_hitbox(*p).h;

  set_player_hitbox(p, temp);

  return;

}

void render_player (player p, SDL_Renderer *renderer, intpoint mouse_pos) {

  SDL_Rect *temp = NULL;
  temp = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  temp->w = 32;
  temp->h = 64;

  if (get_player_dir(p) == 1) {
    //player facing right

    switch (get_player_state(p)) {

      //stand-by/walking
      case 0:

        if (get_player_velocity(p).x == 0 && get_player_velocity(p).y == 0) {

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

        if (get_player_velocity(p).x == 0 && get_player_velocity(p).y == 0) {

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

  SDL_Rect tempSpritePos = get_player_sprite_pos(p);
  SDL_Rect tempPos = get_player_hitbox(p);

  SDL_RenderCopy(renderer, get_player_img(p), &tempSpritePos, &tempPos);

  free(temp);

  return;
}

/* BEHAVIOR */

void player_melee (player p, SDL_Renderer *renderer) {

  SDL_Rect *target = NULL;
  target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  target->x = get_player_screen_position(p).x;
  target->y = get_player_screen_position(p).y;
  target->w = get_player_hitbox(p).w;
  target->h = get_player_hitbox(p).h;

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

  SDL_RenderCopy(renderer, get_player_img(p), effect, target);

  free(target);
  free(effect);

  return;

}

void player_update_step (player *p) {

  if(get_player_velocity(*p).x != 0) {

    set_player_step(p, get_player_step(*p) + 1);

    if(get_player_step(*p) == 4) {

      set_player_step(p, 0);

    }

  }

}

void player_update_dir (player *p, intpoint mouse_pos) {

  if(get_player_real_position(*p).x + (IMG_WIDTH / 2) < mouse_pos.x) {
    set_player_dir(p, 1); //right
  } else {
    set_player_dir(p, 0); //left
  }

}

void player_apply_velocity (player *p) {
  set_player_real_position(p, get_player_real_position(*p).x + get_player_velocity(*p).x, get_player_real_position(*p).y + get_player_velocity(*p).y);
  return;
}

float player_jumping_x (player p, Uint32 timeN) {
  float t = timeN, x0 = get_floatpoint_x(get_player_real_position(p)), v = get_player_velocity(p).x;

  return (v * t) + x0;
}

float player_jumping_y (player p, Uint32 timeN) {
  float t = timeN, y0 = get_floatpoint_y(get_player_real_position(p)), v = abs(get_player_velocity(p).y);

  return y0 - (v * t);
}

void player_gravity(player *p) {
  if ((get_floatpoint_y(get_player_real_position(*p)) + IMG_HEIGHT) < SCREEN_HEIGHT) {
    set_player_real_position(p, get_floatpoint_x(get_player_real_position(*p)), get_floatpoint_y(get_player_real_position(*p)) + 2);
  }

  return;
}

//temporary
floatpoint calcul_position (player p, float v_init, floatpoint pos_init, float angle, Uint32 timeN) {
  floatpoint pos = set_floatpoint(0.001 * player_jumping_x(p, timeN), -0.01 * player_jumping_y(p, timeN));

  return pos;
}

void player_jumping (player *p, Uint32 timeN_A, Uint32 timeN_B) {

  Uint32 timeN = timeN_B - timeN_A;

  if (get_player_state(*p) == 1 || get_player_state(*p) == 2) {
    floatpoint pos = set_floatpoint(get_player_real_position(*p).x, get_player_real_position(*p).y);
    floatpoint next_pos = calcul_position(*p, get_player_velocity(*p).x, pos, 0.78, timeN);

    set_player_real_position(p, get_floatpoint_x(next_pos) + get_floatpoint_x(pos), get_floatpoint_y(next_pos) + get_floatpoint_y(pos));

    return;
  }

  if (timeN >= 950) {
    set_player_state(p, 0);
  }

  return;
}

/* SET */

//create a new player
player set_player (short int maxHealthPoints, floatpoint position, vector velocity, SDL_Texture *image, SDL_Rect posSprite, SDL_Rect hitbox) {

  player p;
  set_player_maxhp(&p, maxHealthPoints);
  set_player_hp(&p, maxHealthPoints);
  set_player_dir(&p, 0);
  set_player_dJump(&p, true);
  set_player_jumpPoint(&p, 0);
  set_player_highPoint(&p, 0);
  set_player_state(&p, 0);
  set_player_real_position(&p, get_floatpoint_x(position), get_floatpoint_y(position));
  set_player_screen_position(&p, (int)get_floatpoint_x(position), (int)get_floatpoint_y(position));
  set_player_vel_x(&p, get_vector_x(velocity));
  set_player_vel_y(&p, get_vector_y(velocity));
  set_player_img(&p, image);
  set_player_sprite_pos(&p, posSprite);
  set_player_hitbox(&p, hitbox);

  return p;
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

//set the player's real position
void set_player_real_position (player *p, float x, float y) {
  p->realPos.x = x;
  p->realPos.y = y;
  return;
}

//set the player's position
void set_player_screen_position (player *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

//set the player's x velocity
void set_player_vel_x (player *p, float x) {
  p->vel.x = x;
  return;
}

//set the player's y velocity
void set_player_vel_y (player *p, float y) {
  p->vel.y = y;
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

//set the player hitbox
void set_player_hitbox (player *p, SDL_Rect hitbox) {
  p->hitbox = hitbox;
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

//get the player's real position
floatpoint get_player_real_position (player p) {
  return p.realPos;
}

//get the player's position
intpoint get_player_screen_position (player p) {
  return p.screenPos;
}

//get the player's x velocity
vector get_player_velocity (player p) {
  return p.vel;
}

//get the player's image
SDL_Texture* get_player_img (player p) {
  return p.img;
}

//get the player's sprite position on the sprite sheet
SDL_Rect get_player_sprite_pos (player p) {
  return p.spritePos;
}

//get the player's hitbox
SDL_Rect get_player_hitbox (player p) {
  return p.hitbox;
}
