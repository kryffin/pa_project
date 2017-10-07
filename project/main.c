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
  SDL_Rect *mouse_pos = NULL;

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

  //the destination rectangle used to load the characters size
  SDL_Rect *desRec = NULL;
  desRec = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  desRec->x = 0;
  desRec->y = 0;
  desRec->w = 32;
  desRec->h = 64;

  /* * * * * * game loop * * * * * */

  //variable running the main loop and quitting the game if desired
  bool *quit = NULL;

  /* * * * * * initialization * * * * * */

  if (init_variables(&initTimer, &manager, &window, &renderer, &mouse_pos, &event, &jumped, &mouse_btn, &i, &font, &colorPalette, &p, &projectiles, &stepDelay, &quit, &temp, &playerSprite, &cursor) == 0) {
    return EXIT_FAILURE;
  }

  //clear the renderer's render
  SDL_RenderClear(renderer);

  //render the present renderer
  SDL_RenderPresent(renderer);


  /* * * * * * player initialization * * * * * */

  //base position of the player
  SDL_Rect *basePosition = NULL;
  basePosition = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  basePosition->x = (SCREEN_WIDTH / 2) - (IMG_WIDTH / 2);
  basePosition->y = SCREEN_HEIGHT - IMG_HEIGHT;
  basePosition->w = 32;
  basePosition->h = 64;

  //base velocity of the player
  SDL_Rect *baseVelocity = NULL;
  baseVelocity = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  baseVelocity->x = 0;
  baseVelocity->y = 0;
  baseVelocity->w = 16;
  baseVelocity->h = 16;

  //creating the player
  *p = set_player(10, 10, 0, true, *basePosition, *baseVelocity, playerSprite, *desRec);

  for (*i = 0; *i < 100; *i += 1) {
    projectiles[*i] = set_projectile(0.0, 0.0, *baseVelocity, *baseVelocity, playerSprite);
  }

  //PLACEHOLDER for these won't be used again
  free(basePosition);
  free(baseVelocity);
  free(desRec);

  //rendering the initialization time
  printf("Init time : %u ms\n", SDL_GetTicks() - *initTimer);

  //only used once
  free(initTimer);

  /* * * * * * main menu * * * * * */

  if (render_menu(quit, font, colorPalette, renderer, mouse_pos, cursor) == 0) {
    return EXIT_FAILURE;
  }

  /* * * * * * main game loop * * * * * */

  //while we are not quitting the game
  while (*quit == false) {

    //clearing the render to the draw color
    SDL_RenderClear(renderer);

    /* * * * * * player controls * * * * * */

    controls(event, quit, p, jumped, renderer, mouse_pos, mouse_btn, cursor, key);

    //PLACEHOLDER to render the enemy
    render_player(*p, renderer, *mouse_pos);

    //init a projectile if shooting
    init_projectile(*mouse_btn, *p, playerSprite, projectiles, *mouse_pos);

    //render the projectile
    render_projectile(projectiles, renderer);

    if (SDL_GetTicks() >= *stepDelay + DELAY_STEP) {
      player_update_step(p);
      *stepDelay = SDL_GetTicks();
    }

    player_apply_velocity(p);
    player_update_dir(p, *mouse_pos);

    //RAW vertical hyper space
    if (p->pos.x + IMG_WIDTH > SCREEN_HEIGHT) {
      p->pos.x = 0;
    }

    if (p->pos.x < 0) {
      p->pos.x = SCREEN_WIDTH - IMG_WIDTH;
    }

    player_jumping(p);

    //RAW gravity
    if (get_player_state(*p) == 0 || get_player_state(*p) == 3) {
      if (p->pos.y < SCREEN_HEIGHT - IMG_HEIGHT) {
        //currently in air
        p->pos.y += 5; //12 works perfectly
      } else if (p->pos.y > SCREEN_HEIGHT - IMG_HEIGHT){
        //currently below wanted place
        printf("\nwrong place\n\n");
        p->pos.y = SCREEN_HEIGHT - IMG_HEIGHT;
      }
    }

    //RAW re-enabling double jump
    if (p->dJump == false && p->pos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
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

    /* * * */

    SDL_RenderPresent(renderer);

    SDL_framerateDelay(manager);

  }

  free_variables(msgState, msgJump, playerSprite, tempTxt, renderer, window, font, i, projectiles, p, manager, colorPalette, strState, strJump, posMsgState, posMsgJump, event, quit, jumped, mouse_pos, mouse_btn);

  return EXIT_SUCCESS;
}
