/*

main.c : contain the game loop

*/

#include "../header_files/header.h"

int main () {

  //entire structure of the game
  game_t *g = malloc(sizeof(game_t));
  create_game(g);

  //clear the renderer's render
  SDL_RenderClear(g->renderer);

  //render the present renderer
  SDL_RenderPresent(g->renderer);

  g->currLevel = level_list_empty();

  //main menu
  menu(g);

  while (!(g->quit)) {

    //clearing the render to the draw color
    SDL_RenderClear(g->renderer);

    /* character controls */

    //control the keyboard and mouse inputs
    controls(g);

    /* movement */

    character_update_grid_pos(&g->player);
    character_update_dir(&g->player, g->mouse_pos);
    character_gravity(&g->player);
    character_apply_velocity(&g->player, g->currLevel->head.blocks);

    /* updates */

    //player
    update_character(&g->player, &g->enemies, g->currLevel->head.blocks, g->mouse_pos, &g->quit, g->musicBox);
    //g->player.projectiles = update_projectiles(g->player.projectiles, g->currLevel->head.blocks, &g->player, g->enemies, true);


    if (SDL_GetTicks() >= g->player.stepDelay + DELAY_STEP) {
      character_update_step(&g->player);
      g->player.stepDelay = SDL_GetTicks();
    }

    //debug
    if (get_floatpoint_y(get_character_real_position(g->player)) + IMG_HEIGHT > SCREEN_HEIGHT) {
      set_character_real_position(&g->player, get_floatpoint_x(get_character_real_position(g->player)), SCREEN_HEIGHT - IMG_HEIGHT);
      g->player.onGround = true;
    }

    /* rendering */

    rendering(g);

    //game over screen
    if (!is_alive(g->player)) {
      game_over(*g);
      reset_game(g);
      menu(g);
    }

    /* fps */

    SDL_framerateDelay(g->manager);

  }

  /* free */

  exit_game(g);

  return EXIT_SUCCESS;
}
