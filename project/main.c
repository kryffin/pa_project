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
  SDL_Texture *playerSprite = NULL;

  //texture of the cursor
  SDL_Texture *cursor = NULL;

  /* * * * * * keyboard & mouse * * * * * */

  //mouse position
  intpoint *mouse_pos = NULL;

  //array for the keys pressed
  SDL_Keycode key[SDL_NUM_SCANCODES] = {0};

  //event running the controls
  SDL_Event *event = NULL;

  //used to know if the player jumped
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

  /* * * * * * messages * * * * * */

  //message stating the current player state
  SDL_Surface *msgState = NULL;

  //message stating if the double jump is available
  SDL_Surface *msgJump = NULL;

  //text strings for the 2 messages above
  char *strState = NULL;
  strState = (char*)malloc(25 * sizeof(char));

  char *strJump = NULL;
  strJump = (char*)malloc(25 * sizeof(char));

  //texts positions of the 2 messages above
  SDL_Rect *posMsgState = NULL;
  posMsgState = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgState->x = 10;
  posMsgState->y = 10;

  SDL_Rect *posMsgJump = NULL;
  posMsgJump = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgJump->x = 10;
  posMsgJump->y = 30;

  //temporary texture used to load the messages to render them
  SDL_Texture *tempTxt = NULL;

  /* * * * * * characters * * * * * */

  //the main player
  player *p = NULL;

  //projectiles of the player : array of 100
  projectile *projectiles = NULL;

  //delay used between each step in the character animation
  int *stepDelay = NULL;

  /* * * * * * game loop * * * * * */

  //variable running the main loop and quitting the game if desired
  bool *quit = NULL;

  Uint32 *timeN_A = NULL;
  Uint32 *timeN_B = NULL;

  level *currLevel = NULL;
  /**********************************************/
  /* testlist_level*/


  level *lvl1 = malloc(sizeof(level));
  level *lvl2 = malloc(sizeof(level));
  level *nextLevel = malloc(sizeof(level));


  //temp won't be used again
  SDL_FreeSurface(temp);

  list_l LISTElvl = cons_list_l(lvl2, cons_list_l(lvl1, list_l_empty()));
  nextLevel = head_list_l(next_list_l (LISTElvl));
  currLevel = head_list_l (LISTElvl);



  /**********************************************/
  /*************************************************/
  SDL_Texture *blocks_spritesheet = NULL;
  SDL_Texture *background = NULL;

  /* * * * * * initialization * * * * * */

  if (init_variables(&initTimer, &manager, &window, &renderer, &mouse_pos, &event, &jumped, &mouse_btn, &i, &font, &colorPalette, &p, &projectiles, &stepDelay, &quit, &temp, &playerSprite, &cursor, &timeN_A, &timeN_B, &currLevel, &blocks_spritesheet, &background) == 0) {
    return EXIT_FAILURE;
  }

  //clear the renderer's render
  SDL_RenderClear(renderer);

  //render the present renderer
  SDL_RenderPresent(renderer);


  /* * * * * * player initialization * * * * * */

  //base position of the player
  floatpoint *basePosition = NULL;
  basePosition = (floatpoint*)malloc(sizeof(floatpoint));
  *basePosition = set_floatpoint((SCREEN_WIDTH / 2) - (IMG_WIDTH / 2), SCREEN_HEIGHT - IMG_HEIGHT);

  //base velocity of the player
  vector *baseVelocity = NULL;
  baseVelocity = (vector*)malloc(sizeof(vector));
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

  //creating the player
  *p = set_player(10, *basePosition, *baseVelocity, playerSprite, *desRec, *hitbox);
  //temporary
  p->enableGravity = true;
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



  *currLevel = init_level(blocks_spritesheet, background, p, 1);
  *nextLevel = init_level(blocks_spritesheet, background, p, 2);

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

    /* * * * * * player controls * * * * * */

    controls(event, quit, p, jumped, renderer, mouse_pos, mouse_btn, cursor, key);

    if (!is_colision(p, currLevel) & p->enableGravity){
      //printf("\tgravity\n");
      player_gravity(p);
    }
    //printf("velx:%f\tvely:%f\n", get_player_velocity(*p).x ,get_player_velocity(*p).y);
    player_jumping(p, *timeN_A, *timeN_B);

    //player_apply_velocity(p);
    ////
    //player_colision (p, currLevel);
    player_apply_velocity(p);
    update_player(p);

    //init a projectile if shooting
    shooting(*mouse_btn, *p, projectiles, *mouse_pos);

    update_projectiles(projectiles);

    if (SDL_GetTicks() >= *stepDelay + DELAY_STEP) {
      player_update_step(p);
      *stepDelay = SDL_GetTicks();
    }

    player_update_dir(p, *mouse_pos);

    //RAW vertical hyper space
    if (p->realPos.x + (IMG_WIDTH / 2) > SCREEN_WIDTH) {
      p->realPos.x = 0;
    }

    if (p->realPos.x + (IMG_WIDTH / 2) < 0) {
      p->realPos.x = SCREEN_WIDTH - IMG_WIDTH;
    }

    //RAW re-enabling double jump
    if (p->dJump == false && p->realPos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
      p->dJump = true;
    }

    /* debug */

    //text rendering
    switch (get_player_state(*p)) {
      case 0:
        sprintf(strState, "state : walking");
        break;
      case 1:
        sprintf(strState, "state : jumping");
        break;
      case 2:
        sprintf(strState, "state : double-jumping");
        break;
      case 3:
        sprintf(strState, "state : attacking");
        break;
      case 4:
        sprintf(strState, "state : crouching");
        break;
      default:
        break;
    }

    if (get_player_dJump(*p)) {
      sprintf(strJump, "dJump : true");
      SDL_FreeSurface(msgJump);
      msgJump = TTF_RenderText_Solid(font, strJump, colorPalette[3]);
    } else {
      sprintf(strJump, "dJump : false");
      SDL_FreeSurface(msgJump);
      msgJump = TTF_RenderText_Solid(font, strJump, colorPalette[2]);
    }

    SDL_FreeSurface(msgState);
    msgState = TTF_RenderText_Solid(font, strState, colorPalette[0]);

    //renderting the message on the window
    tempTxt = SDL_CreateTextureFromSurface(renderer, msgState);
    SDL_QueryTexture(tempTxt, NULL, NULL, &(posMsgState->w), &(posMsgState->h));
    SDL_RenderCopy(renderer, tempTxt, NULL, posMsgState);

    tempTxt = SDL_CreateTextureFromSurface(renderer, msgJump);
    SDL_QueryTexture(tempTxt, NULL, NULL, &(posMsgJump->w), &(posMsgJump->h));
    SDL_RenderCopy(renderer, tempTxt, NULL, posMsgJump);

    /* rendering */
    rendering(p, projectiles, cursor, *currLevel, mouse_pos, renderer);

    SDL_framerateDelay(manager);

  }

  free_variables(msgState, msgJump, playerSprite, tempTxt, renderer, window, font, i, projectiles, p, manager, colorPalette, strState, strJump, posMsgState, posMsgJump, event, quit, jumped, mouse_pos, mouse_btn, timeN_A, timeN_B, currLevel, blocks_spritesheet, background, stepDelay);

  return EXIT_SUCCESS;
}
