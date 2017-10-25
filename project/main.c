#include "header.h"

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
  player_t *p = NULL;

  //projectiles of the player_t : array of 100
  projectile *projectiles = NULL;

  //delay used between each step in the character animation
  int *stepDelay = NULL;

  /* * * * * * game loop * * * * * */

  //variable running the main loop and quitting the game if desired
  bool *quit = NULL;

  Uint32 *timeN_A = NULL;
  Uint32 *timeN_B = NULL;

  level *currLevel = NULL;
  SDL_Texture *blocks_spritesheet = NULL;
  SDL_Texture *background = NULL;

  /* * * * * * initialization * * * * * */

  if (init_variables(&initTimer, &manager, &window, &renderer, &mouse_pos, &event, &jumped, &mouse_btn, &i, &font, &colorPalette, &p, &projectiles, &stepDelay, &quit, &temp, &player_tSprite, &cursor, &timeN_A, &timeN_B, &currLevel, &blocks_spritesheet, &background) == 0) {
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
  *p = set_player(10, *basePosition, *baseVelocity, player_tSprite, *desRec, *hitbox);

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

  *currLevel = init_level(blocks_spritesheet, background, p);

  *timeN_A = SDL_GetTicks();

  /* * * * * * main game loop * * * * * */

  //while we are not quitting the game
  while (*quit == false) {

    //hashing the time
    *timeN_B = SDL_GetTicks();
    if (*timeN_B >= *timeN_A + 1000) {
      *timeN_A = *timeN_B;
    }

    //clearing the render to the draw color
    SDL_RenderClear(renderer);

    /* * * * * * player_t controls * * * * * */

    controls(event, quit, p, jumped, mouse_pos, mouse_btn, key);

    //player_jumping(p, *timeN_A, *timeN_B);

    player_gravity(p);

    update_player(p, quit);

    //init a projectile if shooting
    shooting(*mouse_btn, *p, projectiles, *mouse_pos);

    update_projectiles(projectiles);

    if (SDL_GetTicks() >= *stepDelay + DELAY_STEP) {
      player_update_step(p);
      *stepDelay = SDL_GetTicks();
    }

    player_apply_velocity(p);
    player_update_dir(p, *mouse_pos);

    //RAW vertical hyper space
    if (p->realPos.x + (IMG_WIDTH / 2) > SCREEN_WIDTH) {
      p->hp = 0;
    }

    if (p->realPos.x + (IMG_WIDTH / 2) < 0) {
      p->realPos.x = SCREEN_WIDTH - IMG_WIDTH;
    }

    //RAW re-enabling double jump
    if (p->dJump == false && p->realPos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
      p->dJump = true;
    }

    /* rendering */
    rendering(p, projectiles, cursor, *currLevel, mouse_pos, renderer);
    if (!is_alive(*p)) {
      game_over(renderer);
    }

    SDL_framerateDelay(manager);

  }

  free_variables(player_tSprite, renderer, window, font, i, projectiles, p, manager, colorPalette, event, quit, jumped, mouse_pos, mouse_btn, timeN_A, timeN_B, currLevel, blocks_spritesheet, background, stepDelay);

  return EXIT_SUCCESS;
}
