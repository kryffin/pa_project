#include "header.h"

void shooting (bool mouse_btn, player p, projectile proj[100], intpoint mouse_pos) {

  vector dir = set_vector(1.0, 0.0);

  int i;

  if (mouse_btn) {

    //if clicking we shoot
    for (i = 0; i < 100; i += 1) {

      //if a projectile has no direction it doesn't exists
      if (get_projectile_direction(proj[i]).x == 0 && get_projectile_direction(proj[i]).y == 0) {
        printf("%d\n", i);
        set_projectile_direction(&proj[i], dir);
        return;
      }

    }

  }

  //security check
  return;

}

void update_projectiles (projectile *p[100]) {

  int i;

  for (i = 0; i < 100; i += 1) {

    //if the projectile exists
    if (get_projectile_direction((*p)[i]).x != 0.0 || get_projectile_direction((*p)[i]).y != 0.0) {
      set_projectile_screen_position(p[i], (int)get_projectile_real_position((*p)[i]).x, (int)get_projectile_real_position((*p)[i]).y);

      SDL_Rect temp;
      temp.x = get_projectile_screen_position((*p)[i]).x;
      temp.y = get_projectile_screen_position((*p)[i]).y;
      temp.w = get_projectile_hitbox((*p)[i]).w;
      temp.h = get_projectile_hitbox((*p)[i]).h;

      set_projectile_hitbox(p[i], temp);
    }

  }

  return;

}

void render_projectile (projectile p[100], SDL_Renderer *renderer) {

  SDL_Rect *tempSpritePos = NULL;
  tempSpritePos = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *tempPos = NULL;
  tempPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < 100; *i += 1) {
    if (get_projectile_direction(p[*i]).x != 0.0 || get_projectile_direction(p[*i]).y != 0.0) {

      tempSpritePos->x = get_projectile_sprite_pos(p[*i]).x;
      tempSpritePos->y = get_projectile_sprite_pos(p[*i]).y;
      tempSpritePos->w = get_projectile_sprite_pos(p[*i]).w;
      tempSpritePos->h = get_projectile_sprite_pos(p[*i]).h;

      *tempPos = get_projectile_hitbox(p[*i]);

      SDL_RenderCopy(renderer, get_projectile_image(p[*i]), tempSpritePos, tempPos);

    }
  }

  free(tempSpritePos);
  free(tempPos);
  free(i);

  return;

}

/* * * * * * Set * * * * * */

projectile set_projectile (float x, float y, vector dir, SDL_Rect hitbox, SDL_Rect spritePos, SDL_Texture *img) {

  projectile p;

  set_projectile_real_position(&p, x, y);
  set_projectile_screen_position(&p, (int)x, (int)y);
  set_projectile_direction(&p, dir);
  set_projectile_hitbox(&p, hitbox);
  set_projectile_sprite_pos(&p, spritePos);
  set_projectile_image(&p, img);

  return p;

}

void set_projectile_screen_position (projectile *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

void set_projectile_real_position (projectile *p, float x, float y) {
  p->realPos.x = x;
  p->realPos.y = y;
  return;
}

void set_projectile_direction (projectile *p, vector dir) {
  p->dir.x = dir.x;
  p->dir.y = dir.y;
  return;
}

void set_projectile_hitbox (projectile *p, SDL_Rect hitbox) {
  p->hitbox.x = hitbox.x;
  p->hitbox.y = hitbox.y;
  return;
}

void set_projectile_sprite_pos (projectile *p, SDL_Rect spritePos) {
  p->spritePos.x = spritePos.x;
  p->spritePos.y = spritePos.y;
  return;
}

void set_projectile_image (projectile *p, SDL_Texture *img) {
  p->img = img;
  return;
}

/* * * * * * Get * * * * * */

floatpoint get_projectile_real_position (projectile p) {
  return p.realPos;
}

intpoint get_projectile_screen_position (projectile p) {
  return p.screenPos;
}

vector get_projectile_direction (projectile p) {
  return p.dir;
}

SDL_Rect get_projectile_hitbox (projectile p) {
  return p.hitbox;
}

SDL_Rect get_projectile_sprite_pos (projectile p) {
  return p.spritePos;
}

SDL_Texture* get_projectile_image (projectile p) {
  return p.img;
}
