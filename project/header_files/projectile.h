#ifndef PROJECTILE_H
#define PROJECTILE_H

typedef struct Projectile {
  floatpoint_t realPos;

  vector_t dir; //direction
  intpoint_t screenPos; //screen position
  SDL_Rect hitbox; //hitbox
  SDL_Rect spritePos; //position in the sprite sheet

  SDL_Texture *img; //img used
} projectile_t ;

/* projectile.c */
void delete_projectile (projectile_t *p);
void shooting (bool mouse_btn, player_t p, projectile_t proj[100], intpoint_t mouse_pos);
void update_projectiles (projectile_t p[100]);
void render_projectile (projectile_t p[100], SDL_Renderer *renderer);
projectile_t set_projectile (float x, float y, vector_t dir, SDL_Rect hitbox, SDL_Rect spritePos, SDL_Texture *img);
void set_projectile_screen_position (projectile_t *p, int x, int y);
void set_projectile_real_position (projectile_t *p, float x, float y);
void set_projectile_direction (projectile_t *p, vector_t dir);
void set_projectile_hitbox (projectile_t *p, SDL_Rect hitbox);
void set_projectile_image (projectile_t *p, SDL_Texture *img);
void set_projectile_sprite_pos (projectile_t *p, SDL_Rect spritePos);
floatpoint_t get_projectile_real_position (projectile_t p);
intpoint_t get_projectile_screen_position (projectile_t p);
vector_t get_projectile_direction (projectile_t p);
SDL_Rect get_projectile_hitbox (projectile_t p);
SDL_Rect get_projectile_sprite_pos (projectile_t p);
SDL_Texture* get_projectile_image (projectile_t p);

#endif
