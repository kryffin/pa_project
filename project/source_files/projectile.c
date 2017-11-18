#include "../header_files/projectile.h"

projectile_list_t update_projectiles (projectile_list_t projectiles, block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT]) {

  if (projectile_list_is_empty(projectiles)) {
    return projectile_list_empty();
  }

  if ((get_projectile_real_position(projectile_list_head(projectiles)).x + BULLET_WIDTH < 0.0
        || get_projectile_real_position(projectile_list_head(projectiles)).x > SCREEN_WIDTH)
        || (get_projectile_real_position(projectile_list_head(projectiles)).y + BULLET_HEIGHT < 0.0
        || get_projectile_real_position(projectile_list_head(projectiles)).y > SCREEN_HEIGHT)) {

    //projectile isn't in the screen
    return projectile_list_rest(projectiles);
  }

  if (get_block_type(blocks[(int)floor((get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + (BULLET_WIDTH / 2)) / 16)][(int)floor((get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + (BULLET_HEIGHT / 2)) / 16)]) != Blank) {
    return projectile_list_rest(projectiles);
  }

  projectile_t p;
  floatpoint_t newPos = set_floatpoint(get_floatpoint_x(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_x(get_projectile_direction(projectile_list_head(projectiles))), get_floatpoint_y(get_projectile_real_position(projectile_list_head(projectiles))) + get_vector_y(get_projectile_direction(projectile_list_head(projectiles))));
  SDL_Rect hitbox = {floor(get_floatpoint_x(newPos)), floor(get_floatpoint_y(newPos)), BULLET_WIDTH, BULLET_HEIGHT};

  p = set_projectile(newPos, get_projectile_direction(projectile_list_head(projectiles)), hitbox, get_projectile_sprite_pos(projectile_list_head(projectiles)));

  return projectile_list_build(p, update_projectiles(projectile_list_rest(projectiles), blocks));
}

projectile_list_t projectile_list_build (projectile_t p, projectile_list_t pl) {
  projectile_list_t tmp;
  tmp = malloc(sizeof(*tmp));
  tmp->head = p;
  tmp->next = pl;
  return tmp;
}

projectile_t projectile_list_head (projectile_list_t p) {
  if (projectile_list_is_empty(p)) {
    printf("Reading head of an empty projectile list!");
    exit(0);
  }
  return p->head;
}

projectile_list_t projectile_list_rest (projectile_list_t p) {
  return p->next;
}

bool projectile_list_is_empty (projectile_list_t p) {
  return p == NULL;
}

projectile_list_t projectile_list_empty () {
  return NULL;
}

void projectile_list_free (projectile_list_t p) {
  if (projectile_list_is_empty(p)) {
    return;
  }
  projectile_list_free(projectile_list_rest(p));
  free(p);
}

/* * * * * * Set * * * * * */

projectile_t set_projectile (floatpoint_t pos, vector_t dir, SDL_Rect hitbox, SDL_Rect spritePos) {

  projectile_t p;

  set_projectile_real_position(&p, pos);
  set_projectile_screen_position(&p, floor(get_floatpoint_x(pos)), floor(get_floatpoint_y(pos)));
  set_projectile_direction(&p, dir);
  set_projectile_hitbox(&p, hitbox);
  set_projectile_sprite_pos(&p, spritePos);

  return p;

}

void set_projectile_screen_position (projectile_t *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

void set_projectile_real_position (projectile_t *p, floatpoint_t pos) {
  p->realPos.x = get_floatpoint_x(pos);
  p->realPos.y = get_floatpoint_y(pos);
  return;
}

void set_projectile_direction (projectile_t *p, vector_t dir) {
  p->dir.x = dir.x;
  p->dir.y = dir.y;
  return;
}

void set_projectile_hitbox (projectile_t *p, SDL_Rect hitbox) {
  p->hitbox.x = hitbox.x;
  p->hitbox.y = hitbox.y;
  p->hitbox.w = hitbox.w;
  p->hitbox.h = hitbox.h;
  return;
}

void set_projectile_sprite_pos (projectile_t *p, SDL_Rect spritePos) {
  p->spritePos.x = spritePos.x;
  p->spritePos.y = spritePos.y;
  p->spritePos.w = spritePos.w;
  p->spritePos.h = spritePos.h;
  return;
}

/* * * * * * Get * * * * * */

floatpoint_t get_projectile_real_position (projectile_t p) {
  return p.realPos;
}

intpoint_t get_projectile_screen_position (projectile_t p) {
  return p.screenPos;
}

vector_t get_projectile_direction (projectile_t p) {
  return p.dir;
}

SDL_Rect get_projectile_hitbox (projectile_t p) {
  return p.hitbox;
}

SDL_Rect get_projectile_sprite_pos (projectile_t p) {
  return p.spritePos;
}
