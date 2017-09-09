#include "header.h"

int main () {

  /* VARIABLES */

  //window
  SDL_Surface *screen = NULL; //surface of the screen

  //img surfaces
  SDL_Surface *player_l = NULL; //image representing the player looking left
  SDL_Surface *player_r = NULL; //image representing the player looking right

  //font variables
  TTF_Font *font = NULL; //font used in the game
  SDL_Color black = {0, 0, 0}; //black font color
  SDL_Color red = {255, 0, 0}; //red font color
  SDL_Color green = {0, 180, 0}; //green font color

  //message surfaces
  SDL_Surface *msgState = NULL; //state indicator
  SDL_Surface *msgJump = NULL; //double jump indicator
  SDL_Surface *msgDash = NULL; //dash indicator

  //text strings
  char strState[25] = "";
  char strJump[15] = "";
  char strDash[15] = "";

  //texts positions
  SDL_Rect posMsgState;
  posMsgState.x = 10;
  posMsgState.y = 10;
  SDL_Rect posMsgJump;
  posMsgJump.x = 10;
  posMsgJump.y = 30;
  SDL_Rect posMsgDash;
  posMsgDash.x = 10;
  posMsgDash.y = 50;

  //event running the controls
  SDL_Event event;

  //the main player
  player p;

  bool exit = false;

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

  SDL_WM_SetCaption("MetroidVania test", "MVt");

  //screen initialization to 640x480
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0);
  if (screen == NULL) {
    printf("Error during SetVideoMode : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);

  //left player image loading
  player_l = SDL_LoadBMP(PATH_IMG_L);
  if (player_l == NULL) {
    printf("Error during image (left) loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  /* applying the colorkey */
  SDL_SetColorKey(player_l, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  //right player image loading
  player_r = SDL_LoadBMP(PATH_IMG_R);
  if (player_r == NULL) {
    printf("Error during image (right) loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  /* applying the colorkey */
  SDL_SetColorKey(player_r, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  font = TTF_OpenFont(PATH_FONT, FONT_SIZE);
  if (font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Rect acPos;
  acPos.x = (SCREEN_WIDTH / 2) - (IMG_WIDTH / 2);
  acPos.y = SCREEN_HEIGHT - IMG_HEIGHT;

  SDL_Rect acVel;
  acVel.x = 0;
  acVel.y = 0;

  p = set_player(10, 10, 0, true, false, acPos, acVel, player_r);

  while (!exit) {
    //filling the screen with white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format ,255, 255, 255));

    player_blit(p, player_l, player_r, screen);

    player_apply_velocity(&p);

    player_dashing(&p);

    //RAW vertical hyper space
    if (p.pos.x + IMG_WIDTH > SCREEN_WIDTH) {
      p.pos.x = 0;
    }

    if (p.pos.x < 0) {
      p.pos.x = SCREEN_WIDTH - IMG_WIDTH;
    }

    player_jumping(&p);

    //RAW gravity
    if (p.state == 0) {
      if (p.pos.y < SCREEN_HEIGHT - IMG_HEIGHT) {
        //currently in air
        p.pos.y += 12; //12 works perfectly
      } else if (p.pos.y > SCREEN_HEIGHT - IMG_HEIGHT){
        //currently below wanted place
        printf("\nwrong place\n\n");
        p.pos.y = SCREEN_HEIGHT - IMG_HEIGHT;
      }
    }

    //RAW re-enabling dash
    if (p.dash == false && p.pos.y == SCREEN_HEIGHT - IMG_HEIGHT && p.dashState == 0) {
      p.dash = true;
    }

    //RAW re-enabling double jump
    /*if (p.dJump == false && p.pos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
      p.dJump = true;
    }*/

    control(event, &p, &exit);

    /* debug */

    //text rendering
    switch (get_player_state(p)) {
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
        sprintf(strState, "state : dashing");
        break;
      default:
        break;
    }

    if (get_player_dJump(p)) {
      sprintf(strJump, "dJump : true");
      msgJump = TTF_RenderText_Solid(font, strJump, green);
    } else {
      sprintf(strJump, "dJump : false");
      msgJump = TTF_RenderText_Solid(font, strJump, red);
    }

    if (get_player_dash(p)) {
      sprintf(strDash, "dash : true");
      msgDash = TTF_RenderText_Solid(font, strDash, green);
    } else {
      sprintf(strDash, "dash : false");
      msgDash = TTF_RenderText_Solid(font, strDash, red);
    }

    msgState = TTF_RenderText_Solid(font, strState, black);

    //blitting the message on the screen
    SDL_BlitSurface(msgState, NULL, screen, &posMsgState);
    SDL_BlitSurface(msgJump, NULL, screen, &posMsgJump);
    SDL_BlitSurface(msgDash, NULL, screen, &posMsgDash);

    /* * * */

    SDL_Flip(screen);

    SDL_Delay(50);
  }

  return EXIT_SUCCESS;
}
