#include "header.h"

//function returning the state of the mouse :
/* 0 : no motion
   1 : button down
   2 : button up
   10 : quit
*/
int menu_controls(SDL_Event *event, int *mousex, int *mousey) {
  //controls
  while (SDL_PollEvent(event)) {
    switch(event->type) {
      case SDL_MOUSEMOTION:
        *mousex = event->motion.x;
        *mousey = event->motion.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        printf("hello\n");
        return 1;
        break;

      case SDL_MOUSEBUTTONUP:
        return 2;
        break;

      case SDL_KEYDOWN:
        return 10;
        break;

      default:
        break;
    }
  }

  return 0;
}

int menu_display (SDL_Surface *screen, TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red) {

  int *mousex = (int*)malloc(sizeof(int));
  int *mousey = (int*)malloc(sizeof(int));
  int *control = (int*)malloc(sizeof(int));
  int *option = (int*)malloc(sizeof(int));

  //message surfaces
  SDL_Surface *surContinue = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  surContinue = NULL; //state indicator
  SDL_Surface *surOptions = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  surOptions = NULL; //double jump indicator
  SDL_Surface *surQuit = (SDL_Surface*)malloc(sizeof(SDL_Surface));
  surQuit = NULL; //dash indicator

  //text strings
  char *strContinue = (char*)malloc(9 * sizeof(char));
  sprintf(strContinue, "Continue");
  char *strOptions = (char*)malloc(8 * sizeof(char));
  sprintf(strOptions, "Options");
  char *strQuit = (char*)malloc(5 * sizeof(char));
  sprintf(strQuit, "Quit");

  //text positions
  SDL_Rect *posContinue = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  SDL_Rect *posOptions = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  SDL_Rect *posQuit = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  //event running the controls
  SDL_Event *event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //render the messages
  surContinue = TTF_RenderText_Solid(font, strContinue, *black);
  surOptions = TTF_RenderText_Solid(font, strOptions, *black);
  surQuit = TTF_RenderText_Solid(font, strQuit, *black);

  //message positions
  posContinue->x = (SCREEN_WIDTH / 2) - (surContinue->clip_rect.w / 2);
  posContinue->y = (SCREEN_HEIGHT / 2) - (surContinue->clip_rect.h / 2) - 100;
  posOptions->x = (SCREEN_WIDTH / 2) - (surOptions->clip_rect.w / 2);
  posOptions->y = (SCREEN_HEIGHT / 2) - (surOptions->clip_rect.h / 2);
  posQuit->x = (SCREEN_WIDTH / 2) - (surQuit->clip_rect.w / 2);
  posQuit->y = (SCREEN_HEIGHT / 2) - (surQuit->clip_rect.h / 2) + 100;

  while (1) {

    //fill the screen with white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format ,255, 255, 255));

    //controls
    *control = menu_controls(event, mousex, mousey);

    if (*mousex <= ((SCREEN_WIDTH / 2) - (surContinue->clip_rect.w / 2)) + surContinue->clip_rect.w
        && *mousex >= ((SCREEN_WIDTH / 2) - (surContinue->clip_rect.w / 2))
        && *mousey <= ((SCREEN_HEIGHT / 2) - (surContinue->clip_rect.h / 2) - 100) + surContinue->clip_rect.h
        && *mousey >= ((SCREEN_HEIGHT / 2) - (surContinue->clip_rect.h / 2) - 100)) {
      if (*control == 0) {
        surContinue = TTF_RenderText_Solid(font, strContinue, *green);
      } else if (*control == 1){
        surContinue = TTF_RenderText_Solid(font, strContinue, *red);
      } else if (*control == 2) {
        surContinue = TTF_RenderText_Solid(font, strContinue, *green);
        *option = 1;
      }
    } else if (*mousex <= ((SCREEN_WIDTH / 2) - (surOptions->clip_rect.w / 2)) + surOptions->clip_rect.w
              && *mousex >= ((SCREEN_WIDTH / 2) - (surOptions->clip_rect.w / 2))
              && *mousey <= ((SCREEN_HEIGHT / 2) - (surOptions->clip_rect.h / 2)) + surOptions->clip_rect.h
              && *mousey >= ((SCREEN_HEIGHT / 2) - (surOptions->clip_rect.h / 2))) {
      if (*control == 0) {
        surOptions = TTF_RenderText_Solid(font, strOptions, *green);
      } else if (*control == 1){
        surOptions = TTF_RenderText_Solid(font, strOptions, *red);
      } else if (*control == 2) {
        surOptions = TTF_RenderText_Solid(font, strOptions, *green);
        *option = 2;
      }
    } else if (*mousex <= ((SCREEN_WIDTH / 2) - (surQuit->clip_rect.w / 2)) + surQuit->clip_rect.w
              && *mousex >= ((SCREEN_WIDTH / 2) - (surQuit->clip_rect.w / 2))
              && *mousey <= ((SCREEN_HEIGHT / 2) - (surQuit->clip_rect.h / 2) + 100) + surQuit->clip_rect.h
              && *mousey >= ((SCREEN_HEIGHT / 2) - (surQuit->clip_rect.h / 2) + 100)) {
      if (*control == 0) {
        surQuit = TTF_RenderText_Solid(font, strQuit, *green);
      } else if (*control == 1) {
        surQuit = TTF_RenderText_Solid(font, strQuit, *red);
      } else if (*control == 2) {
        surContinue = TTF_RenderText_Solid(font, strContinue, *green);
        *option = 3;
      }
    } else {
      //render the messages
      surContinue = TTF_RenderText_Solid(font, strContinue, *black);
      surOptions = TTF_RenderText_Solid(font, strOptions, *black);
      surQuit = TTF_RenderText_Solid(font, strQuit, *black);
    }

    //blitting the message on the screen
    SDL_BlitSurface(surContinue, NULL, screen, posContinue);
    SDL_BlitSurface(surOptions, NULL, screen, posOptions);
    SDL_BlitSurface(surQuit, NULL, screen, posQuit);

    SDL_Flip(screen);
    printf("x : %d \t w : %d\n", (SCREEN_WIDTH / 2) - (surContinue->clip_rect.w / 2), surContinue->clip_rect.w); //debug
    printf("y : %d \t h : %d\n", (SCREEN_HEIGHT / 2) - (surContinue->clip_rect.h / 2) - 100, surContinue->clip_rect.h); //debug
    printf("x : %d \t y : %d\n", *mousex, *mousey); //debug position de la souris
    SDL_Delay(200);

    if (*option != 0 || *control == 10) {
      free(mousex);
      free(mousey);
      free(control);
      free(surContinue);
      free(surOptions);
      free(surQuit);
      free(strContinue);
      free(strOptions);
      free(strQuit);
      free(posContinue);
      free(posOptions);
      free(posQuit);
      free(event);
      return *option;
    }
  }
}
