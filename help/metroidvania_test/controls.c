#include "header.h"

void control (SDL_Event event, player *p, bool *exit) {

  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {

          //'q' key for left
          case SDLK_q:
            set_player_vel_x(p, -20); //set a left velocity
            set_player_dir(p, 0); //turn the player towards left
            break;

          //'d' key for right
          case SDLK_d:
            set_player_vel_x(p, 20); //set a right velocity
            set_player_dir(p, 1); //turn the player towards right
            break;

          //'space' or 'z' to jump
          case SDLK_SPACE:
            if (get_player_pos(*p).y == SCREEN_HEIGHT - IMG_HEIGHT) {
              set_player_state(p, 1);
              set_player_jumpPoint(p, get_player_pos(*p).y);
            } else if (get_player_dJump(*p)) {
              set_player_dJump(p, false);
              set_player_state(p, 2);
              set_player_jumpPoint(p, get_player_pos(*p).y);
            }
            break;

          case SDLK_LSHIFT:
            if (get_player_dash(*p) && get_player_state(*p) != 3) {
              set_player_state(p, 3);
              set_player_dash(p, false);
            }
            break;

          //'esc' to quit
          case SDLK_ESCAPE:
            *exit = true;
            break;

          default:
            break;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {

          //'q' key for left
          case SDLK_q:
            if (get_player_vel_x(*p) < 0) {
              set_player_vel_x(p, 0);
            }
            break;

          //'d' key for right
          case SDLK_d:
            if (get_player_vel_x(*p) > 0) {
              set_player_vel_x(p, 0);
            }
            break;

          //'space' to jump
          case SDLK_SPACE:
            //nothing happens
            break;

          default:
            break;
        }
        break;

      default:
        break;
    }
  }

}
