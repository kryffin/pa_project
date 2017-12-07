/*

character.c : contain every functions for the characters

*/

#include "../header_files/character.h"

//apply damage on a character and begin the invincibility frames
void apply_damage (character_t *p, int dmg) {
  if (get_i_frames_invincible(p->iFrames)) {
    return;
  }

  //apply the damage
  set_character_hp(p, get_character_hp(*p) - dmg);

  //set the Invincibility state to true
  set_i_frames_invincible(&p->iFrames, true);

  //set the time of the damage for a delay
  set_i_frames_delay(&p->iFrames, SDL_GetTicks());

  return;
}

//create a new projectile and add it in the list
projectile_list_t shooting (bool mouse_btn, character_t p, intpoint_t mouse_pos, musicbox_t musicBox) {

  if (!mouse_btn) {
    return p.projectiles;
  }

  vector_t dir = set_vector((get_intpoint_x(mouse_pos)) - (get_character_real_position(p).x + (IMG_WIDTH / 2)), (get_intpoint_y(mouse_pos)) - (get_character_real_position(p).y + (IMG_HEIGHT / 4) ));
  dir = normalize(dir);
  dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);
  SDL_Rect tempSprite;

  projectile_list_t tmp = projectile_list_copy(p.projectiles);
  projectile_list_free(p.projectiles);

  short int weapon = get_character_weapon(p);

  switch (weapon) {

    case Rifle:

      //sprite position
      if (p.type == Player) {
        tempSprite.x = 128;
        tempSprite.y = 64;
      } else {
        tempSprite.x = 144;
        tempSprite.y = 64;
      }
      tempSprite.w = BULLET_WIDTH;
      tempSprite.h = BULLET_HEIGHT;

      Mix_PlayChannel(-1, musicBox.rifleSoundEffect, 0);

      return projectile_list_build(set_projectile(set_floatpoint(get_character_hitbox(p).x + (IMG_WIDTH / 2), get_character_hitbox(p).y + (IMG_HEIGHT / 4)), dir, Bullet, tempSprite), tmp);

      break;

    case Shotgun:

      //sprite position
      tempSprite.x = 144;
      tempSprite.y = 64;
      tempSprite.w = BULLET_WIDTH;
      tempSprite.h = BULLET_HEIGHT;

      Mix_PlayChannel(-1, musicBox.shotgunSoundEffect, 0);

      tmp = projectile_list_build(set_projectile(set_floatpoint(get_character_hitbox(p).x + (IMG_WIDTH / 2), get_character_hitbox(p).y + (IMG_HEIGHT / 4)), dir, Bullet, tempSprite), tmp);
      tmp = projectile_list_build(set_projectile(set_floatpoint(get_character_hitbox(p).x + (IMG_WIDTH / 2), get_character_hitbox(p).y + (IMG_HEIGHT / 4)), vector_rotate(dir, 25), Bullet, tempSprite), tmp);
      return projectile_list_build(set_projectile(set_floatpoint(get_character_hitbox(p).x + (IMG_WIDTH / 2), get_character_hitbox(p).y + (IMG_HEIGHT / 4)), vector_rotate(dir, -25), Bullet, tempSprite), tmp);

      break;

    case Bazooka:

      //sprite position
      tempSprite.x = 128;
      tempSprite.y = 80;
      tempSprite.w = BULLET_WIDTH;
      tempSprite.h = BULLET_HEIGHT;

      Mix_PlayChannel(-1, musicBox.missileSoundEffect, 0);

      return projectile_list_build(set_projectile(set_floatpoint(get_character_hitbox(p).x + (IMG_WIDTH / 2), get_character_hitbox(p).y + (IMG_HEIGHT / 4)), dir, Missile, tempSprite), tmp);

      break;

    default:
      break;

  }

  return p.projectiles;

}

//update the grid position
void character_update_grid_pos (character_t *character) {
  character->gridPos.x = (int)floor((get_floatpoint_x(get_character_real_position(*character)) + (IMG_WIDTH / 2)) / BLOCK_SIZE);
  character->gridPos.y = (int)floor((get_floatpoint_y(get_character_real_position(*character))) / BLOCK_SIZE);

  return;
}

//update a list of projectiles
projectile_list_t update_projectiles (projectile_list_t projectiles, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], character_t *player, character_list_t enemies, intpoint_t mouse_pos, bool playerShooting) {

  if (projectile_list_is_empty(projectiles)) {
    return projectile_list_empty();
  }

  if ((get_projectile_real_position(projectile_list_head(projectiles)).x + BULLET_WIDTH < 0.0
        || get_projectile_real_position(projectile_list_head(projectiles)).x > SCREEN_WIDTH)
        || (get_projectile_real_position(projectile_list_head(projectiles)).y + BULLET_HEIGHT < 0.0
        || get_projectile_real_position(projectile_list_head(projectiles)).y > SCREEN_HEIGHT)) {

    //projectile isn't in the screen
    projectile_list_t tmp = projectile_list_copy(projectile_list_rest(projectiles));
    projectile_list_free(projectiles);
    return update_projectiles(tmp, blocks, player, enemies, mouse_pos, playerShooting);
  }

  block_t temp = blocks[(int)floor((get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + (BULLET_WIDTH / 2)) / BLOCK_SIZE)][(int)floor((get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + (BULLET_HEIGHT / 2)) / BLOCK_SIZE)];

  if (get_block_type(temp) == Solid) {
    projectile_list_t tmp = projectile_list_copy(projectile_list_rest(projectiles));
    projectile_list_free(projectiles);
    return update_projectiles(tmp, blocks, player, enemies, mouse_pos, playerShooting);
  }

  if (!playerShooting) {
    //ennemy shooting
    if (get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) >= player->hitbox.x && get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles) ))<= player->hitbox.x + player->hitbox.w && get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) >= player->hitbox.y && get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) <= player->hitbox.y + player->hitbox.h) {
      apply_damage(player, 1);
      projectile_list_t next = projectile_list_copy(projectile_list_rest(projectiles));
      projectile_list_free(projectiles);
      return update_projectiles(next, blocks, player, enemies, mouse_pos, playerShooting);
    }
  } else {
    //player shooting
    bool destroy = false;
    bullet_collision(enemies, projectile_list_head(projectiles), &destroy);
    if (destroy) {
      projectile_list_t next = projectile_list_copy(projectile_list_rest(projectiles));
      projectile_list_free(projectiles);
      return update_projectiles(next, blocks, player, enemies, mouse_pos, playerShooting);
    }
  }

  projectile_t p;
  floatpoint_t newPos;
  vector_t dir;
  float dist;

  short int bulletType = get_projectile_bullet_type(projectile_list_head(projectiles));
  switch (bulletType) {

    case Buckshot:
    case Bullet:
      newPos = set_floatpoint(get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_x(get_projectile_direction(projectile_list_head(projectiles))), get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_y(get_projectile_direction(projectile_list_head(projectiles))));
      p = set_projectile(newPos, get_projectile_direction(projectile_list_head(projectiles)), bulletType, get_projectile_sprite_pos(projectile_list_head(projectiles)));
      break;

    case Missile:
      dist = sqrt(pow(mouse_pos.x - projectiles->head.realPos.x, 2) + pow(mouse_pos.y - projectiles->head.realPos.y, 2));
      if (dist < 10.0) {
        projectile_list_t tmp = projectile_list_copy(projectile_list_rest(projectiles));
        projectile_list_free(projectiles);
        return update_projectiles(tmp, blocks, player, enemies, mouse_pos, playerShooting);
      }
      dir = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_projectile_real_position(projectiles->head).x + (BULLET_WIDTH / 2)), (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_projectile_real_position(projectiles->head).y + (BULLET_HEIGHT / 2)));
      set_vector_x(&dir, (projectiles->head.dir.x + dir.x) / 100);
      set_vector_y(&dir, (projectiles->head.dir.y + dir.y) / 100);
      dir = normalize(dir);
      dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);
      newPos = set_floatpoint(get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_x(dir), get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_y(dir));
      p = set_projectile(newPos, get_projectile_direction(projectile_list_head(projectiles)), bulletType, get_projectile_sprite_pos(projectile_list_head(projectiles)));
      break;

    default:
      break;

  }

  projectile_list_t tmp = projectile_list_copy(projectile_list_rest(projectiles));
  projectile_list_free(projectiles);

  return projectile_list_build(p, update_projectiles(tmp, blocks, player, enemies, mouse_pos, playerShooting));
}

//check the collision between the projectile and the enemies
void bullet_collision (character_list_t enemies, projectile_t p, bool *destroy) {
  if (character_list_is_empty(enemies)) {
    return ;
  }

  if (get_floatpoint_x(get_projectile_real_position(p)) >= enemies->head.hitbox.x && get_floatpoint_x(get_projectile_real_position(p)) <= enemies->head.hitbox.x + enemies->head.hitbox.w && get_floatpoint_y(get_projectile_real_position(p)) >= enemies->head.hitbox.y && get_floatpoint_y(get_projectile_real_position(p)) <= enemies->head.hitbox.y + enemies->head.hitbox.h && enemies->head.hp > 0) {
    //if there is a collision, we stop searching, we decrease enemy life and returns the updated list
    *destroy = true;
    apply_damage(&enemies->head, 1);
    return;
  }

  bullet_collision(character_list_rest(enemies), p, destroy);
}

//update the positions and hitbox
void update_character (character_t *p, character_list_t *enemies, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], intpoint_t mouse_pos, bool *quit, musicbox_t musicBox) {

  SDL_Rect temp;
  temp.x = (int)floor(get_floatpoint_x(get_character_real_position(*p)));
  temp.y = (int)floor(get_floatpoint_y(get_character_real_position(*p)));
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

  if (get_i_frames_invincible(p->iFrames)) {
    if (SDL_GetTicks() >= get_i_frames_delay(p->iFrames) + DELAY_INVINCIBILITY) {
      set_i_frames_invincible(&p->iFrames, false);
    } else {
      if (SDL_GetTicks() >= get_i_frames_display_delay(p->iFrames) + DELAY_BLINK) {
        set_i_frames_display(&p->iFrames, !get_i_frames_display(p->iFrames));
        set_i_frames_display_delay(&p->iFrames, SDL_GetTicks());
      }
    }
  }

  p->projectiles = update_projectiles(p->projectiles, blocks, p, *enemies, mouse_pos, true);

  *enemies = update_enemies(*enemies, p, blocks, musicBox);

  return;
}

//update the enemies' shots and directions
character_list_t update_enemies (character_list_t c, character_t *p, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], musicbox_t musicBox) {

  if (character_list_is_empty(c)) {
    return character_list_empty();
  }

  if (!is_alive(character_list_head(c))) {
    //if this enemy is dead
    if (character_list_head(c).tts > 25) {
      character_t deadEnemy = character_list_head(c);
      character_list_t tmp = character_list_copy(character_list_rest(c));
      character_list_free(c);
      deadEnemy.projectiles = projectile_list_empty();
      deadEnemy.tts -= 25;
      return character_list_build(deadEnemy, update_enemies(tmp, p, blocks, musicBox));
    } else {
      character_list_t tmp = character_list_copy(character_list_rest(c));
      character_list_free(c);
      return update_enemies(tmp, p, blocks, musicBox);
    }
  }

  character_t e = character_list_head(c);

  if (SDL_GetTicks() > e.shootDelay + ENEMY_SHOOT_DELAY) {
    e.projectiles = shooting(true, e, set_intpoint(get_character_hitbox(*p).x + (IMG_WIDTH / 2), get_character_hitbox(*p).y + (IMG_HEIGHT / 2)), musicBox);
    e.shootDelay = SDL_GetTicks();
  }
  e.projectiles = update_projectiles(projectile_list_copy(e.projectiles), blocks, p, c, set_intpoint((int)floor(get_floatpoint_x(get_character_real_position(*p))), (int)floor(get_floatpoint_y(get_character_real_position(*p)))), false);
  //character_gravity(&e);
  character_apply_velocity(&e, blocks);

  SDL_Rect temp;
  temp.x = (int)floor(get_floatpoint_x(get_character_real_position(e)));
  temp.y = (int)floor(get_floatpoint_y(get_character_real_position(e)));
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

  if (get_i_frames_invincible(e.iFrames)) {
    if (SDL_GetTicks() >= get_i_frames_delay(e.iFrames) + DELAY_INVINCIBILITY) {
      set_i_frames_invincible(&e.iFrames, false);
    } else {
      if (SDL_GetTicks() >= get_i_frames_display_delay(e.iFrames) + DELAY_BLINK) {
        set_i_frames_display(&e.iFrames, !get_i_frames_display(e.iFrames));
        set_i_frames_display_delay(&e.iFrames, SDL_GetTicks());
      }
    }
  }

  character_update_dir(&e, set_intpoint(get_character_hitbox(*p).x + (IMG_WIDTH / 2), get_character_hitbox(*p).y + (IMG_HEIGHT / 2)));

  character_list_t tmp = character_list_copy(character_list_rest(c));
  character_list_free(c);

  return character_list_build(e, update_enemies(tmp, p, blocks, musicBox));
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

  if (p->gridPos.y + 4 >= NB_BLOCKS_HEIGHT || get_block_type(blocks[p->gridPos.x][p->gridPos.y + 4]) == Solid) {
    p->onGround = true;
    p->realPos.y = p->gridPos.y * BLOCK_SIZE;
  }

  if (!p->onGround) {
    p->vel.x *= AIR_ACCELERATION;
  }

  if (p->vel.x < 0.0) {
    if (p->gridPos.x != 0 && (blocks[p->gridPos.x - 1][p->gridPos.y].type != 0 && blocks[p->gridPos.x - 1][p->gridPos.y + 1].type != 0 && blocks[p->gridPos.x - 1][p->gridPos.y + 2].type != 0 && blocks[p->gridPos.x - 1][p->gridPos.y + 3].type != 0)) {
      p->realPos.x += p->vel.x;
    }
  }
  if (p->vel.x > 0.0) {
    if (p->gridPos.x != NB_BLOCKS_WIDTH - 1 && (blocks[p->gridPos.x + 1][p->gridPos.y].type != 0 && blocks[p->gridPos.x + 1][p->gridPos.y + 1].type != 0 && blocks[p->gridPos.x + 1][p->gridPos.y + 2].type != 0 && blocks[p->gridPos.x + 1][p->gridPos.y + 3].type != 0)) {
      p->realPos.x += p->vel.x;
    }
  }

  if (blocks[p->gridPos.x][p->gridPos.y - 1].type == 0) {
    p->vel.y = 4.0;
  }

  if (p->vel.y < 0.0) {
    if (p->gridPos.y != 0 && blocks[p->gridPos.x][p->gridPos.y - 1].type != 0) {
      p->realPos.y += p->vel.y;
    }
  }

  if (p->vel.y > 0.0) {
    if (p->gridPos.y != NB_BLOCKS_HEIGHT - 4 && blocks[p->gridPos.x][p->gridPos.y + 4].type != 0) {
      p->realPos.y += p->vel.y;
    }
  }

  return;
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
    exit(1);
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

//copy the list of character
character_list_t character_list_copy (character_list_t c) {
  if (character_list_is_empty(c)) {
    return character_list_empty();
  }

  return character_list_build(character_list_head(c), character_list_copy(character_list_rest(c)));
}

//free the list of character as well as their projectiles
void character_list_free (character_list_t c) {
  if (character_list_is_empty(c)) {
    return;
  }
  character_list_free(character_list_rest(c));

  if (c == NULL) {
    printf("character_list_t already freed!\n");
    exit(1);
  } else {
    free(c);
    c = NULL;
  }

  return;
}

/* SET */

//create a new character
character_t set_character (short int hp, floatpoint_t position, vector_t velocity, SDL_Rect posSprite, short int type) {

  character_t p;

  set_character_hp(&p, hp);
  set_character_dir(&p, Left);
  set_character_step(&p, 0);
  set_character_type(&p, type);
  set_character_on_ground(&p, false);
  set_character_state(&p, Walking);
  set_character_weapon(&p, Rifle);

  p.tts = 255;

  set_character_step_delay(&p, 0);
  set_character_shoot_delay(&p, 0);

  set_character_real_position(&p, get_floatpoint_x(position), get_floatpoint_y(position));
  SDL_Rect hitbox = {(int)floor(get_floatpoint_x(position)), (int)floor(get_floatpoint_y(position)), IMG_WIDTH, IMG_HEIGHT};
  set_character_hitbox(&p, hitbox);
  set_character_grid_position(&p, (int)floor(get_character_hitbox(p).x / BLOCK_SIZE), (int)floor(get_character_hitbox(p).y / BLOCK_SIZE));

  set_character_projectiles(&p, projectile_list_empty());

  set_character_velocity(&p, velocity.x, velocity.y);
  set_character_sprite_pos(&p, posSprite);

  set_character_i_frames(&p, init_i_frames());

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

//set the weapon
void set_character_weapon (character_t *p, short int weapon) {
  p->weapon = weapon;
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

//set the iFrames
void set_character_i_frames(character_t *p, i_frames_t f) {
  p->iFrames = f;
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

//get the weapon
short int get_character_weapon (character_t p) {
  return p.weapon;
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

//get the iFrames
i_frames_t get_character_i_frames (character_t p) {
  return p.iFrames;
}
