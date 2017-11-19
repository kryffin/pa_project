#include "header.h"

void update_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit, intpoint *mouse_pos, bool *mouse_btn) {

  while (SDL_PollEvent(event)) {

    if (event->type == SDL_QUIT) {
      *quit = true;
    }

    if (event->type == SDL_KEYUP) {
      keys[event->key.keysym.scancode] = 0;
    }

    if (event->type == SDL_KEYDOWN) {

      if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        *quit = true;
      }

      keys[event->key.keysym.scancode] = 1;

    }

    if (event->type == SDL_MOUSEMOTION) {
      set_intpoint_x(mouse_pos, event->motion.x);
      set_intpoint_y(mouse_pos, event->motion.y);
    }
    if (event->type == SDL_MOUSEBUTTONUP) {
      *mouse_btn = false;
    }
    if (event->type == SDL_MOUSEBUTTONDOWN) {
      *mouse_btn = true;
    }

  }

  return;

}

void render_cursor (SDL_Texture *img, SDL_Renderer *renderer, intpoint mouse_pos) {

  SDL_Rect temp;
  temp.x = get_intpoint_x(mouse_pos) - (CURSOR_WIDTH/2);
  temp.y = get_intpoint_y(mouse_pos) - (CURSOR_HEIGHT/2);
  temp.w = CURSOR_WIDTH;
  temp.h = CURSOR_HEIGHT;

  SDL_RenderCopy(renderer, img, NULL, &temp);

  return;
}

//gestion des touches du clavier
void keyboard_control (player *p, SDL_Keycode *keys, bool *jumped) {

  //keys :: left, right, jump, melee
  SDL_Keycode keysTab[9] = {SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_F, SDL_SCANCODE_S, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_C, SDL_SCANCODE_N};

  /* KEYDOWN Controls */

  //'q' or 'a' key
  if (keys[keysTab[0]] == 1) {
    if(get_player_state(*p) != 4) {
      set_player_vel_x(p, -3); //set a left velocity
    }
  }

  //'d' key
  if (keys[keysTab[1]] == 1) {
    if(get_player_state(*p) != 4) {
      set_player_vel_x(p, 3); //set a left velocity
    }
  }

  //'space' key
 if (keys[keysTab[2]] == 1 && get_player_dJump(*p)== true) {
     set_player_state(p, 1);
     set_player_vel_y (p, JUMP_HEIGHT);
     set_player_real_position(p, get_player_real_position(*p).x, get_player_real_position(*p).y -BLOCK_WIDTH );
     set_player_dJump(p, false);
 }

  //'f' key
  if (keys[keysTab[3]] == 1) {
    set_player_state(p, 3);
  }

  //'s' key
  if (keys[keysTab[4]] == 1) {
    set_player_state(p, 4);
    set_player_vel_x(p, 0); //set a left velocity
  }

  /* KEYUP Controls */

  //'q' or 'a' key
  if (keys[keysTab[0]] == 0) {
    if (get_player_velocity(*p).x < 0) {
      set_player_vel_x(p, 0);
    }
  }

  //'d' key
  if (keys[keysTab[1]] == 0) {
    if (get_player_velocity(*p).x > 0) {
      set_player_vel_x(p, 0);
    }
  }


  //'f' key
  if (keys[keysTab[3]] == 0) {
    if (get_player_state(*p) == 3) {
      set_player_state(p, 0);
    }
  }

  //'s' key
  if (keys[keysTab[4]] == 0) {
    if (get_player_state(*p) == 4) {
      set_player_state(p, 0);
    }
  }
  //'1' key
  if (keys[keysTab[5]] == 1) {
    p->gunType = 1;
  }
  //'2' key (game)//GTA MAGGLE
  if (keys[keysTab[6]] == 1) {
    p->gunType = 2;
  }

  //'C' key
  if (keys[keysTab[7]] == 1){
    keys[keysTab[7]] == 0;
    p->currLevel =1;
    printf("level %d\n", p->currLevel);

  }

}

void controls (SDL_Event *event, bool *quit, player *p, bool *jumped, SDL_Renderer *renderer, intpoint *mouse_pos, bool *mouse_btn, SDL_Texture *cursor, SDL_Keycode *key) {

  //update the keyboard & mouse controls
  update_controls(event, key, quit, mouse_pos, mouse_btn);

  //act depending on the keyboard state
  keyboard_control(p, key, jumped);

  return;

}
