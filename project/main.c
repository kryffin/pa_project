#include "header.h"

int main () {

  //fps manager
  Uint32 *initTimer = NULL;
  initTimer = (Uint32*)malloc(sizeof(Uint32));
  *initTimer = SDL_GetTicks();

  FPSmanager *manager = NULL;
  manager = (FPSmanager*)malloc(sizeof(FPSmanager));
  SDL_initFramerate(manager);
  SDL_setFramerate(manager, SCREEN_FPS);

  /* VARIABLES */
  SDL_Rect desRec;
  desRec.x = 10;
  desRec.y = 10;
  desRec.w = 10;
  desRec.h = 10;

  //window
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  //img surfaces
  SDL_Surface *temp = NULL;
  SDL_Texture *player_l = NULL;
  SDL_Texture *player_r = NULL;

  //array for the keys pressed
  SDL_Keycode key[SDL_NUM_SCANCODES] = {0};

  //font variables
  TTF_Font *font = NULL; //font used in the game

  SDL_Color *black = NULL;
  black = (SDL_Color*)malloc(sizeof(SDL_Color)); //black font color
  black->r = 0;
  black->g = 0;
  black->b = 0;

  SDL_Color *red = NULL;
  red = (SDL_Color*)malloc(sizeof(SDL_Color)); //red font color
  red->r = 255;
  red->g = 0;
  red->b = 0;

  SDL_Color *green = NULL;
  green = (SDL_Color*)malloc(sizeof(SDL_Color)); //green font color
  green->r = 0;
  green->g = 180;
  green->b = 0;

  bool *jumped = NULL;
  jumped = (bool*)malloc(sizeof(bool));
  *jumped = false;

  //message surfaces
  SDL_Surface *msgState = NULL;

  SDL_Surface *msgJump = NULL;


  //text strings
  char *strState = NULL;
  strState = (char*)malloc(25 * sizeof(char));

  char *strJump = NULL;
  strJump = (char*)malloc(25 * sizeof(char));

  //texts positions
  SDL_Rect *posMsgState = NULL;
  posMsgState = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgState->x = 10;
  posMsgState->y = 10;

  SDL_Rect *posMsgJump = NULL;
  posMsgJump = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgJump->x = 10;
  posMsgJump->y = 30;

  SDL_Texture *tempT = NULL;

  //event running the controls
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //the main player
  player *p = NULL;
  p = (player*)malloc(sizeof(player));

  int *menuOption = NULL;
  menuOption = (int*)malloc(sizeof(int));
  *menuOption = 0;

  bool *quit = NULL;
  quit = (bool*)malloc(sizeof(bool));
  *quit = false;
  /*************/

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

  //window initialization to 640x480
  window = SDL_CreateWindow("MVt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    printf("Error during window creating : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error during renderer creating : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  //int colorkey = SDL_MapRGB(window->format, 255, 0, 255);

  //left player image loading
  temp = SDL_LoadBMP(PATH_IMG_L);
  player_l = SDL_CreateTextureFromSurface(renderer, temp);
  if (player_l == NULL) {
    printf("Error during image (left) loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  /* applying the colorkey */
  //SDL_SetColorKey(player_l, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  SDL_FreeSurface(temp);

  //right player image loading
  temp = SDL_LoadBMP(PATH_IMG_R);
  player_r = SDL_CreateTextureFromSurface(renderer, temp);
  if (player_r == NULL) {
    printf("Error during image (right) loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_FreeSurface(temp);

  /* applying the colorkey */
  //SDL_SetColorKey(player_r, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  font = TTF_OpenFont(PATH_FONT, FONT_SIZE);
  if (font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Rect *acPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  acPos->x = (SCREEN_WIDTH / 2) - (IMG_WIDTH / 2);
  acPos->y = SCREEN_HEIGHT - IMG_HEIGHT;
  acPos->w = 105;
  acPos->h = 130;

  SDL_Rect *acVel = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  acVel->x = 0;
  acVel->y = 0;

  *p = set_player(10, 10, 0, true, *acPos, *acVel, player_r);

  //initialization time
  printf("Init time : %u ms\n", SDL_GetTicks() - *initTimer);

  free(initTimer);

  while (*quit == false) {
    //filling the window with white
    SDL_RenderClear(renderer);

    if (*menuOption == 0) {
      *menuOption = menu_display(font, black, green, red, renderer);
    }

    /*if (menuOption == 2) {
      //menu des options
    }*/

    if (*menuOption == 3) {
      *quit = true;
    } else if (*menuOption == 1) {

      //controls
      update_controls(event, key, quit);
      control(p, key, jumped, renderer);

      player_blit(*p, player_l, player_r, renderer, desRec);

      player_apply_velocity(p);

      //RAW vertical hyper space
      if (p->pos.x + IMG_WIDTH > SCREEN_WIDTH) {
        p->pos.x = 0;
      }

      if (p->pos.x < 0) {
        p->pos.x = SCREEN_WIDTH - IMG_WIDTH;
      }

      player_jumping(p);

      //RAW gravity
      if (p->state == 0) {
        if (p->pos.y < SCREEN_HEIGHT - IMG_HEIGHT) {
          //currently in air
          p->pos.y += 12; //12 works perfectly
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

      //blitting the message on the window
      tempT = SDL_CreateTextureFromSurface(renderer, msgState);
      SDL_QueryTexture(tempT, NULL, NULL, &(posMsgState->w), &(posMsgState->h));
      SDL_RenderCopy(renderer, tempT, NULL, posMsgState);

      tempT = SDL_CreateTextureFromSurface(renderer, msgJump);
      SDL_QueryTexture(tempT, NULL, NULL, &(posMsgJump->w), &(posMsgJump->h));
      SDL_RenderCopy(renderer, tempT, NULL, posMsgJump);

      /* * * */

      SDL_RenderPresent(renderer);

      SDL_framerateDelay(manager);
    }
  }

  /* FREE */

  SDL_FreeSurface(msgState);
  SDL_FreeSurface(msgJump);
  SDL_DestroyTexture(player_l);
  SDL_DestroyTexture(player_r);
  SDL_DestroyTexture(tempT);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);

  TTF_Quit();
  SDL_Quit();

  free(p);
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
  free(acPos);
  free(acVel);
  free(menuOption);
  free(jumped);

  return EXIT_SUCCESS;
}
