#include "../header_files/player.h"

void player_update_grid_pos (player_t *player) {
  player->xGrid = floor(get_floatpoint_x(get_player_real_position(*player))) / 16;
  player->yGrid = floor(get_floatpoint_y(get_player_real_position(*player))) / 16;

  return;
}

void shooting (bool mouse_btn, player_t p, projectile_t proj[100], intpoint_t mouse_pos) {

  vector_t dir = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_player_real_position(p).x + (IMG_WIDTH / 2)), (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_player_real_position(p).y + (IMG_HEIGHT / 2)));

  dir = normalize(dir);

  dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);

  int i;

  if (mouse_btn) {

    //if clicking we shoot
    for (i = 0; i < 100; i += 1) {

      //if a projectile_t has no direction it doesn't exists
      if (get_projectile_direction(proj[i]).x == 0.0 && get_projectile_direction(proj[i]).y == 0.0) {

        set_projectile_real_position(&proj[i], (get_player_real_position(p).x + (IMG_WIDTH / 2)) - (BULLET_WIDTH / 2), (get_player_real_position(p).y + (IMG_HEIGHT / 2)) - (BULLET_HEIGHT / 2));
        set_projectile_direction(&proj[i], dir);

        return;
      }

    }

  }

  //security check
  return;

}

void update_player (player_t *p, bool *quit) {

  if (!is_alive(*p)) {
    *quit = true;
    return;
  }

  set_player_screen_position(p, floor(get_player_real_position(*p).x), floor(get_player_real_position(*p).y));

  if (p->onGround && p->yGrid * 16 != p->screenPos.y) {
    p->screenPos.y = p->yGrid * 16;
  }

  SDL_Rect temp;
  temp.x = get_player_screen_position(*p).x;
  temp.y = get_player_screen_position(*p).y;
  temp.w = get_player_hitbox(*p).w;

  if (get_player_state(*p) == Crouching) {
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

  if (get_player_dir(p) == Left) {
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
    set_player_dir(p, Right); //right
  } else {
    set_player_dir(p, Left); //left
  }

}

void player_apply_velocity (player_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  if (p->yGrid == NB_BLOCKS_HEIGHT - 4 || blocks[p->xGrid][p->yGrid + 4].type == 0 || blocks[p->xGrid + 1][p->yGrid + 4].type == 0) {
    p->onGround = true;
  } else {
    p->onGround = false;
  }


  if (p->vel.x < 0.0) {
    if (p->xGrid != 0 && (blocks[p->xGrid - 1][p->yGrid].type != 0 && blocks[p->xGrid - 1][p->yGrid + 1].type != 0 && blocks[p->xGrid - 1][p->yGrid + 2].type != 0 && blocks[p->xGrid - 1][p->yGrid + 3].type != 0)) {
      p->realPos.x += p->vel.x;
    }
  }
  if (p->vel.x > 0.0 && (blocks[p->xGrid + 2][p->yGrid].type != 0 && blocks[p->xGrid + 2][p->yGrid + 1].type != 0 && blocks[p->xGrid + 2][p->yGrid + 2].type != 0 && blocks[p->xGrid + 2][p->yGrid + 3].type != 0)) {
    if (p->xGrid != NB_BLOCKS_WIDTH - 2) {
      p->realPos.x += p->vel.x;
    }
  }

  if (blocks[p->xGrid][p->yGrid - 1].type == 0 || blocks[p->xGrid + 1][p->yGrid - 1].type == 0) {
    p->vel.y = 4.0;
  }

  if (p->vel.y < 0.0 && (blocks[p->xGrid][p->yGrid - 1].type != 0 && blocks[p->xGrid + 1][p->yGrid - 1].type != 0)) {
    if (p->yGrid != 0) {
      p->realPos.y += p->vel.y;
    }
  }
  if (p->vel.y > 0.0 && (blocks[p->xGrid][p->yGrid + 4].type != 0 && blocks[p->xGrid + 1][p->yGrid + 4].type != 0)) {
    if (p->yGrid != NB_BLOCKS_HEIGHT - 4) {
      p->realPos.y += p->vel.y;
    }
  }

  return;
}

void player_gravity(player_t *p) {

  if (!p->onGround && p->vel.y < 12.0) {
    set_player_vel_y(p, get_player_velocity(*p).y + GRAVITY);
  }

  return;
}


void player_jumping (player_t *p) {

  if (get_player_state(*p) == Jumping || get_player_state(*p) == nouse) {
    set_player_vel_y(p, JUMP_HEIGHT);
  }

  return;
}

bool is_alive(player_t p) {
  return (get_player_hp(p) > 0);
}

/* SET */

//create a new player
player_t set_player (short int maxHealthPoints, floatpoint_t position, vector_t velocity, char *path_sprites, SDL_Rect posSprite, SDL_Rect hitbox, SDL_Renderer *renderer) {

  SDL_Surface *temp;
  player_t p;

  temp = IMG_Load(path_sprites);
  p.img = SDL_CreateTextureFromSurface(renderer, temp);
  if (p.img == NULL) {
    printf("Error during bullet image loading : %s\n", SDL_GetError());
  }
  SDL_FreeSurface(temp);

  set_player_maxhp(&p, maxHealthPoints);
  set_player_hp(&p, maxHealthPoints);
  set_player_dir(&p, Left);
  set_player_step(&p, 0);
  set_player_on_ground(&p, false);
  set_player_jumpPoint(&p, 0);
  set_player_highPoint(&p, 0);
  set_player_state(&p, Walking);
  set_player_real_position(&p, get_floatpoint_x(position), get_floatpoint_y(position));
  set_player_screen_position(&p, (int)get_floatpoint_x(position), (int)get_floatpoint_y(position));
  set_player_vel_x(&p, get_vector_x(velocity));
  set_player_vel_y(&p, get_vector_y(velocity));
  set_player_sprite_pos(&p, posSprite);
  set_player_hitbox(&p, hitbox);
  p.stepDelay = 0;
  p.shootDelay = 0;
  p.jumpDelay = 0;

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
void set_player_on_ground (player_t *p, bool onGround) {
  p->onGround = onGround;
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
bool get_player_on_ground (player_t p) {
  return p.onGround;
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
