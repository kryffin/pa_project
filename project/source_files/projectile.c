/*

projectile.c : contain the functions for the projectiles

*/

#include "../header_files/projectile.h"

/* LIST */

//build a new projectile on the list
projectile_list_t projectile_list_build (projectile_t p, projectile_list_t pl) {
  projectile_list_t tmp;
  tmp = malloc(sizeof(*tmp));
  tmp->head = p;
  tmp->next = pl;
  return tmp;
}

//returns the head of the list
projectile_t projectile_list_head (projectile_list_t p) {
  if (projectile_list_is_empty(p)) {
    printf("Reading head of an empty projectile list!");
    exit(0);
  }
  return p->head;
}

//returns the rest of the projectile list
projectile_list_t projectile_list_rest (projectile_list_t p) {
  return p->next;
}

//check if the list is empty
bool projectile_list_is_empty (projectile_list_t p) {
  return p == NULL;
}

//returns an empty list
projectile_list_t projectile_list_empty () {
  return NULL;
}

//free a list
void projectile_list_free (projectile_list_t p) {
  if (projectile_list_is_empty(p)) {
    return;
  }
  projectile_list_free(projectile_list_rest(p));
  free(p);
  return;
}

/* SET */

//create a new projectile
projectile_t set_projectile (floatpoint_t pos, vector_t dir, SDL_Rect hitbox, SDL_Rect spritePos) {

  projectile_t p;

  set_projectile_real_position(&p, pos);
  set_projectile_screen_position(&p, floor(get_floatpoint_x(pos)), floor(get_floatpoint_y(pos)));
  set_projectile_direction(&p, dir);
  set_projectile_hitbox(&p, hitbox);
  set_projectile_sprite_pos(&p, spritePos);

  return p;

}

//set the screen position
void set_projectile_screen_position (projectile_t *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

//set the real position
void set_projectile_real_position (projectile_t *p, floatpoint_t pos) {
  p->realPos.x = get_floatpoint_x(pos);
  p->realPos.y = get_floatpoint_y(pos);
  return;
}

//set the direction
void set_projectile_direction (projectile_t *p, vector_t dir) {
  p->dir.x = dir.x;
  p->dir.y = dir.y;
  return;
}

//set the hitbox
void set_projectile_hitbox (projectile_t *p, SDL_Rect hitbox) {
  p->hitbox.x = hitbox.x;
  p->hitbox.y = hitbox.y;
  p->hitbox.w = hitbox.w;
  p->hitbox.h = hitbox.h;
  return;
}

//set the sprite position on the sprite sheet
void set_projectile_sprite_pos (projectile_t *p, SDL_Rect spritePos) {
  p->spritePos.x = spritePos.x;
  p->spritePos.y = spritePos.y;
  p->spritePos.w = spritePos.w;
  p->spritePos.h = spritePos.h;
  return;
}

/* GET */

//get the real position
floatpoint_t get_projectile_real_position (projectile_t p) {
  return p.realPos;
}

//get the screen position
intpoint_t get_projectile_screen_position (projectile_t p) {
  return p.screenPos;
}

//get the direction
vector_t get_projectile_direction (projectile_t p) {
  return p.dir;
}

//get the hitbox
SDL_Rect get_projectile_hitbox (projectile_t p) {
  return p.hitbox;
}

//get the sprite position on the sprite sheet
SDL_Rect get_projectile_sprite_pos (projectile_t p) {
  return p.spritePos;
}
