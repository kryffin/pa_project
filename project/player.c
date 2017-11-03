#include "header.h"

intpoint_t get_player_grid_pos (player_t p) {
  int x, y, i, j;
  x = (int)get_player_real_position(p).x;
  y = (int)get_player_real_position(p).y;

  for (i = 0; i < SCREEN_WIDTH; i += 16) {
    if (x >= i && x < i + 16) {
      for (j = 0; j < SCREEN_HEIGHT; j += 16) {
        if (y >= j && y < j + 16) {

          return set_intpoint(i/16, j/16);
        }
      }
    }
  }

  printf("Error in the grid\n");
  return set_intpoint(0, 0);
}

void update_player (player_t *p, bool *quit) {

  if (!is_alive(*p)) {
    *quit = true;
    return;
  }

  set_player_screen_position(p, (int)get_player_real_position(*p).x, (int)get_player_real_position(*p).y);

  SDL_Rect temp;
  temp.x = get_player_screen_position(*p).x;
  temp.y = get_player_screen_position(*p).y;
  temp.w = get_player_hitbox(*p).w;

  if (get_player_state(*p) == 4) {
    //if crouching
    temp.y += 32;
    temp.h = 32;
  } else {
    //if standing up
    temp.h = 64;
  }

  set_player_hitbox(p, temp);

  return;
}

void update_enemy (player_t *p) {

  set_player_screen_position(p, (int)get_player_real_position(*p).x, (int)get_player_real_position(*p).y);

  SDL_Rect temp;
  temp.x = get_player_screen_position(*p).x;
  temp.y = get_player_screen_position(*p).y;
  temp.w = get_player_hitbox(*p).w;
  temp.h = get_player_hitbox(*p).h;

  set_player_hitbox(p, temp);

  return;
}

void render_player (player_t p, SDL_Renderer *renderer, intpoint_t mouse_pos) {

  SDL_Rect *temp = NULL;
  temp = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  temp->w = 32;
  temp->h = 64;
  short int step = get_player_step(p);
  short int state = get_player_state(p);

  if (get_player_dir(p) == 1) {
    //player facing right

    switch (state) {

      //stand-by/walking
      case 0:

        if (get_player_velocity(p).x == 0 && get_player_velocity(p).y == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 0;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          switch (step) {

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
        temp->h = 32;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  } else {
    //player facing left

    switch (state) {

      //stand-by/walking
      case 0:

        if (get_player_velocity(p).x == 0 && get_player_velocity(p).y == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 64;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          switch (step) {

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
        temp->y = 32;
        temp->h = 32;
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

void player_melee (player_t p, SDL_Renderer *renderer) {

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

void player_update_step (player_t *p) {

  if(get_player_velocity(*p).x != 0) {

    set_player_step(p, get_player_step(*p) + 1);

    if(get_player_step(*p) == 4) {

      set_player_step(p, 0);

    }

  }

  return;

}

void player_update_dir (player_t *p, intpoint_t mouse_pos) {

  if(get_player_real_position(*p).x + (IMG_WIDTH / 2) < mouse_pos.x) {
    set_player_dir(p, 1); //right
  } else {
    set_player_dir(p, 0); //left
  }

}

void player_apply_velocity (player_t *p, block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  if (get_player_real_position(*p).y + get_player_velocity(*p).y + IMG_HEIGHT > SCREEN_HEIGHT) {
    set_player_vel_y(p, SCREEN_HEIGHT - (get_player_real_position(*p).y + IMG_HEIGHT));
  }

  set_player_real_position(p, get_player_real_position(*p).x + get_player_velocity(*p).x, get_player_real_position(*p).y + get_player_velocity(*p).y);

  int w, h;
  if (colision(*p, blocks, &w, &h)) {
    intpoint_t dist;
    dist = closest_out(*p, w, h);
    set_player_real_position(p, get_intpoint_x(dist), get_intpoint_y(dist));
  }

  return;
}

void player_gravity(player_t *p, block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  //intpoint_t gridPos = get_player_grid_pos(*p);

  /*if (get_block_type(blocks[get_intpoint_x(gridPos)][get_intpoint_y(gridPos) + 4]) == 0 || get_block_type(blocks[get_intpoint_x(gridPos) + 1][get_intpoint_y(gridPos) + 4]) == 0 || get_block_type(blocks[get_intpoint_x(gridPos) + 2][get_intpoint_y(gridPos) + 4]) == 0) {
    printf("on ground x : %d | y : %d\n", gridPos.x, gridPos.y);
    set_player_vel_y(p, 0.0);
    //set_player_real_position(p, get_intpoint_x(gridPos) * 16, (get_intpoint_y(gridPos) * 16) - 1);
    return;
  }*/

  if (get_player_real_position(*p).y <= SCREEN_HEIGHT - IMG_HEIGHT) {
    set_player_vel_y(p, get_player_velocity(*p).y + GRAVITY);
  }

  return;
}


void player_jumping (player_t *p, Uint32 timeN_A, Uint32 timeN_B) {
  if (get_player_state(*p) == 1 || get_player_state(*p) == 2) {
    set_player_vel_y(p, JUMP_HEIGHT);
  }

  return;
}

bool is_alive(player_t p) {
  return (get_player_hp(p) > 0);
}

/* SET */

//create a new player
player_t set_player (short int maxHealthPoints, floatpoint_t position, vector_t velocity, SDL_Texture *image, SDL_Rect posSprite, SDL_Rect hitbox) {

  player_t p;
  set_player_maxhp(&p, maxHealthPoints);
  set_player_hp(&p, maxHealthPoints);
  set_player_dir(&p, 0);
  set_player_step(&p, 0);
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
void set_player_maxhp (player_t *p, short int maxhp) {
  p->maxhp = maxhp;
  return;
}

//set the player's health points
void set_player_hp (player_t *p, short int hp) {
  p->hp = hp;
  return;
}

//set the current direction
void set_player_dir (player_t *p, short int dir) {
  p->dir = dir;
  return;
}

//set the step
void set_player_step (player_t *p, short int step) {
  p->step = step;
  return;
}

//set the player's ability to double jump
void set_player_dJump (player_t *p, bool dJump) {
  p->dJump = dJump;
  return;
}

//set the player's jump point
void set_player_jumpPoint (player_t *p, int jumpPoint) {
  p->jumpPoint = jumpPoint;
  return;
}

//set the player's high point
void set_player_highPoint (player_t *p, int highPoint) {
  p->highPoint = highPoint;
  return;
}

//set the player's state
void set_player_state (player_t *p, short int state) {
  p->state = state;
  return;
}

//set the player's real position
void set_player_real_position (player_t *p, float x, float y) {
  p->realPos.x = x;
  p->realPos.y = y;
  return;
}

//set the player's position
void set_player_screen_position (player_t *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

//set the player's x velocity
void set_player_vel_x (player_t *p, float x) {
  p->vel.x = x;
  return;
}

//set the player's y velocity
void set_player_vel_y (player_t *p, float y) {
  p->vel.y = y;
  return;
}

//set the player's image
void set_player_img (player_t *p, SDL_Texture *img) {
  p->img = img;
  return;
}

//set the player sprite position on the spritesheet
void set_player_sprite_pos (player_t *p, SDL_Rect posSprite) {
  p->spritePos = posSprite;
  return;
}

//set the player hitbox
void set_player_hitbox (player_t *p, SDL_Rect hitbox) {
  p->hitbox = hitbox;
  return;
}

/* GET */

//get the player's max health points
short int get_player_maxhp (player_t p) {
  return p.maxhp;
}

//get the player's health points
short int get_player_hp (player_t p) {
  return p.hp;
}

//get the current direction
short int get_player_dir (player_t p) {
  return p.dir;
}

//get the step
short int get_player_step (player_t p) {
  return p.step;
}

//get the player's ability to double jump
bool get_player_dJump (player_t p) {
  return p.dJump;
}

//get the player's jump point
int get_player_jumpPoint (player_t p) {
  return p.jumpPoint;
}

//get the player's high point
int get_player_highPoint (player_t p) {
  return p.highPoint;
}

//get the player's state
short int get_player_state (player_t p) {
  return p.state;
}

//get the player's real position
floatpoint_t get_player_real_position (player_t p) {
  return p.realPos;
}

//get the player's position
intpoint_t get_player_screen_position (player_t p) {
  return p.screenPos;
}

//get the player's x velocity
vector_t get_player_velocity (player_t p) {
  return p.vel;
}

//get the player's image
SDL_Texture* get_player_img (player_t p) {
  return p.img;
}

//get the player's sprite position on the sprite sheet
SDL_Rect get_player_sprite_pos (player_t p) {
  return p.spritePos;
}

//get the player's hitbox
SDL_Rect get_player_hitbox (player_t p) {
  return p.hitbox;
}
