/*

controls.c : contain every functions for the controls regarding the keyboard and mouse

*/

#include "../header_files/controls.h"

//update the controls of the keyboard and mouse
void update_controls (game_t *game) {

  while (SDL_PollEvent(game->event)) {

    if (game->event->type == SDL_QUIT) {
      game->quit = true;
    }

    if (game->event->type == SDL_KEYUP) {
      game->keys[game->event->key.keysym.scancode] = 0;
    }

    if (game->event->type == SDL_KEYDOWN) {

      if (game->event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        game->quit = true;
      }

      game->keys[game->event->key.keysym.scancode] = 1;

    }

    if (game->event->type == SDL_MOUSEMOTION) {
      set_intpoint_x(&game->mouse_pos, game->event->motion.x);
      set_intpoint_y(&game->mouse_pos, game->event->motion.y);
    }
    if (game->event->type == SDL_MOUSEBUTTONUP) {
      game->mouse_btn = false;
    }
    if (game->event->type == SDL_MOUSEBUTTONDOWN) {
      game->mouse_btn = true;
    }

  }

  return;
}

//manages the keyboard inputs
void keyboard_control (game_t *game) {

  //keys :: left, right, jump, melee
  SDL_Keycode keysTab[5] = {SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_F, SDL_SCANCODE_S};

  /* KEYDOWN Controls */

  //'q' or 'a' key
  if (game->keys[keysTab[0]] == 1) {
    if(get_character_state(game->player) != Crouching) {
      set_character_velocity(&game->player, -1 * CHARACTER_SPEED, game->player.vel.y); //set a left velocity
    }
  }

  //'d' key
  if (game->keys[keysTab[1]] == 1) {
    if(get_character_state(game->player) != Crouching) {
      set_character_velocity(&game->player, 1 * CHARACTER_SPEED, game->player.vel.y); //set a left velocity
    }
  }

  //'space' key
  if (game->keys[keysTab[2]] == 1) {
    if (!(game->player.onGround)) {
      set_character_state(&game->player, Walking);
    } else {
      set_character_state(&game->player, Jumping);
      game->player.onGround = false;
    }
    if (SDL_GetTicks() > game->player.jumpDelay + JUMP_DURATION) {
      set_character_state(&game->player, Walking);
    }
  }

  //'f' key
  if (game->keys[keysTab[3]] == 1) {
    set_character_state(&game->player, Attacking);
  }

  //'s' key
  if (game->keys[keysTab[4]] == 1) {
    set_character_state(&game->player, Crouching);
    set_character_velocity(&game->player, 0, game->player.vel.y); //set a left velocity
  }

  /* KEYUP Controls */

  //'q' or 'a' key
  if (game->keys[keysTab[0]] == 0) {
    if (get_character_velocity(game->player).x < 0) {
      set_character_velocity(&game->player, 0, game->player.vel.y);
    }
  }

  //'d' key
  if (game->keys[keysTab[1]] == 0) {
    if (get_character_velocity(game->player).x > 0) {
      set_character_velocity(&game->player, 0, game->player.vel.y);
    }
  }

  //'space' key
  if (game->keys[keysTab[2]] == 0) {
    if (get_character_state(game->player) == Jumping) {
      set_character_state(&game->player, Walking);
      set_character_velocity(&game->player, game->player.vel.x, 0);
    }
    game->player.jumpDelay = SDL_GetTicks();
  }

  //'f' key
  if (game->keys[keysTab[3]] == 0) {
    if (get_character_state(game->player) == Attacking) {
      set_character_state(&game->player, Walking);
    }
  }

  //'s' key
  if (game->keys[keysTab[4]] == 0) {
    if (get_character_state(game->player) == Crouching) {
      set_character_state(&game->player, Walking);
    }
  }

  return;
}

//call the update and control of the keyboard and mouse
void controls (game_t *game) {

  //update the keyboard & mouse controls
  update_controls(game);

  //act depending on the keyboard state
  keyboard_control(game);

  return;
}
