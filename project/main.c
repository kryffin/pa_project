#include "header.h"

int main () {

  /* * * * * * fps * * * * * */

  //timer used for the fps delay
  Uint32 *initTimer = NULL;
  initTimer = (Uint32*)malloc(sizeof(Uint32));
  *initTimer = SDL_GetTicks(); //init the timer to the current time

  //the manager managing the fps
  FPSmanager *manager = NULL;
  manager = (FPSmanager*)malloc(sizeof(FPSmanager));
  SDL_initFramerate(manager);
  SDL_setFramerate(manager, SCREEN_FPS);

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
  mouse_pos = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  //array for the keys pressed
  SDL_Keycode key[SDL_NUM_SCANCODES] = {0};

  //event running the controls
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //used to know if the player jumped
  //  essentially used to avoid the key from being pressed multiple times in one stroke
  bool *jumped = NULL;
  jumped = (bool*)malloc(sizeof(bool));
  *jumped = false;

  //actual state of the mouse button
  bool *mouse_btn = NULL;
  mouse_btn = (bool*)malloc(sizeof(bool));
  *mouse_btn = false;

  /* * * * * * font & colors * * * * * */

  //font used in the game
  TTF_Font *font = NULL;

  //black color
  SDL_Color *black = NULL;
  black = (SDL_Color*)malloc(sizeof(SDL_Color)); //black font color
  black->r = 0;
  black->g = 0;
  black->b = 0;

  //red color
  SDL_Color *red = NULL;
  red = (SDL_Color*)malloc(sizeof(SDL_Color)); //red font color
  red->r = 255;
  red->g = 0;
  red->b = 0;

  //greeen color
  SDL_Color *green = NULL;
  green = (SDL_Color*)malloc(sizeof(SDL_Color)); //green font color
  green->r = 0;
  green->g = 180;
  green->b = 0;

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
  p = (player*)malloc(sizeof(player));

  //PLACEHOLDER for the enemies
  player *enemy = NULL;
  enemy = (player*)malloc(sizeof(player));

  //delay used between each step in the character animation
  int *stepDelay = NULL;
  stepDelay = (int*)malloc(sizeof(int));
  *stepDelay = 0;

  //the destination rectangle used to load the characters size
  SDL_Rect *desRec = NULL;
  desRec = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  desRec->x = 0;
  desRec->y = 0;
  desRec->w = 32;
  desRec->h = 64;

  /* * * * * * menu * * * * * */

  //the option selected in the main menu
  int *mainMenuOption = NULL;
  mainMenuOption = (int*)malloc(sizeof(int));
  *mainMenuOption = 0;

  //the option selected in the option menu
  int *optionMenuOption = NULL;
  optionMenuOption = (int*)malloc(sizeof(int));
  *optionMenuOption = 0;

  /* * * * * * game loop * * * * * */

  //variable running the main loop and quitting the game if desired
  bool *quit = NULL;
  quit = (bool*)malloc(sizeof(bool));
  *quit = false;

  /* * * * * * initialization * * * * * */

  //SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error while SDL initialization : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //TTF initialization
  if (TTF_Init() != 0) {
    printf("Error while TTF initialization : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //window initialization
  window = SDL_CreateWindow("MVt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    printf("Error during window creating : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //renderer initialization
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error during renderer creating : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //hide the computer cursor to only show the game's
  SDL_ShowCursor(SDL_DISABLE);

  //set the draw color of the renderer to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  //clear the renderer's render
  SDL_RenderClear(renderer);

  //render the present renderer
  SDL_RenderPresent(renderer);

  /* * * * * * images loading * * * * * */

  //spritesheet image loading through the temp surface to a texture
  temp = SDL_LoadBMP(PATH_SPRITES);
  playerSprite = SDL_CreateTextureFromSurface(renderer, temp);
  if (playerSprite == NULL) {
    printf("Error during sprite sheet image loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //freeing the temp to use it again
  SDL_FreeSurface(temp);

  //cursor image loading through the temp surface to a texture
  temp = SDL_LoadBMP(PATH_CURSOR);
  cursor = SDL_CreateTextureFromSurface(renderer, temp);
  if (cursor == NULL) {
    printf("Error during cursor image loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //temp won't be used again
  SDL_FreeSurface(temp);

  /* * * * * * font loading * * * * * */

  //font loading
  font = TTF_OpenFont(PATH_FONT, FONT_SIZE);
  if (font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

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

  //creating the player
  *p = set_player(10, 10, 0, true, *basePosition, *baseVelocity, playerSprite, *desRec);

  //updating the base position for the enemy
  basePosition->x = 10;

  //PLACEHOLDER for creating the enemy
  *enemy = set_player(10, 10, 0, true, *basePosition, *baseVelocity, playerSprite, *desRec);

  //PLACEHOLDER for these won't be used again
  free(basePosition);
  free(baseVelocity);
  free(desRec);

  //rendering the initialization time
  printf("Init time : %u ms\n", SDL_GetTicks() - *initTimer);

  //only used once
  free(initTimer);

  /* * * * * * main game loop * * * * * */

  //while we are not quitting the game
  while (*quit == false) {

    //clearing the render to the draw color
    SDL_RenderClear(renderer);

    //while we are in the main or option menu
    while (*mainMenuOption == 0 || *mainMenuOption == 2) {

      //set the option menu to 0, which means nothing have been selected
      *optionMenuOption = 0;

      //getting the option selected from the main menu
      *mainMenuOption = main_menu_display (font, black, green, red, renderer, mouse_pos, cursor);

      //if we wanna enter the option menu
      if (*mainMenuOption == 2) {

        //while we don't select back in the option menu
        while (*optionMenuOption != 6) {

          //getting the option selected from the option menu
          *optionMenuOption = option_menu_display (font, black, green, red, renderer, mouse_pos, cursor);

          //depending on the choice selected
          switch (*optionMenuOption) {

            case 1:
              //option 1
              SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
              break;

            case 2:
              //option 2
              break;

            case 3:
              //option 3
              break;

            case 4:
              //option 4
              break;

            case 5:
              //option 5
              break;

            case 6:
              //option 6 : quitting the option menu
              *mainMenuOption = 0;
              *optionMenuOption = 6;
              break;

          }

        }
      }

      //if we choose "quit" in the main menu
      if (*mainMenuOption == 3) {
        //quitting the game
        *quit = true;
      }

    }

    //if we don't wanna quit the game / we are playing it
    if (*quit == false) {

      /* * * * * * player controls * * * * * */

      //update the keyboard controls
      update_keyboard_controls(event, key, quit);

      //act depending on the keyboard state
      keyboard_control(p, key, jumped, renderer);

      //update the mouse position and mouse button state
      update_mouse_controls(event, mouse_pos, mouse_btn);

      //render the cursor
      cursor_render(cursor, renderer, *mouse_pos);

      //render the player
      player_render(*enemy, playerSprite, renderer, *mouse_pos);

      //PLACEHOLDER to render the enemy
      player_render(*p, playerSprite, renderer, *mouse_pos);

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
        msgJump = TTF_RenderText_Solid(font, strJump, *green);
      } else {
        sprintf(strJump, "dJump : false");
        SDL_FreeSurface(msgJump);
        msgJump = TTF_RenderText_Solid(font, strJump, *red);
      }

      SDL_FreeSurface(msgState);
      msgState = TTF_RenderText_Solid(font, strState, *black);

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
  }

  /* FREE */

  SDL_FreeSurface(msgState);
  SDL_FreeSurface(msgJump);
  SDL_DestroyTexture(playerSprite);
  SDL_DestroyTexture(tempTxt);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);

  TTF_Quit();
  SDL_Quit();

  free(p);
  free(enemy);
  free(manager);
  free(black);
  free(red);
  free(green);
  free(strState);
  free(strJump);
  free(posMsgState);
  free(posMsgJump);
  free(event);
  free(quit);
  free(mainMenuOption);
  free(jumped);
  free(mouse_pos);

  return EXIT_SUCCESS;
}
