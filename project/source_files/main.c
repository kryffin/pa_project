/* INCLUDES */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../header_files/header.h"
#include "../header_files/2dpoint.h"
#include "../header_files/blocks.h"
#include "../header_files/vector.h"
#include "../header_files/player.h"
#include "../header_files/projectile.h"
#include "../header_files/level.h"
#include "../header_files/var_init.h"
#include "../header_files/menu.h"
#include "../header_files/controls.h"

int main () {

  /* * * * * * fps * * * * * */

  //timer used for the fps delay
  Uint32 *initTimer = NULL;

  //the manager managing the fps
  FPSmanager *manager = NULL;

  /* * * * * * window * * * * * */

  //game window
  SDL_Window *window = NULL;

  //game renderer
  SDL_Renderer *renderer = NULL;

  //temporary surface used for loading the images
  SDL_Surface *temp = NULL;

  //texture of the sprite sheet
  SDL_Texture *player_tSprite = NULL;

  //texture of the cursor
  SDL_Texture *cursor = NULL;

  /* * * * * * keyboard & mouse * * * * * */

  //mouse position
  intpoint_t *mouse_pos = NULL;

  //array for the keys pressed
  SDL_Keycode key[SDL_NUM_SCANCODES] = {0};

  //event running the controls
  SDL_Event *event = NULL;

  //used to know if the player_t jumped
  //  essentially used to avoid the key from being pressed multiple times in one stroke
  bool *jumped = NULL;

  //actual state of the mouse button
  bool *mouse_btn = NULL;

  int *i = NULL;

  /* * * * * * font & colors * * * * * */

  //font used in the game
  TTF_Font *font = NULL;

  //palette of 15 colors
  SDL_Color *colorPalette = NULL;

  /* * * * * * characters * * * * * */

  //the main player_t
  player_t *player = NULL;
  intpoint_t player_pos;
  player_t *enemies = NULL;

  //projectiles of the player_t : array of 100
  projectile_t  *playerProjectiles = NULL;
  projectile_t  *enemyProjectiles = NULL;

  //delay used between each step in the character animation
  int *stepDelay = NULL;

  /* * * * * * game loop * * * * * */

  //variable running the main loop and quitting the game if desired
  bool *quit = NULL;

  Uint32 *timeN_A = NULL;
  Uint32 *timeN_B = NULL;

  Uint32 enemyShootDelay = 0;
  Uint32 playerShootDelay = 0;

  level_t *currLevel = NULL;
  SDL_Texture *blocks_spritesheet = NULL;
  SDL_Texture *background = NULL;

  /* * * * * * initialization * * * * * */

  if (init_variables(&initTimer, &manager, &window, &renderer, &mouse_pos, &event, &jumped, &mouse_btn, &i, &font, &colorPalette, &player, &playerProjectiles, &stepDelay, &quit, &temp, &player_tSprite, &cursor, &timeN_A, &timeN_B, &currLevel, &blocks_spritesheet, &background, &enemies, &enemyProjectiles) == 0) {
    return EXIT_FAILURE;
  }

  //clear the renderer's render
  SDL_RenderClear(renderer);

  //render the present renderer
  SDL_RenderPresent(renderer);


  /* * * * * * player_t initialization * * * * * */

  //base position of the player_t
  floatpoint_t *basePosition = NULL;
  basePosition = (floatpoint_t*)malloc(sizeof(floatpoint_t));
  *basePosition = set_floatpoint((SCREEN_WIDTH / 2) - (IMG_WIDTH / 2), SCREEN_HEIGHT - IMG_HEIGHT);

  //base velocity of the player_t
  vector_t *baseVelocity = NULL;
  baseVelocity = (vector_t*)malloc(sizeof(vector_t));
  *baseVelocity = set_vector(0.0, 0.0);

  //base hitbox
  SDL_Rect *hitbox = NULL;
  hitbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  hitbox->w = IMG_WIDTH;
  hitbox->h = IMG_HEIGHT;

  //the destination rectangle used to load the characters size
  SDL_Rect *desRec = NULL;
  desRec = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  desRec->x = 0;
  desRec->y = 0;
  desRec->w = 32;
  desRec->h = 64;

  //creating the player_t
  *player = set_player(10, *basePosition, *baseVelocity, player_tSprite, *desRec, *hitbox);
  for (*i = 0; *i < 10; *i += 1) {
    enemies[*i] = set_player(0, *basePosition, *baseVelocity, player_tSprite, *desRec, *hitbox);
  }

  //PLACEHOLDER for these won't be used again
  free(basePosition);
  free(baseVelocity);
  free(desRec);
  free(hitbox);

  //rendering the initialization time
  printf("Init time : %u ms\n", SDL_GetTicks() - *initTimer);

  //only used once
  free(initTimer);

  /* * * * * * main menu * * * * * */

  if (render_menu(quit, font, colorPalette, renderer, mouse_pos, cursor) == 0) {
    return EXIT_FAILURE;
  }

  *currLevel = init_level(blocks_spritesheet, background, player, enemies);

  *timeN_A = SDL_GetTicks();

  /* * * * * * main game loop * * * * * */

  //while we are not quitting the game
  while (*quit == false) {

    //clearing the render to the draw color
    SDL_RenderClear(renderer);

    /* * * * * * player_t controls * * * * * */

    controls(event, quit, player, jumped, mouse_pos, mouse_btn, key, timeN_A);

    player_jumping(player);

    //init a projectile_t if shooting
    if (SDL_GetTicks() > playerShootDelay + PLAYER_SHOOT_DELAY) {
      shooting(*mouse_btn, *player, playerProjectiles, *mouse_pos);
      playerShootDelay = SDL_GetTicks();
    }

    //update enemies
    for (*i = 0; *i < 10; *i += 1) {
      if (is_alive(enemies[*i])) {
        //player_gravity(&(enemies)[*i]);
        update_enemy(&(enemies)[*i]);
        player_pos = set_intpoint(get_player_screen_position(*player).x + (IMG_WIDTH / 2), get_player_screen_position(*player).y + (IMG_HEIGHT / 2));
      }
    }

    //enemies shooting
    if (SDL_GetTicks() > enemyShootDelay + ENEMY_SHOOT_DELAY) {
      for (*i = 0; *i < 10; *i += 1) {
        if (is_alive(enemies[*i])) {
          shooting(true, enemies[*i], enemyProjectiles, player_pos);
        }
      }
      enemyShootDelay = SDL_GetTicks();
    }

    update_projectiles(playerProjectiles);
    update_projectiles(enemyProjectiles);

    if (SDL_GetTicks() >= *stepDelay + DELAY_STEP) {
      player_update_step(player);
      *stepDelay = SDL_GetTicks();
    }

    player_apply_velocity(player, currLevel->blocks);
    player_update_dir(player, *mouse_pos);
    player_gravity(player);
    update_player(player, quit);

    //printf("%d :: real : %.2f \t sreen : %d \t hitbox : %d\n", SDL_GetTicks(), player->realPos.y, player->screenPos.y, player->hitbox.y);

    //RAW vertical hyper space
    /*if (player->realPos.x + (IMG_WIDTH / 2) > SCREEN_WIDTH) {
      player->hp = 0;
    }

    if (player->realPos.x + (IMG_WIDTH / 2) < 0) {
      player->realPos.x = SCREEN_WIDTH - IMG_WIDTH;
    }

    //RAW re-enabling double jump
    if (player->dJump == false && player->realPos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
      player->dJump = true;
    }*/

    /* rendering */
    rendering(player, enemies, playerProjectiles, enemyProjectiles, cursor, *currLevel, mouse_pos, renderer);
    if (!is_alive(*player)) {
      game_over(renderer);
    }

    SDL_framerateDelay(manager);

  }

  free_variables(player_tSprite, renderer, window, font, i, playerProjectiles, player, manager, colorPalette, event, quit, jumped, mouse_pos, mouse_btn, timeN_A, timeN_B, currLevel, blocks_spritesheet, background, stepDelay, enemies, enemyProjectiles);

  return EXIT_SUCCESS;
}
