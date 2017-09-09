#include "header.h"

int main () {

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

  SDL_WM_SetCaption("Bouncy Image", "BI");

  //screen initialization to 1366x768 fullscreen
  SDL_Surface *screen = NULL;
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN);
  if (screen == NULL) {
    printf("Error during SetVideoMode : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //image loading
  SDL_Surface *img = NULL;
  img = SDL_LoadBMP("./img.bmp");
  if (img == NULL) {
    printf("Error during image loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //font loading to size 15
  TTF_Font *font = NULL;
  font = TTF_OpenFont("font.ttf", 15);
  if (font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //velocity for the image movement
  int vel_x = 1;
  int vel_y = 1;

  //font color
  SDL_Color black = {0, 0, 0};

  //messages initialization
  //how to
  SDL_Surface *text = NULL;
  //current speed
  SDL_Surface *text2 = NULL;

  //writing the messages
  char strMess[40] = "";
  sprintf(strMess, "'+' pour accelerer | '-' pour ralentir");
  char strClue[15] = "";
  sprintf(strClue, "Vitesse : %d", vel_x);

  //text rendering
  text = TTF_RenderText_Solid(font, strMess, black);
  text2 = TTF_RenderText_Solid(font, strClue, black);

  //position of the text
  SDL_Rect tPos;
  tPos.x = 10;
  tPos.y = 10;
  //position of the text2
  SDL_Rect tPos2;
  tPos2.x = 10;
  tPos2.y = 30;

  //position of the image (centered)
  SDL_Rect pos;
  pos.x = (SCREEN_WIDTH / 2) - (IMG_WIDTH / 2);
  pos.y = (SCREEN_HEIGHT / 2) - (IMG_HEIGHT / 2);

  //loop breaking variable
  short int exit = 0;

  //event for the keyboard inputs
  SDL_Event event;

  //main game loop
  while (!exit) {

    //filling the screen with gray
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format ,218, 218, 218));

    //blitting the image on the screen
    SDL_BlitSurface(img, NULL, screen, &pos);

    //updating the position of the image
    pos.x += vel_x;
    pos.y += vel_y;

    //vertical bouncing
    if (pos.x + IMG_WIDTH >= SCREEN_WIDTH || pos.x <= 0) {
      vel_x = -vel_x;
    }

    //horizontal bouncing
    if (pos.y + IMG_HEIGHT >= SCREEN_HEIGHT || pos.y <= 0) {
      vel_y = -vel_y;
    }

    //keyboard input event
    while (SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            //'-' key for lower speed
            case SDLK_KP_MINUS:
              if ((vel_x != 1 && vel_y != 1) && (vel_x != -1 && vel_y != -1)) {
                vel_x /= 2;
                vel_y /= 2;
              }
              break;

            //'+' key for higher speed
            case SDLK_KP_PLUS:
              if ((vel_x < 10 && vel_y < 10 )&&( vel_x > -10 && vel_y > -10)) {
                vel_x *= 2;
                vel_y *= 2;
                printf("%d\n", vel_x);
              }
              break;

            //'q' to quit
            case SDLK_q:
              exit = 1;
              break;

            default:
              break;
          }
      }
    }

    //updating the speed message
    sprintf(strClue, "Vitesse : %d", abs(vel_x));
    text2 = TTF_RenderText_Solid(font, strClue, black);

    //blitting the updated messages on the screen
    SDL_BlitSurface(text, NULL, screen, &tPos);
    SDL_BlitSurface(text2, NULL, screen, &tPos2);

    //re-draw the screen
    SDL_Flip(screen);

    //delay of 50 ms
    SDL_Delay(50);
  }

  /* CLEANING */

  //close the font
  TTF_CloseFont(font);
  //free the image surface
  SDL_FreeSurface(img);
  TTF_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
