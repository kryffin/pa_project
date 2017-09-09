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

  SDL_WM_SetCaption("MetroidVania test", "MVt");

  //screen initialization to 640x480
  SDL_Surface *screen = NULL;
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0);
  if (screen == NULL) {
    printf("Error during SetVideoMode : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //images loading
  SDL_Surface *img = NULL;
  img = SDL_LoadBMP("./img.bmp");
  if (img == NULL) {
    printf("Error during image loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //flipped version
  SDL_Surface *imgFlipped = NULL;
  imgFlipped = SDL_LoadBMP("./imgFlipped.bmp");
  if (imgFlipped == NULL) {
    printf("Error during image (flipped) loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //font loading to size 15
  TTF_Font *font = NULL;
  font = TTF_OpenFont("font.ttf", 15);
  if (font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //font colors
  SDL_Color black = {0, 0, 0};
  SDL_Color red = {255, 0, 0};
  SDL_Color green = {0, 180, 0};

  //messages initialization
  //how to
  SDL_Surface *text = NULL;
  SDL_Surface *text2 = NULL;
  SDL_Surface *text3 = NULL;

  //writing the messages
  char strState[25] = "";
  char strJump[15] = "";
  char strDash[15] = "";

  //position of the text
  SDL_Rect tPos;
  tPos.x = 10;
  tPos.y = 10;
  //position of the text2
  SDL_Rect tPos2;
  tPos2.x = 10;
  tPos2.y = 30;
  //position of the text2
  SDL_Rect tPos3;
  tPos3.x = 10;
  tPos3.y = 50;

  //position of the image (centered)
  SDL_Rect pos;
  pos.x = (SCREEN_WIDTH / 2) - (IMG_WIDTH / 2);
  pos.y = SCREEN_HEIGHT - IMG_HEIGHT;

  //movement velocity
  int vel_x = 0, vel_y = 0;

  //loop breaking variable
  bool exit = false;

  //state initialization
  short int state = 0;

  /*
  0 : walking / normal
  1 : jumping
  2 : double-jumping
  3 : dashing
  */

  //jumping state
  //bool inAir = false;

  //current direction for img use (1 : left | 2 : right)
  short int currDir = 1;

  //current state of the dashing
  short int dashState = 0;

  //is dash available?
  bool dash = true;

  //start of the jump
  int jumpPoint = 0;
  int highPoint = 0;

  //distance for falling
  //float distFall = 0.;

  //is double jumping available?
  bool dJump = true;

  //event for the keyboard inputs
  SDL_Event event;

  //main game loop
  while (!exit) {

    //filling the screen with gray
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format ,218, 218, 218));

    //blitting the image on the screen with the right direction
    if (currDir == 1) {
      SDL_BlitSurface(img, NULL, screen, &pos);
    } else if (currDir == 2) {
      SDL_BlitSurface(imgFlipped, NULL, screen, &pos);
    } else {
      printf("Wrong direction\n");
      return EXIT_FAILURE;
    }

    //moving with the current velocity
    if (state != 3) {
      pos.x += vel_x;
    }

    //dashing
    if (state == 3) {
      if (dashState >= 5) {
        dashState = 0;
        state = 0;
      } else {
        dashState += 1;
        if (currDir == 1) {
          pos.x -= 60;
        } else if (currDir == 2) {
          pos.x += 60;
        }
      }
    }

    //vertical hyper space
    if (pos.x + IMG_WIDTH > SCREEN_WIDTH) {
      pos.x = 0;
    }

    if (pos.x < 0) {
      pos.x = SCREEN_WIDTH - IMG_WIDTH;
    }

    //jumping state
    if (state == 1 || state == 2) {
      if (pos.y > jumpPoint - IMG_HEIGHT) {
        //currently jumping
        pos.y -= (pos.y - (jumpPoint - IMG_HEIGHT)) * 0.3;
      } else {
        //jumping ends
        highPoint = pos.y;
        state = 0;
      }
    }

    //gravity
    if (state == 0) {
      if (pos.y < SCREEN_HEIGHT - IMG_HEIGHT) {
        //currently in air
        pos.y += ((SCREEN_HEIGHT - IMG_HEIGHT) - highPoint) * 0.2;
      } else if (pos.y > SCREEN_HEIGHT - IMG_HEIGHT){
        //currently below wanted place
        printf("\nwrong place\n\n");
        pos.y = SCREEN_HEIGHT - IMG_HEIGHT;
      }
    }

    //re-enabling double jump
    if (dJump == false && pos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
      dJump = true;
    }

    //re-enabling dash
    if (dash == false && pos.y == SCREEN_HEIGHT - IMG_HEIGHT && dashState == 0) {
      dash = true;
    }

    //keyboard input event
    if (state != 3) {
      while (SDL_PollEvent(&event)) {
        switch(event.type) {
          case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {

              //'q' key for left
              case SDLK_q:
                vel_x = -20;
                currDir = 1;
                break;

              //'d' key for right
              case SDLK_d:
                vel_x = 20;
                currDir = 2;
                break;

              //'space' or 'z' to jump
              case SDLK_z:
              case SDLK_SPACE:
                if (pos.y == SCREEN_HEIGHT - IMG_HEIGHT) {
                  state = 1;
                  jumpPoint = pos.y;
                } else if (dJump == true) {
                  dJump = false;
                  state = 2;
                  jumpPoint = pos.y;
                }
                break;

              case SDLK_LSHIFT:
                if (dash == true && state != 3) {
                  state = 3;
                  dash = false;
                }
                break;

              //'esc' to quit
              case SDLK_ESCAPE:
                exit = true;
                break;

              default:
                break;
            }
            break;

          case SDL_KEYUP:
            switch (event.key.keysym.sym) {

              //'q' key for left
              case SDLK_q:
                if (vel_x < 0) {
                  vel_x = 0;
                }
                break;

              //'d' key for right
              case SDLK_d:
                if (vel_x > 0) {
                  vel_x = 0;
                }
                break;

              //'space' to jump
              case SDLK_SPACE:
                //nothing happens
                break;

              default:
                break;
            }
            break;

          default:
            break;
        }
      }
    }

    //text rendering
    switch (state) {
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

    if (dJump) {
      sprintf(strJump, "dJump : true");
      text2 = TTF_RenderText_Solid(font, strJump, green);
    } else {
      sprintf(strJump, "dJump : false");
      text2 = TTF_RenderText_Solid(font, strJump, red);
    }

    if (dash) {
      sprintf(strDash, "dash : true");
      text3 = TTF_RenderText_Solid(font, strDash, green);
    } else {
      sprintf(strDash, "dash : false");
      text3 = TTF_RenderText_Solid(font, strDash, red);
    }

    text = TTF_RenderText_Solid(font, strState, black);

    //blitting the message on the screen
    SDL_BlitSurface(text, NULL, screen, &tPos);
    SDL_BlitSurface(text2, NULL, screen, &tPos2);
    SDL_BlitSurface(text3, NULL, screen, &tPos3);

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
