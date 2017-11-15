#include "../header_files/header.h"

int main () {

  game_t *g = malloc(sizeof(game_t));
  g = create_game();
  int i;

  //clear the renderer's render
  SDL_RenderClear(g->renderer);

  //render the present renderer
  SDL_RenderPresent(g->renderer);

  /* * * * * * main menu * * * * * */

  if (render_menu(g) == 0) {
    return EXIT_FAILURE;
  }

  /* * * * * * main game loop * * * * * */

  //while we are not quitting the game

  while (!(g->quit)) {

    //clearing the render to the draw color
    SDL_RenderClear(g->renderer);

    /* * * * * * player_t controls * * * * * */

    controls(g);

    player_jumping(&g->player);

    //init a projectile_t if shooting
    if (SDL_GetTicks() > g->player.shootDelay + PLAYER_SHOOT_DELAY) {
      //shooting(*mouse_btn, *player, playerProjectiles, *mouse_pos);
      g->player.shootDelay = SDL_GetTicks();
    }

    //update enemies
    for (i = 0; i < 10; i += 1) {
      if (is_alive(g->enemies[i])) {
        //player_gravity(&(enemies)[i]);
        update_enemy(&(g->enemies)[i]);

        if (SDL_GetTicks() > g->enemies[i].shootDelay + ENEMY_SHOOT_DELAY) {
          shooting(true, g->enemies[i], g->enemyProjectiles, set_intpoint(get_player_screen_position(g->player).x + (IMG_WIDTH / 2), get_player_screen_position(g->player).y + (IMG_HEIGHT / 2)));
          g->enemies[i].shootDelay = SDL_GetTicks();
        }
      }
    }

    update_projectiles(g->playerProjectiles);
    update_projectiles(g->enemyProjectiles);

    if (SDL_GetTicks() >= g->player.stepDelay + DELAY_STEP) {
      player_update_step(&g->player);
      g->player.stepDelay = SDL_GetTicks();
    }

    player_update_grid_pos(&g->player);
    player_apply_velocity(&g->player, g->currLevel.blocks);
    player_update_dir(&g->player, g->mouse_pos);
    player_gravity(&g->player);
    update_player(&g->player, &g->quit);

    if (get_floatpoint_y(get_player_real_position(g->player)) + IMG_HEIGHT > SCREEN_HEIGHT) {
      set_player_real_position(&g->player, get_floatpoint_x(get_player_real_position(g->player)), SCREEN_HEIGHT - IMG_HEIGHT);
      g->player.onGround = true;
    }

    /* rendering */
    rendering(g);
    if (!is_alive(g->player)) {
      game_over(g->renderer);
    }

    SDL_framerateDelay(g->manager);

  }

  SDL_DestroyTexture(g->player.img);
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
