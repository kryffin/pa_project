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

      if (game->event->key.keysym.scancode == SDL_SCANCODE_A) {
        game->keys[KeyQ] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_S) {
        game->keys[KeyS] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_D) {
        game->keys[KeyD] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_F) {
        game->keys[KeyF] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
        game->keys[KeySpace] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_1) {
        game->keys[Key1] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_2) {
        game->keys[Key2] = false;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_3) {
        game->keys[Key3] = false;
      }

    }

    if (game->event->type == SDL_KEYDOWN) {

      if (game->event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        game->quit = true;
      }

      if (game->event->key.keysym.scancode == SDL_SCANCODE_A) {
        game->keys[KeyQ] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_S) {
        game->keys[KeyS] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_D) {
        game->keys[KeyD] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_F) {
        game->keys[KeyF] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
        game->keys[KeySpace] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_1) {
        game->keys[Key1] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_2) {
        game->keys[Key2] = true;
      }
      if (game->event->key.keysym.scancode == SDL_SCANCODE_3) {
        game->keys[Key3] = true;
      }

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

  /* KEYDOWN Controls */

  //'q' key
  if (game->keys[KeyQ] == true) {
    if(get_character_state(game->player) != Crouching) {
      set_character_velocity(&game->player, -1 * CHARACTER_SPEED, game->player.vel.y); //set a left velocity
    }
  }

  //'d' key
  if (game->keys[KeyD] == true) {
    if(get_character_state(game->player) != Crouching) {
      set_character_velocity(&game->player, 1 * CHARACTER_SPEED, game->player.vel.y); //set a left velocity
    }
  }

  //'space' key
  if (game->keys[KeySpace] == true) {
    if (!(game->player.onGround)) {
      set_character_state(&game->player, Walking);
    } else {
      set_character_state(&game->player, Jumping);
      character_jumping(&game->player);
      game->player.onGround = false;
    }
  }

  //'f' key
  if (game->keys[KeyF] == true) {
    set_character_state(&game->player, Attacking);
  }

  //'s' key
  if (game->keys[KeyS] == true) {
    set_character_state(&game->player, Crouching);
    set_character_velocity(&game->player, 0, game->player.vel.y); //set a left velocity

    //debug
    if (!level_list_is_empty(level_list_rest(game->currLevel))) {
      game->currLevel = level_list_rest(game->currLevel);
    }
    set_character_weapon(&game->player, Bazooka);
  }

  //'space' key
  if (game->keys[Key1] == true) {
    set_character_weapon(&game->player, Rifle);
  }

  //'f' key
  if (game->keys[Key2] == true) {
    set_character_weapon(&game->player, Shotgun);
  }

  //'s' key
  if (game->keys[Key3] == true) {
    set_character_weapon(&game->player, Bazooka);
  }

  /* KEYUP Controls */

  //'q' key
  if (game->keys[KeyQ] == false) {
    if (get_character_velocity(game->player).x < 0) {
      set_character_velocity(&game->player, 0, game->player.vel.y);
    }
  }

  //'d' key
  if (game->keys[KeyD] == false) {
    if (get_character_velocity(game->player).x > 0) {
      set_character_velocity(&game->player, 0, game->player.vel.y);
    }
  }

  //'space' key
  if (game->keys[KeySpace] == false) {
    if (get_character_state(game->player) == Jumping) {
      set_character_state(&game->player, Walking);
      set_character_velocity(&game->player, game->player.vel.x, 0);
    }
  }

  //'f' key
  if (game->keys[KeyF] == false) {
    if (get_character_state(game->player) == Attacking) {
      set_character_state(&game->player, Walking);
    }
  }

  //'s' key
  if (game->keys[KeyS] == false) {
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

  //add a new projectile to the list if right mouse button is clicked
  short int weapon = get_character_weapon(game->player);
  int shoot_delay = 0;

  switch (weapon) {

    case Rifle:
      shoot_delay = RIFLE_SHOOT_DELAY;
      break;

    case Shotgun:
      shoot_delay = SHOTGUN_SHOOT_DELAY;
      break;

    case Bazooka:
      shoot_delay = BAZOOKA_SHOOT_DELAY;
      break;

    default:
      break;

  }
  if (SDL_GetTicks() > game->player.shootDelay + shoot_delay) {
    shooting(game->mouse_btn, &game->player, game->mouse_pos);
    game->player.shootDelay = SDL_GetTicks();
  }

  return;
}
