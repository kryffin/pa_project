#include "header.h"

void update_controls (SDL_Event *event, SDL_Keycode *keys, bool *quit) {

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
  }
}

void mouse_print (SDL_Texture *img, SDL_Renderer *renderer, SDL_Rect mouse_pos) {
  mouse_pos.x -= CURSOR_WIDTH / 2;
  mouse_pos.y -= CURSOR_HEIGHT / 2;
  mouse_pos.w = CURSOR_WIDTH;
  mouse_pos.h = CURSOR_HEIGHT;
  SDL_RenderCopy(renderer, img, NULL, &mouse_pos);
}

//gestion du click de la souris et de sa position
void mouse_control (SDL_Event *event, SDL_Rect *mouse_pos, bool *mouse_btn) {

  if (event->type == SDL_MOUSEMOTION) {
    mouse_pos->x = event->motion.x;
    mouse_pos->y = event->motion.y;
  }
  if (event->type == SDL_MOUSEBUTTONUP) {
    *mouse_btn = false;
  }
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    *mouse_btn = true;
  }

  return;
}

//gestion des touches du clavier
void keyboard_control (player *p, SDL_Keycode *keys, bool *jumped, SDL_Renderer *renderer, SDL_Rect *display) {

  //keys :: left, right, jump, melee
  SDL_Keycode keysTab[5] = {SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_F, SDL_SCANCODE_S};

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
  if (keys[keysTab[2]] == 1 && *jumped == false) {
    if (get_player_pos(*p).y == display->h - display->w) {
      set_player_state(p, 1);
      set_player_jumpPoint(p, get_player_pos(*p).y);
    } else if (get_player_dJump(*p)) {
      set_player_dJump(p, false);
      set_player_state(p, 2);
      set_player_jumpPoint(p, get_player_pos(*p).y);
    }
    *jumped = true;
  }

  //'f' key
  if (keys[keysTab[3]] == 1) {
    set_player_state(p, 3);
    player_melee(*p, renderer);
  }

  //'s' key
  if (keys[keysTab[4]] == 1) {
    set_player_state(p, 4);
    set_player_vel_x(p, 0); //set a left velocity
  }

  /* KEYUP Controls */

  //'q' or 'a' key
  if (keys[keysTab[0]] == 0) {
    if (get_player_vel_x(*p) < 0) {
      set_player_vel_x(p, 0);
    }
  }

  //'d' key
  if (keys[keysTab[1]] == 0) {
    if (get_player_vel_x(*p) > 0) {
      set_player_vel_x(p, 0);
    }
  }

  //'space' key
  if (keys[keysTab[2]] == 0) {
    *jumped = false;
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

}
