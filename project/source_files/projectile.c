#include "../header_files/projectile.h"

void delete_projectile (projectile_t *p) {

  vector_t dir = set_vector(0.0, 0.0);

  set_projectile_direction(p, dir);
  set_projectile_real_position(p, 0.0, 0.0);

  return;

}

void update_projectiles (projectile_t p[100]) {

  int i;

  for (i = 0; i < 100; i += 1) {

    //if the projectile_t exists
    if (get_projectile_direction(p[i]).x != 0.0 || get_projectile_direction(p[i]).y != 0.0) {

      //if the projectile_t is not in the screen
      if ((get_projectile_real_position(p[i]).x + BULLET_WIDTH < 0.0 || get_projectile_real_position(p[i]).x > SCREEN_WIDTH) || (get_projectile_real_position(p[i]).y + BULLET_HEIGHT < 0.0 || get_projectile_real_position(p[i]).y > SCREEN_HEIGHT)) {

        //delete the projectile
        delete_projectile(&p[i]);

      //if it is in the screen
      } else {

        //update the position of the projectile_t following the direction
        set_projectile_real_position(&p[i], get_projectile_real_position(p[i]).x + get_projectile_direction(p[i]).x, get_projectile_real_position(p[i]).y + get_projectile_direction(p[i]).y);

        //updating the screen position
        set_projectile_screen_position(&p[i], (int)get_projectile_real_position(p[i]).x, (int)get_projectile_real_position(p[i]).y);
        //printf("%d : %d\n----------------%d\n", i, p[i].screenPos.x, SDL_GetTicks());

        //temp rectangle used for the hitbox
        SDL_Rect temp;
        temp.x = get_projectile_screen_position(p[i]).x - (BULLET_WIDTH / 2);
        temp.y = get_projectile_screen_position(p[i]).y - (BULLET_HEIGHT / 2);
        temp.w = get_projectile_hitbox(p[i]).w;
        temp.h = get_projectile_hitbox(p[i]).h;

        //applying the hitbox on the projectile
        set_projectile_hitbox(&p[i], temp);

      }

    }

  }

  return;

}

void render_projectile (projectile_t p[100], SDL_Renderer *renderer) {

  int i;

  for (i = 0; i < 100; i += 1) {

    //if the projectile_t exists
    if (get_projectile_direction(p[i]).x != 0.0 || get_projectile_direction(p[i]).y != 0.0) {

      SDL_Rect tempSpritePos = get_projectile_sprite_pos(p[i]);
      SDL_Rect tempPos = get_projectile_hitbox(p[i]);

      SDL_RenderCopy(renderer, get_projectile_image(p[i]), &tempSpritePos, &tempPos);

    }
  }

  return;

}

/* * * * * * Set * * * * * */

projectile_t set_projectile (float x, float y, vector_t dir, SDL_Rect hitbox, SDL_Rect spritePos, SDL_Texture *img) {

  projectile_t p;

  set_projectile_real_position(&p, x, y);
  set_projectile_screen_position(&p, (int)x, (int)y);
  set_projectile_direction(&p, dir);
  set_projectile_hitbox(&p, hitbox);
  set_projectile_sprite_pos(&p, spritePos);
  set_projectile_image(&p, img);

  return p;

}

void set_projectile_screen_position (projectile_t *p, int x, int y) {
  p->screenPos.x = x;
  p->screenPos.y = y;
  return;
}

void set_projectile_real_position (projectile_t *p, float x, float y) {
  p->realPos.x = x;
  p->realPos.y = y;
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

void set_projectile_image (projectile_t *p, SDL_Texture *img) {
  p->img = img;
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

SDL_Texture* get_projectile_image (projectile_t p) {
  return p.img;
}
