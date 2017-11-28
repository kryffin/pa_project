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

  g->currLevel = level_list_empty();

  //main menu
  int menuOption = render_menu(g);
  switch (menuOption) {

    case 1:
      g->currLevel = level_list_build(init_level(PATH_BLOCKS_SHEET, "./res/background1.jpg", "./res/level1.txt", &g->player, &g->enemies, g->renderer), level_list_build( init_level(PATH_BLOCKS_SHEET, "./res/background2.png", "./res/level2.txt", &g->player, &g->enemies, g->renderer), level_list_build( init_level(PATH_BLOCKS_SHEET, PATH_BACKGROUND, "./res/level3.txt", &g->player, &g->enemies, g->renderer), level_list_empty())));
      break;

    case 2:
      g->currLevel = level_list_build(init_level(PATH_BLOCKS_SHEET, PATH_BACKGROUND, "./res/arena.txt", &g->player, &g->enemies, g->renderer), level_list_empty());
      break;

    case 3:
      g->quit = true;
      break;

    default:
      break;
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

    //player
    character_gravity(&g->player);
    character_apply_velocity(&g->player, g->currLevel->head.blocks);

    //enemies
    //character_apply_velocity_ennemies(&g->enemies, g->currLevel->head.blocks, SDL_GetTicks());

    /* updates */
    printf("size ennemies : %d\n", character_list_size(g->enemies));

    //player
    update_character(&g->player, &g->enemies, g->currLevel->head.blocks, &g->quit);
    g->player.projectiles = update_projectiles(g->player.projectiles, g->currLevel->head.blocks, &g->player, g->enemies, true);
    character_update_grid_pos(&g->player);
    character_update_dir(&g->player, g->mouse_pos);

    //enemies


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
      game_over(g->renderer);
    }

    /* fps */

    SDL_framerateDelay(g->manager);

  }

  /* free */

  printf("%lu \n",sizeof(*g));

  projectile_list_free(g->player.projectiles);
  character_list_free(g->enemies);
  level_list_free(g->currLevel);
  SDL_DestroyTexture(g->spriteSheet);
  SDL_DestroyTexture(g->cursor);
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
