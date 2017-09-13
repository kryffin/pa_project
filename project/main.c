#include "header.h"

int main () {

  /* VARIABLES */

  //window
  SDL_Surface *screen = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  screen = NULL; //surface of the screen

  //img surfaces
  SDL_Surface *player_l = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  player_l = NULL; //image representing the player looking left
  SDL_Surface *player_r = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  player_r = NULL; //image representing the player looking right

  //font variables
  TTF_Font *font = (TTF_Font*)malloc(sizeof(font)); //font used in the game
  font = NULL;
  SDL_Color *black = (SDL_Color*)malloc(sizeof(SDL_Color)); //black font color
  black->r = 0;
  black->g = 0;
  black->b = 0;
  SDL_Color *red = (SDL_Color*)malloc(sizeof(SDL_Color)); //red font color
  red->r = 255;
  red->g = 0;
  red->b = 0;
  SDL_Color *green = (SDL_Color*)malloc(sizeof(SDL_Color)); //green font color
  green->r = 0;
  green->g = 180;
  green->b = 0;

  //message surfaces
  SDL_Surface *msgState = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  msgState = NULL; //state indicator
  SDL_Surface *msgJump = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  msgJump = NULL; //double jump indicator
  SDL_Surface *msgDash = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  msgDash = NULL; //dash indicator

  //text strings
  char *strState = (char*)malloc(25 * sizeof(char));
  char *strJump = (char*)malloc(25 * sizeof(char));
  char *strDash = (char*)malloc(25 * sizeof(char));

  //texts positions
  SDL_Rect *posMsgState = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgState->x = 10;
  posMsgState->y = 10;
  SDL_Rect *posMsgJump = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgJump->x = 10;
  posMsgJump->y = 30;
  SDL_Rect *posMsgDash = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  posMsgDash->x = 10;
  posMsgDash->y = 50;

  //event running the controls
  SDL_Event *event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //the main player
  player *p = (player*)malloc(sizeof(player));

  bool *quit = (bool*)malloc(sizeof(bool));
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

  SDL_Rect *acPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  acPos->x = (SCREEN_WIDTH / 2) - (IMG_WIDTH / 2);
  acPos->y = SCREEN_HEIGHT - IMG_HEIGHT;

  SDL_Rect *acVel = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  acVel->x = 0;
  acVel->y = 0;

  *p = set_player(10, 10, 0, true, true, *acPos, *acVel, player_r);

  while (*quit == false) {
    //filling the screen with white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format ,255, 255, 255));

    player_blit(*p, player_l, player_r, screen);

    player_apply_velocity(p);

    player_dashing(p);

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

    //RAW re-enabling dash
    if (p->dash == false && p->pos.y == SCREEN_HEIGHT - IMG_HEIGHT && p->dashState == 0) {
      p->dash = true;
    }

    //RAW re-enabling double jump
    if (p->dJump == false && p->pos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
      p->dJump = true;
    }

    control(*event, p, quit);

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
        sprintf(strState, "state : dashing");
        break;
      default:
        break;
    }

    if (get_player_dJump(*p)) {
      sprintf(strJump, "dJump : true");
      msgJump = TTF_RenderText_Solid(font, strJump, *green);
    } else {
      sprintf(strJump, "dJump : false");
      msgJump = TTF_RenderText_Solid(font, strJump, *red);
    }

    if (get_player_dash(*p)) {
      sprintf(strDash, "dash : true");
      msgDash = TTF_RenderText_Solid(font, strDash, *green);
    } else {
      sprintf(strDash, "dash : false");
      msgDash = TTF_RenderText_Solid(font, strDash, *red);
    }

    msgState = TTF_RenderText_Solid(font, strState, *black);

    //blitting the message on the screen
    SDL_BlitSurface(msgState, NULL, screen, posMsgState);
    SDL_BlitSurface(msgJump, NULL, screen, posMsgJump);
    SDL_BlitSurface(msgDash, NULL, screen, posMsgDash);

    /* * * */

    SDL_Flip(screen);

    SDL_Delay(50);
  }

  /* FREE */

  free(screen);
  free(player_l);
  free(player_r);
  free(font);
  free(black);
  free(red);
  free(green);
  free(msgState);
  free(msgJump);
  free(msgDash);
  free(strState);
  free(strJump);
  free(strDash);
  free(posMsgState);
  free(posMsgJump);
  free(posMsgDash);
  free(event);
  free(quit);
  free(acPos);
  free(acVel);

  return EXIT_SUCCESS;
}
