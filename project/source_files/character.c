#include "../header_files/character.h"

void shooting (bool mouse_btn, character_t *p, intpoint_t mouse_pos) {

  if (!mouse_btn) {
    return;
  }

  vector_t dir = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_character_real_position(*p).x + (IMG_WIDTH / 2)), (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_character_real_position(*p).y + (IMG_HEIGHT / 2)));
  dir = normalize(dir);
  dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);

  SDL_Rect temp = {floor(get_floatpoint_x(get_character_real_position(*p))), floor(get_floatpoint_x(get_character_real_position(*p))), BULLET_WIDTH, BULLET_HEIGHT};
  SDL_Rect tempSprite;
  if (p->type == Player) {
    tempSprite.x = 128;
    tempSprite.y = 64;
  } else {
    tempSprite.x = 144;
    tempSprite.y = 64;
  }
  tempSprite.w = BULLET_WIDTH;
  tempSprite.h = BULLET_HEIGHT;

  p->projectiles = projectile_list_build(set_projectile(set_floatpoint(get_floatpoint_x(get_character_real_position(*p)) + (IMG_WIDTH / 2), get_floatpoint_y(get_character_real_position(*p)) + (IMG_HEIGHT / 4)), dir, temp, tempSprite), p->projectiles);

  return;

}

void character_update_grid_pos (character_t *character) {
  character->xGrid = floor(get_floatpoint_x(get_character_real_position(*character))) / 16;
  character->yGrid = floor(get_floatpoint_y(get_character_real_position(*character))) / 16;

  return;
}

void update_character (character_t *p, bool *quit) {

  if (!is_alive(*p)) {
    *quit = true;
    return;
  }

  set_character_screen_position(p, floor(get_character_real_position(*p).x), floor(get_character_real_position(*p).y));

  if (p->onGround && p->yGrid * 16 != p->screenPos.y) {
    p->screenPos.y = p->yGrid * 16;
  }

  SDL_Rect temp;
  temp.x = get_character_screen_position(*p).x;
  temp.y = get_character_screen_position(*p).y;
  temp.w = get_character_hitbox(*p).w;

  if (get_character_state(*p) == Crouching) {
    //if crouching
    temp.y += 32;
    temp.h = 32;
  } else {
    //if standing up
    temp.h = 64;
  }

  set_character_hitbox(p, temp);

  return;
}

character_list_t update_enemies (character_list_t c, character_t p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  if (character_list_is_empty(c)) {
    return character_list_empty();
  }

  if (!is_alive(character_list_head(c))) {
    //if this enemy is dead
    return character_list_rest(c);
  }

  character_t e = character_list_head(c);
  e.projectiles = character_list_head(c).projectiles;

  if (e.onGround && e.yGrid * 16 != e.screenPos.y) {
    e.screenPos.y = e.yGrid * 16;
  }

  if (SDL_GetTicks() > e.shootDelay + ENEMY_SHOOT_DELAY) {
    shooting(true, &e, set_intpoint(get_character_screen_position(p).x + (IMG_WIDTH / 2), get_character_screen_position(p).y + (IMG_HEIGHT / 2)));
    e.shootDelay = SDL_GetTicks();
  }
  e.projectiles = update_projectiles(e.projectiles, blocks);

  character_update_dir(&e, set_intpoint(get_character_screen_position(p).x + (IMG_WIDTH / 2), get_character_screen_position(p).y + (IMG_HEIGHT / 2)));

  return character_list_build(e, update_enemies(character_list_rest(c), p, blocks));
}

/* BEHAVIOR */

void character_melee (character_t p, SDL_Renderer *renderer, SDL_Texture *img) {

  SDL_Rect *target = NULL;
  target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  target->x = get_character_screen_position(p).x;
  target->y = get_character_screen_position(p).y;
  target->w = get_character_hitbox(p).w;
  target->h = get_character_hitbox(p).h;

  SDL_Rect *effect = NULL;
  effect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  effect->y = 128;
  effect->w = 32;
  effect->h = 64;

  if (get_character_dir(p) == Left) {
    //facing left
    target->x -= IMG_WIDTH;
    effect->x = 32;

  } else {
    //facing right
    target->x += IMG_WIDTH;
    effect->x = 0;

  }

  SDL_RenderCopy(renderer, img, effect, target);

  free(target);
  free(effect);

  return;

}

void character_update_step (character_t *p) {

  if(get_character_velocity(*p).x != 0) {

    set_character_step(p, get_character_step(*p) + 1);

    if(get_character_step(*p) == 4) {

      set_character_step(p, 0);

    }

  }

  return;

}

void character_update_dir (character_t *p, intpoint_t mouse_pos) {

  if(get_character_real_position(*p).x + (IMG_WIDTH / 2) < mouse_pos.x) {
    set_character_dir(p, Right); //right
  } else {
    set_character_dir(p, Left); //left
  }

}

void character_apply_velocity (character_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

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

void character_gravity(character_t *p) {

  if (!p->onGround && p->vel.y < 12.0) {
    set_character_vel_y(p, get_character_velocity(*p).y + GRAVITY);
  }

  return;
}


void character_jumping (character_t *p) {

  if (get_character_state(*p) == Jumping || get_character_state(*p) == nouse) {
    set_character_vel_y(p, JUMP_HEIGHT);
  }

  return;
}

bool is_alive(character_t c) {
  return (get_character_hp(c) > 0);
}

character_list_t character_list_build (character_t c, character_list_t cl) {
  character_list_t tmp;
  tmp = malloc(sizeof(*tmp));
  tmp->head = c;
  tmp->next = cl;
  return tmp;
}

character_t character_list_head (character_list_t c) {
  if (character_list_is_empty(c)) {
    printf("Reading head of an empty character list!");
    exit(0);
  }
  return c->head;
}

character_list_t character_list_rest (character_list_t c) {
  return c->next;
}

bool character_list_is_empty (character_list_t c) {
  return c == NULL;
}

character_list_t character_list_empty () {
  return NULL;
}

void character_list_free (character_list_t c) {
  if (character_list_is_empty(c)) {
    return;
  }
  character_list_free(character_list_rest(c));
  projectile_list_free(character_list_head(c).projectiles);
  free(c);
}

/* SET */

//create a new character
character_t set_character (short int hp, floatpoint_t position, vector_t velocity, SDL_Rect posSprite, SDL_Rect hitbox, short int type) {

  character_t p;

  set_character_hp(&p, hp);
  set_character_dir(&p, Left);
  set_character_step(&p, 0);
  set_character_on_ground(&p, false);
  set_character_jumpPoint(&p, 0);
  set_character_highPoint(&p, 0);
  set_character_state(&p, Walking);
  set_character_real_position(&p, get_floatpoint_x(position), get_floatpoint_y(position));
  set_character_screen_position(&p, (int)get_floatpoint_x(position), (int)get_floatpoint_y(position));
  set_character_vel_x(&p, get_vector_x(velocity));
  set_character_vel_y(&p, get_vector_y(velocity));
  set_character_sprite_pos(&p, posSprite);
  set_character_hitbox(&p, hitbox);
  p.stepDelay = 0;
  p.shootDelay = 0;
  p.jumpDelay = 0;
  p.projectiles = projectile_list_empty();
  p.type = type;

  return p;
}

//set the character's health points
void set_character_hp (character_t *p, short int hp) {
  p->hp = hp;
  return;
}

//set the current direction
void set_character_dir (character_t *p, short int dir) {
  p->dir = dir;
  return;
}

//set the step
void set_character_step (character_t *p, short int step) {
  p->step = step;
  return;
}

//set the character's ability to double jump
void set_character_on_ground (character_t *p, bool onGround) {
  p->onGround = onGround;
  return;
}

//set the character's jump point
void set_character_jumpPoint (character_t *p, int jumpPoint) {
  p->jumpPoint = jumpPoint;
  return;
}

//set the character's high point
void set_character_highPoint (character_t *p, int highPoint) {
  p->highPoint = highPoint;
  return;
}

//set the character's state
void set_character_state (character_t *p, short int state) {
  p->state = state;
  return;
}

//set the character's real position
void set_character_real_position (character_t *p, float x, float y) {
  p->realPos.x = x;
  p->realPos.y = y;
  return;
}

//set the character's position
void set_character_screen_position (character_t *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

//set the character's x velocity
void set_character_vel_x (character_t *p, float x) {
  p->vel.x = x;
  return;
}

//set the character's y velocity
void set_character_vel_y (character_t *p, float y) {
  p->vel.y = y;
  return;
}

//set the character sprite position on the spritesheet
void set_character_sprite_pos (character_t *p, SDL_Rect posSprite) {
  p->spritePos = posSprite;
  return;
}

//set the character hitbox
void set_character_hitbox (character_t *p, SDL_Rect hitbox) {
  p->hitbox = hitbox;
  return;
}

/* GET */

//get the character's health points
short int get_character_hp (character_t p) {
  return p.hp;
}

//get the current direction
short int get_character_dir (character_t p) {
  return p.dir;
}

//get the step
short int get_character_step (character_t p) {
  return p.step;
}

//get the character's ability to double jump
bool get_character_on_ground (character_t p) {
  return p.onGround;
}

//get the character's jump point
int get_character_jumpPoint (character_t p) {
  return p.jumpPoint;
}

//get the character's high point
int get_character_highPoint (character_t p) {
  return p.highPoint;
}

//get the character's state
short int get_character_state (character_t p) {
  return p.state;
}

//get the character's real position
floatpoint_t get_character_real_position (character_t p) {
  return p.realPos;
}

//get the character's position
intpoint_t get_character_screen_position (character_t p) {
  return p.screenPos;
}

//get the character's x velocity
vector_t get_character_velocity (character_t p) {
  return p.vel;
}

//get the character's sprite position on the sprite sheet
SDL_Rect get_character_sprite_pos (character_t p) {
  return p.spritePos;
}

//get the character's hitbox
SDL_Rect get_character_hitbox (character_t p) {
  return p.hitbox;
}
