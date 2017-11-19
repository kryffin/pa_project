/*

main.c : contain the game loop

*/

#include "../header_files/header.h"

int main () {

  //entire structure of the game
  game_t *g = malloc(sizeof(game_t));
  g = create_game();

  //clear the renderer's render
  SDL_RenderClear(g->renderer);

  //render the present renderer
  SDL_RenderPresent(g->renderer);

  //main menu
  if (render_menu(g) == 0) {
    return EXIT_FAILURE;
  }

  while (!(g->quit)) {

    //clearing the render to the draw color
    SDL_RenderClear(g->renderer);

    /* character controls */

    //control the keyboard and mouse inputs
    controls(g);

    //add a new projectile to the list if right mouse button is clicked
    if (SDL_GetTicks() > g->player.shootDelay + PLAYER_SHOOT_DELAY) {
      shooting(g->mouse_btn, &g->player, g->mouse_pos);
      g->player.shootDelay = SDL_GetTicks();
    }

    /* movement */

    character_jumping(&g->player);
    character_gravity(&g->player);
    character_apply_velocity(&g->player, g->currLevel.blocks);

    /* updates */

    //player
    update_character(&g->player, &g->quit);
    g->player.projectiles = update_projectiles(g->player.projectiles, g->currLevel.blocks);
    character_update_grid_pos(&g->player);
    character_update_dir(&g->player, g->mouse_pos);

    if (SDL_GetTicks() >= g->player.stepDelay + DELAY_STEP) {
      character_update_step(&g->player);
      g->player.stepDelay = SDL_GetTicks();
    }

    //enemies
    g->enemies = update_enemies(g->enemies, g->player, g->currLevel.blocks);

    //debug
    if (get_floatpoint_y(get_character_real_position(g->player)) + IMG_HEIGHT > SCREEN_HEIGHT) {
      set_character_real_position(&g->player, get_floatpoint_x(get_character_real_position(g->player)), SCREEN_HEIGHT - IMG_HEIGHT);
      g->player.onGround = true;
    }

    /* rendering */

    rendering(g);

    //game over screen
    if (!is_alive(g->player)) {
      game_over(g->renderer);
    }

    /* fps */

    SDL_framerateDelay(g->manager);

  }

  /* free */

  projectile_list_free(g->player.projectiles);
  character_list_free(g->enemies);
  SDL_DestroyTexture(g->spriteSheet);
  SDL_DestroyTexture(g->currLevel.blocks_spritesheet);
  SDL_DestroyTexture(g->currLevel.background);
  SDL_DestroyRenderer(g->renderer);
  SDL_DestroyWindow(g->window);
  TTF_CloseFont(g->font);

  TTF_Quit();
  SDL_Quit();

  free(g->manager);
  free(g->colorPalette);
  free(g->event);
  free(g);

  return EXIT_SUCCESS;
}
