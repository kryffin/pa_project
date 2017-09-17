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

void control (player *p, SDL_Keycode *keys, bool *jumped, SDL_Renderer *renderer, SDL_Rect *display) {

  //keys :: left, right, jump, melee
  SDL_Keycode keysTab[5] = {SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_F, SDL_SCANCODE_S};

  /* KEYDOWN Controls */

  //'q' or 'a' key
  if (keys[keysTab[0]] == 1) {
    set_player_vel_x(p, -3); //set a left velocity
    set_player_dir(p, 0); //turn the player towards left
  }

  //'d' key
  if (keys[keysTab[1]] == 1) {
    set_player_vel_x(p, 3); //set a left velocity
    set_player_dir(p, 1); //turn the player towards left
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

  //'z' or 'w' key
  if (keys[keysTab[4]] == 1) {
    set_player_state(p, 4);
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

  //'z' or 'w' key
  if (keys[keysTab[4]] == 0) {
    if (get_player_state(*p) == 4) {
      set_player_state(p, 0);
    }
  }

}
