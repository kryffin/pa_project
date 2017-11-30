/*

character.c : contain every functions for the characters

*/

#include "../header_files/character.h"

//create a new projectile and add it in the list
void shooting (bool mouse_btn, character_t *p, intpoint_t mouse_pos) {

  if (!mouse_btn) {
    return;
  }

  vector_t dir = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_character_real_position(*p).x + (IMG_WIDTH / 2)), (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_character_real_position(*p).y + (IMG_HEIGHT / 2)));
  dir = normalize(dir);
  dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);

  SDL_Rect temp = {get_intpoint_x(get_character_screen_position(*p)), get_intpoint_x(get_character_screen_position(*p)), BULLET_WIDTH, BULLET_HEIGHT};
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

  p->projectiles = projectile_list_build(set_projectile(set_floatpoint(get_intpoint_x(get_character_screen_position(*p)) + (IMG_WIDTH / 2), get_intpoint_y(get_character_screen_position(*p)) + (IMG_HEIGHT / 4)), dir, temp, tempSprite), p->projectiles);

  return;

}

//update the grid position
void character_update_grid_pos (character_t *character) {
  character->gridPos.x = (int)floor((get_floatpoint_x(get_character_real_position(*character)) + (IMG_WIDTH / 2)) / 16);
  character->gridPos.y = (int)floor((get_floatpoint_y(get_character_real_position(*character)) + (IMG_HEIGHT / 2)) / 16);

  return;
}

//update a list of projectiles
projectile_list_t update_projectiles (projectile_list_t projectiles, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], character_t *player, character_list_t enemies, bool playerShooting) {

  if (projectile_list_is_empty(projectiles)) {
    return projectile_list_empty();
  }

  if ((get_projectile_real_position(projectile_list_head(projectiles)).x + BULLET_WIDTH < 0.0
        || get_projectile_real_position(projectile_list_head(projectiles)).x > SCREEN_WIDTH)
        || (get_projectile_real_position(projectile_list_head(projectiles)).y + BULLET_HEIGHT < 0.0
        || get_projectile_real_position(projectile_list_head(projectiles)).y > SCREEN_HEIGHT)) {

    //projectile isn't in the screen
    return update_projectiles(projectile_list_rest(projectiles), blocks, player, enemies, playerShooting);
  }

  block_t temp = blocks[(int)floor((get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + (BULLET_WIDTH / 2)) / 16)][(int)floor((get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + (BULLET_HEIGHT / 2)) / 16)];

  if (get_block_type(temp) == Solid) {
    return update_projectiles(projectile_list_rest(projectiles), blocks, player, enemies, playerShooting);
  }

  if (!playerShooting) {
    //ennemy shooting
    if (get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) >= player->hitbox.x && get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles) ))<= player->hitbox.x + player->hitbox.w && get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) >= player->hitbox.y && get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) <= player->hitbox.y + player->hitbox.h) {
      player->hp -= 1;
      return update_projectiles(projectile_list_rest(projectiles), blocks, player, enemies, playerShooting);
    }
  } else {
    //player shooting
    bool destroy = false;
    enemies = bullet_collision(enemies, projectile_list_head(projectiles), &destroy);
    if (destroy) {
      return update_projectiles(projectile_list_rest(projectiles), blocks, player, enemies, playerShooting);
    }
  }

  projectile_t p;
  floatpoint_t newPos = set_floatpoint(get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_x(get_projectile_direction(projectile_list_head(projectiles))), get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_y(get_projectile_direction(projectile_list_head(projectiles))));
  SDL_Rect hitbox = {floor(get_floatpoint_x(newPos)), floor(get_floatpoint_y(newPos)), BULLET_WIDTH, BULLET_HEIGHT};

  p = set_projectile(newPos, get_projectile_direction(projectile_list_head(projectiles)), hitbox, get_projectile_sprite_pos(projectile_list_head(projectiles)));

  return projectile_list_build(p, update_projectiles(projectile_list_rest(projectiles), blocks, player, enemies, playerShooting));
}

//check the collision between the projectile and the enemies
character_list_t bullet_collision (character_list_t enemies, projectile_t p, bool *destroy) {
  if (character_list_is_empty(enemies)) {
    return character_list_empty();
  }

  if (get_floatpoint_x(get_projectile_real_position(p)) >= enemies->head.hitbox.x && get_floatpoint_x(get_projectile_real_position(p)) <= enemies->head.hitbox.x + enemies->head.hitbox.w && get_floatpoint_y(get_projectile_real_position(p)) >= enemies->head.hitbox.y && get_floatpoint_y(get_projectile_real_position(p)) <= enemies->head.hitbox.y + enemies->head.hitbox.h) {
    //if there is a collision, we stop searching, we decrease enemy's life and returns the updated list
    *destroy = true;
    enemies->head.hp -= 1;
    return character_list_build(enemies->head, character_list_rest(enemies));
  }

  return character_list_build(enemies->head, bullet_collision(character_list_rest(enemies), p, destroy));
}

//update the positions and hitbox
void update_character (character_t *p, character_list_t *enemies, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], bool *quit) {

  if (!is_alive(*p)) {
    *quit = true;
    return;
  }

  set_character_screen_position(p, (int)floor(get_character_real_position(*p).x), (int)floor(get_character_real_position(*p).y));

  if (p->onGround && p->gridPos.y * 16 != p->screenPos.y) {
    p->screenPos.y = p->gridPos.y * 16;
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

  p->projectiles = update_projectiles(p->projectiles, blocks, p, *enemies, true);

  *enemies = update_enemies(*enemies, p, blocks);

  return;
}

//update the enemies' shots and directions
character_list_t update_enemies (character_list_t c, character_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  if (character_list_is_empty(c)) {
    return character_list_empty();
  }

  if (!is_alive(character_list_head(c))) {
    //if this enemy is dead
    return update_enemies(character_list_rest(c), p, blocks);
  }

  character_t e = character_list_head(c);
  e.projectiles = character_list_head(c).projectiles;

  set_character_screen_position(&e, (int)floor(get_character_real_position(e).x), (int)floor(get_character_real_position(e).y));

  if (e.onGround && e.gridPos.y * 16 != e.screenPos.y) {
    e.screenPos.y = e.gridPos.y * 16;
  }

  SDL_Rect temp;
  temp.x = get_character_screen_position(e).x;
  temp.y = get_character_screen_position(e).y;
  temp.w = get_character_hitbox(e).w;

  if (get_character_state(e) == Crouching) {
    //if crouching
    temp.y += 32;
    temp.h = 32;
  } else {
    //if standing up
    temp.h = 64;
  }

  set_character_hitbox(&e, temp);

  character_behaviour (&e, character_list_size(c), get_character_screen_position(*p).x, get_character_screen_position(*p).y);
  //printf("velX:%2.f\n", e.vel.x);
  e.projectiles = update_projectiles(e.projectiles, blocks, p, c, false);

  character_update_dir(&e, set_intpoint(get_character_screen_position(*p).x + (IMG_WIDTH / 2), get_character_screen_position(*p).y + (IMG_HEIGHT / 2)));


  character_update_grid_pos (&e);
  character_apply_velocity (&e, blocks);
  character_gravity(&e);

  return character_list_build(e, update_enemies(character_list_rest(c), p, blocks));
}

//embryon of IA
void character_behaviour(character_t *e, int taille, int x, int y){

  //initialisation of a random number:
  srand(SDL_GetTicks());
  int rdm = rand();
  printf("%d\n", rdm);
  rdm *= taille;
  rdm %= 3;
  //printf("___%d\n*****", rdm);
  switch (rdm){
  case -2:
      //set_character_velocity(e, 5, 0);
      break;
  case -1:
      //set_character_velocity(e, -5, 0);
      break;
    //moving on x axis
  case 0:
    if (SDL_GetTicks() > e->changeVelDelay + 1500) {
      int velX;
      velX = (SDL_GetTicks()%taille); //cause 27 is a prime number and i like it
      velX %= 5;
      velX = (SDL_GetTicks()%2 == 0)? -velX : velX;
      set_character_velocity(e, velX, 0);
      e->changeVelDelay = SDL_GetTicks();
    }
    break;
    //jumping
  case 1:
    if (SDL_GetTicks() > e->changeVelDelay + 1500){
      character_jumping(e);
    }
    break;
    //shooting
  case 2:
    if (SDL_GetTicks() > e->shootDelay + ENEMY_SHOOT_DELAY) {
        shooting(true, e, set_intpoint(x + (IMG_WIDTH / 2), y + (IMG_HEIGHT / 2)));
        e->shootDelay = SDL_GetTicks();
    }
    break;

  case 3:
    shooting(false, e, set_intpoint(x + (IMG_WIDTH / 2), y + (IMG_HEIGHT / 2)));
    break;
  }
}

//update the step used for the walking animation
void character_update_step (character_t *p) {

  if(get_character_velocity(*p).x != 0) {

    set_character_step(p, get_character_step(*p) + 1);

    if(get_character_step(*p) == 4) {

      set_character_step(p, 0);

    }

  }

  return;

}


//update the character direction to look towards the target
void character_update_dir (character_t *p, intpoint_t target) {

  if(get_character_real_position(*p).x + (IMG_WIDTH / 2) < target.x) {
    set_character_dir(p, Right); //right
  } else {
    set_character_dir(p, Left); //left
  }

}



//apply the velocity on the character if possible
void character_apply_velocity (character_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  if (p->gridPos.y == NB_BLOCKS_HEIGHT - 4 || blocks[p->gridPos.x][p->gridPos.y + 4].type == 0 || blocks[p->gridPos.x + 1][p->gridPos.y + 4].type == 0) {
    p->onGround = true;
  } else {
    p->onGround = false;
  }

  if (!p->onGround) {
    //p->vel.x *= AIR_ACCELERATION;
  }


  if (p->vel.x < 0.0) {
    if (p->gridPos.x != 0 && (blocks[p->gridPos.x - 1][p->gridPos.y].type != 0 && blocks[p->gridPos.x - 1][p->gridPos.y + 1].type != 0 && blocks[p->gridPos.x - 1][p->gridPos.y + 2].type != 0 && blocks[p->gridPos.x - 1][p->gridPos.y + 3].type != 0)) {
      p->realPos.x += p->vel.x;
    }
  }
  if (p->vel.x > 0.0 && (blocks[p->gridPos.x + 1][p->gridPos.y].type != 0 && blocks[p->gridPos.x + 1][p->gridPos.y + 1].type != 0 && blocks[p->gridPos.x + 1][p->gridPos.y + 2].type != 0 && blocks[p->gridPos.x + 1][p->gridPos.y + 3].type != 0)) {
    if (p->gridPos.x != NB_BLOCKS_WIDTH - 1) {
      p->realPos.x += p->vel.x;
    }
  }

  if (blocks[p->gridPos.x][p->gridPos.y - 1].type == 0) {
    p->vel.y = 4.0;
  }

  if (p->vel.y < 0.0 && blocks[p->gridPos.x][p->gridPos.y - 1].type != 0) {
    if (p->gridPos.y != 0) {
      p->realPos.y += p->vel.y;
    }
  }
  if (p->vel.y > 0.0 && blocks[p->gridPos.x][p->gridPos.y + 4].type != 0) {
    if (p->gridPos.y != NB_BLOCKS_HEIGHT - 4) {
      p->realPos.y += p->vel.y;
    }
  }

  return;
}

void character_apply_velocity_ennemies (character_list_t *enemies, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], Uint32 time) {
    if(!character_list_is_empty(*enemies)){
      if(is_alive(character_list_head(*enemies))){
        //character_t tmp = character_list_head(*enemies);
        character_list_t tmpRest = character_list_rest(*enemies);
        character_apply_velocity_ennemies(&tmpRest, blocks, SDL_GetTicks());

      } else {
        return;
      }
    } else {
      return;
    }
}



//apply the gravity if the character is in the air
void character_gravity(character_t *p) {

  if (!p->onGround && p->vel.y < 12.0) {
    set_character_velocity(p, get_character_velocity(*p).x, get_character_velocity(*p).y + GRAVITY);
  }

  return;
}

//make the character jump
void character_jumping (character_t *p) {

  set_character_velocity (p, get_character_velocity(*p).x, JUMP_HEIGHT);

  return;
}

//returns true if the character is alive, dead otherwise
bool is_alive(character_t c) {

  return (get_character_hp(c) > 0);
}

/* LIST */

//build a new character on the list
character_list_t character_list_build (character_t c, character_list_t cl) {
  character_list_t tmp;
  tmp = malloc(sizeof(*tmp));
  tmp->head = c;
  tmp->next = cl;
  return tmp;
}

//returns the head of the character list
character_t character_list_head (character_list_t c) {

  if (character_list_is_empty(c)) {
    printf("Reading head of an empty character list!");
    exit(0);
  }

  return c->head;
}

//returns the rest of the character list
character_list_t character_list_rest (character_list_t c) {
  return c->next;
}

//returns true if the character list is empty, false otherwise
bool character_list_is_empty (character_list_t c) {
  return c == NULL;
}

//returns an empty character list
character_list_t character_list_empty () {
  return NULL;
}

//free the list of character as well as their projectiles
void character_list_free (character_list_t c) {
  if (character_list_is_empty(c)) {
    return;
  }
  character_list_free(character_list_rest(c));
  projectile_list_free(character_list_head(c).projectiles);
  free(c);
}

// return the size of the list
int character_list_size (character_list_t c) {
  if (character_list_is_empty(c)) {
    return 0;
  } else {
    character_list_t tempRest = character_list_rest(c);
    return 1 + character_list_size (tempRest);
  }
}
/* SET */

//create a new character
character_t set_character (short int hp, floatpoint_t position, vector_t velocity, SDL_Rect posSprite, SDL_Rect hitbox, short int type) {

  character_t p;

  set_character_hp(&p, hp);
  set_character_dir(&p, Left);
  set_character_step(&p, 0);
  set_character_type(&p, type);
  set_character_on_ground(&p, false);
  set_character_state(&p, Walking);

  set_character_step_delay(&p, 0);
  set_character_shoot_delay(&p, 0);

  set_character_real_position(&p, get_floatpoint_x(position), get_floatpoint_y(position));
  set_character_screen_position(&p, (int)floor(get_floatpoint_x(position)), (int)floor(get_floatpoint_y(position)));
  set_character_grid_position(&p, (int)floor(get_intpoint_x(get_character_screen_position(p))), (int)floor(get_intpoint_y(get_character_screen_position(p)) / 16));

  set_character_projectiles(&p, projectile_list_empty());

  set_character_velocity(&p, velocity.x, velocity.y);
  set_character_sprite_pos(&p, posSprite);
  set_character_hitbox(&p, hitbox);

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

//set the type
void set_character_type (character_t *p, short int type) {
  p->type = type;
  return;
}

//set the character on ground or not
void set_character_on_ground (character_t *p, bool onGround) {
  p->onGround = onGround;
  return;
}

//set the character's state
void set_character_state (character_t *p, short int state) {
  p->state = state;
  return;
}

//set the delay of the step
void set_character_step_delay (character_t *p, int stepDelay) {
  p->stepDelay = stepDelay;
  return;
}

//set the delay of shooting
void set_character_shoot_delay (character_t *p, int shootDelay) {
  p->shootDelay = shootDelay;
  return;
}

//set the character's real position
void set_character_real_position (character_t *p, float x, float y) {
  p->realPos.x = x;
  p->realPos.y = y;
  return;
}

//set the character's screen position
void set_character_screen_position (character_t *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

//set the character's grid position
void set_character_grid_position (character_t *p, int x, int y) {
  p->gridPos.x = x;
  p->gridPos.y = y;
  return;
}

//set the list of projectiles
void set_character_projectiles (character_t *p, projectile_list_t projectiles) {
  p->projectiles = projectiles;
  return;
}

//set the character's velocity
void set_character_velocity (character_t *p, float x, float y) {
  p->vel.x = x;
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

//get the type
short int get_character_type (character_t p) {
  return p.type;
}

//get the on ground boolean
bool get_character_on_ground (character_t p) {
  return p.onGround;
}

//get the character's state
short int get_character_state (character_t p) {
  return p.state;
}

//get the character's step delay
int get_character_step_delay (character_t p) {
  return p.stepDelay;
}

//get the character's shoot delay
int get_character_shoot_delay (character_t p) {
  return p.shootDelay;
}

//get the character's real position
floatpoint_t get_character_real_position (character_t p) {
  return p.realPos;
}

//get the character's position
intpoint_t get_character_screen_position (character_t p) {
  return p.screenPos;
}

//get the character's grid position
intpoint_t get_character_grid_position (character_t p) {
  return p.gridPos;
}

//get the list of projectiles
projectile_list_t get_character_projectiles (character_t p) {
  return p.projectiles;
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
