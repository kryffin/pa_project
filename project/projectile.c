#include "header.h"

void delete_projectile (projectile *p) {

  vector dir = set_vector(0.0, 0.0);

  set_projectile_direction(p, dir);
  set_projectile_real_position(p, 0.0, 0.0);

  return;

}

void shooting (bool mouse_btn, player p, projectile proj[100], intpoint mouse_pos) {

  vector dir = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_player_real_position(p).x + (IMG_WIDTH / 2)), (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_player_real_position(p).y + (IMG_HEIGHT / 2)));
  vector dir2 = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_player_real_position(p).x + (IMG_WIDTH / 2)) +20, (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_player_real_position(p).y + (IMG_HEIGHT / 2))+20);
  vector dir3 = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - (get_player_real_position(p).x + (IMG_WIDTH / 2)) -20, (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - (get_player_real_position(p).y + (IMG_HEIGHT / 2))-20);
  int i;

  switch (p.gunType){
    case 1:

      dir = normalize(dir);

      dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);



      if (mouse_btn) {

        //if clicking we shoot
        for (i = 0; i < 100; i += 1) {

          //if a projectile has no direction it doesn't exists
          if (get_projectile_direction(proj[i]).x == 0.0 && get_projectile_direction(proj[i]).y == 0.0) {

            set_projectile_real_position(&proj[i], (get_player_real_position(p).x + (IMG_WIDTH / 2)) - (BULLET_WIDTH / 2), (get_player_real_position(p).y + (IMG_HEIGHT / 2)) - (BULLET_HEIGHT / 2));
            set_projectile_direction(&proj[i], dir);

            return;
          }

        }

      }
      break;
    case 2:
      dir = normalize(dir);
      dir = set_vector(get_vector_x(dir) * BULLET_SPEED_SG, get_vector_y(dir) * BULLET_SPEED_SG);
      dir2 = normalize(dir2);
      dir2 = set_vector(get_vector_x(dir2) * BULLET_SPEED_SG, get_vector_y(dir2) * BULLET_SPEED_SG);
      dir3 = normalize(dir3);
      dir3 = set_vector(get_vector_x(dir3) * BULLET_SPEED_SG, get_vector_y(dir3) * BULLET_SPEED_SG);



      if (mouse_btn) {

        //if clicking we shoot
        for (i = 0; i < 99; i += 3) {

          //if a projectile has no direction it doesn't exists
          if (get_projectile_direction(proj[i]).x == 0.0 && get_projectile_direction(proj[i]).y == 0.0) {

            set_projectile_real_position(&proj[i], (get_player_real_position(p).x + (IMG_WIDTH / 2)) - (BULLET_WIDTH / 2), (get_player_real_position(p).y + (IMG_HEIGHT / 2)) - (BULLET_HEIGHT / 2));
            set_projectile_direction(&proj[i], dir);

            set_projectile_real_position(&proj[i+1], (get_player_real_position(p).x + (IMG_WIDTH / 2)) - (BULLET_WIDTH / 2), (get_player_real_position(p).y + (IMG_HEIGHT / 2)) - (BULLET_HEIGHT / 2));
            set_projectile_direction(&proj[i+1], dir2);

            set_projectile_real_position(&proj[i+2], (get_player_real_position(p).x + (IMG_WIDTH / 2)) - (BULLET_WIDTH / 2), (get_player_real_position(p).y + (IMG_HEIGHT / 2)) - (BULLET_HEIGHT / 2));
            set_projectile_direction(&proj[i+2], dir3);

            return;
          }

        }

      }
      break;

    case 3:

      /*dir = normalize(dir);
      dir = set_vector(get_vector_x(dir) * BULLET_SPEED, get_vector_y(dir) * BULLET_SPEED);

          //if clicking we shoot
          for (i = 0; i < 100; i += 1) {
            //if a projectile has no direction it doesn't exists
            //if (get_projectile_direction(proj[0]).x == 0.0 && get_projectile_direction(proj[0]).y == 0.0) {

              set_projectile_real_position(&proj[0], (get_player_real_position(p).x + (IMG_WIDTH / 2)) - (BULLET_WIDTH / 2), (get_player_real_position(p).y + (IMG_HEIGHT / 2)) - (BULLET_HEIGHT / 2));
              set_projectile_direction(&proj[0], dir);

            //}

            dir2 = calcul_vector_p_m(dir, mouse_pos);
            set_projectile_real_position(&proj[0], get_projectile_real_position(proj[0]).x + dir2.x, get_projectile_real_position(proj[0]).y + dir2.y);
            set_projectile_direction(&proj[0], dir);


          }
*/

      break;

    } //end switch
  //security check
  return;

}

vector calcul_vector_p_m (vector dir, intpoint mouse_pos)
{
    vector dir2 = set_vector((get_intpoint_x(mouse_pos) + (CURSOR_WIDTH / 2)) - dir.x, (get_intpoint_y(mouse_pos) + (CURSOR_HEIGHT / 2)) - dir.y);
    return dir2;

}
void update_projectiles (projectile p[100]) {

  int i;

  for (i = 0; i < 100; i += 1) {

    //if the projectile exists
    if (get_projectile_direction(p[i]).x != 0.0 || get_projectile_direction(p[i]).y != 0.0) {

      //if the projectile is not in the screen
      if ((get_projectile_real_position(p[i]).x + BULLET_WIDTH < 0.0 || get_projectile_real_position(p[i]).x > SCREEN_WIDTH) || (get_projectile_real_position(p[i]).y + BULLET_HEIGHT < 0.0 || get_projectile_real_position(p[i]).y > SCREEN_HEIGHT)) {

        //delete the projectile
        delete_projectile(&p[i]);

      //if it is in the screen
      } else {

        //update the position of the projectile following the direction
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

void render_projectile (projectile p[100], SDL_Renderer *renderer) {

  int i;

  for (i = 0; i < 100; i += 1) {

    //if the projectile exists
    if (get_projectile_direction(p[i]).x != 0.0 || get_projectile_direction(p[i]).y != 0.0) {

      SDL_Rect tempSpritePos = get_projectile_sprite_pos(p[i]);
      SDL_Rect tempPos = get_projectile_hitbox(p[i]);

      SDL_RenderCopy(renderer, get_projectile_image(p[i]), &tempSpritePos, &tempPos);

    }
  }

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
  p->hitbox.w = hitbox.w;
  p->hitbox.h = hitbox.h;
  return;
}

void set_projectile_sprite_pos (projectile *p, SDL_Rect spritePos) {
  p->spritePos.x = spritePos.x;
  p->spritePos.y = spritePos.y;
  p->spritePos.w = spritePos.w;
  p->spritePos.h = spritePos.h;
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
