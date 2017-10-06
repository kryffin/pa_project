#include "header.h"

void init_projectile (bool mouse_btn, player p, SDL_Texture *spriteSheet, projectile proj[100], SDL_Rect mouse_pos) {

  SDL_Rect *tempPos = NULL;
  tempPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  tempPos->x = get_player_pos(p).x;
  tempPos->y = get_player_pos(p).y;
  tempPos->w = 16;
  tempPos->h = 16;

  SDL_Rect *tempDir = NULL;
  tempDir = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  tempDir->x = mouse_pos.x - tempPos->x; //something to get the direction
  tempDir->y = mouse_pos.y - tempPos->y; //something to get the direction

  if (mouse_btn) {
    proj[0] = set_projectile(get_player_pos(p).x, get_player_pos(p).y, *tempDir, *tempPos, spriteSheet);
  }

  free(tempDir);
  free(tempPos);

  return;

}

void render_projectile (projectile p[100], SDL_Renderer *renderer) {

  //temp rect used to define the area in the spritesheet
  SDL_Rect *temp = NULL;
  temp = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  temp->x = 128;
  temp->y = 128;
  temp->w = 16;
  temp->h = 16;

  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < 100; *i += 1) {
    if (get_projectile_position(p[*i]).x != 0) {
      SDL_RenderCopy(renderer, get_projectile_image(p[*i]), temp, &(p[*i].pos));
    }
  }

  free(temp);

  return;

}

/* * * * * * Set * * * * * */

projectile set_projectile (float realPosX, float realPosY, SDL_Rect dir, SDL_Rect pos, SDL_Texture *img) {

  projectile p;

  set_projectile_real_position_x(&p, realPosX);
  set_projectile_real_position_y(&p, realPosY);
  set_projectile_direction(&p, dir);
  set_projectile_position(&p, pos);
  set_projectile_image(&p, img);

  return p;

}

void set_projectile_real_position_x (projectile *p, float realPosX) {
  p->realPosX = realPosX;
  return;
}

void set_projectile_real_position_y (projectile *p, float realPosY) {
  p->realPosY = realPosY;
  return;
}

void set_projectile_direction (projectile *p, SDL_Rect dir) {
  p->dir.x = dir.x;
  p->dir.y = dir.y;
  return;
}

void set_projectile_position (projectile *p, SDL_Rect pos) {
  p->pos.x = pos.x;
  p->pos.y = pos.y;
  p->pos.w = pos.w;
  p->pos.h = pos.h;
  return;
}

void set_projectile_image (projectile *p, SDL_Texture *img) {
  p->img = img;
  return;
}

/* * * * * * Get * * * * * */

float get_projectile_real_position_x (projectile p) {
  return p.realPosX;
}

float get_projectile_real_position_y (projectile p) {
  return p.realPosY;
}

SDL_Rect get_projectile_direction (projectile p) {
  return p.dir;
}

SDL_Rect get_projectile_position (projectile p) {
  return p.pos;
}

SDL_Texture* get_projectile_image (projectile p) {
  return p.img;
}
