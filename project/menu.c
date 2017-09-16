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
        return 1;
        break;

      case SDL_MOUSEBUTTONUP:
        return 2;
        break;

      default:
        break;
    }
  }

  return 0;
}

/*display of the menu which returns :
  1 : Continue
  2 : Options
  3 : Quit
*/
int menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer) {

  int *mousex = NULL;
  mousex = (int*)malloc(sizeof(int));
  int *mousey = NULL;
  mousey = (int*)malloc(sizeof(int));
  int *control = NULL;
  control = (int*)malloc(sizeof(int));
  int option = 0;

  //message surfaces
  SDL_Surface *surContinue = NULL;
  surContinue = (SDL_Surface*)malloc(sizeof(SDL_Surface)); //state indicator
  SDL_Surface *surOptions = NULL;
  surOptions = (SDL_Surface*)malloc(sizeof(SDL_Surface)); //double jump indicator
  SDL_Surface *surQuit = NULL;
  surQuit = (SDL_Surface*)malloc(sizeof(SDL_Surface)); //dash indicator

  SDL_Texture *tempT = NULL;

  //text strings
  char *strContinue = NULL;
  strContinue = (char*)malloc(9 * sizeof(char));
  sprintf(strContinue, "Continue");

  char *strOptions = NULL;
  strOptions = (char*)malloc(8 * sizeof(char));
  sprintf(strOptions, "Options");

  char *strQuit = NULL;
  strQuit = (char*)malloc(5 * sizeof(char));
  sprintf(strQuit, "Quit");

  //text positions
  SDL_Rect *posContinue = NULL;
  posContinue = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posOptions = NULL;
  posOptions = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posQuit = NULL;
  posQuit = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  //event running the controls
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

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
    SDL_RenderClear(renderer);

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
        option = 1;

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
        option = 2;

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
        option = 3;

      }

    } else {
      //render the messages
      surContinue = TTF_RenderText_Solid(font, strContinue, *black);
      surOptions = TTF_RenderText_Solid(font, strOptions, *black);
      surQuit = TTF_RenderText_Solid(font, strQuit, *black);

    }

    //blitting the options on the window
    tempT = SDL_CreateTextureFromSurface(renderer, surContinue);
    SDL_QueryTexture(tempT, NULL, NULL, &(posContinue->w), &(posContinue->h));
    SDL_RenderCopy(renderer, tempT, NULL, posContinue);

    tempT = SDL_CreateTextureFromSurface(renderer, surOptions);
    SDL_QueryTexture(tempT, NULL, NULL, &(posOptions->w), &(posOptions->h));
    SDL_RenderCopy(renderer, tempT, NULL, posOptions);

    tempT = SDL_CreateTextureFromSurface(renderer, surQuit);
    SDL_QueryTexture(tempT, NULL, NULL, &(posQuit->w), &(posQuit->h));
    SDL_RenderCopy(renderer, tempT, NULL, posQuit);

    SDL_RenderPresent(renderer);

    SDL_Delay(200);

    if (option != 0 || *control == 10) {
      free(mousex);
      free(mousey);
      free(control);
      SDL_FreeSurface(surContinue);
      SDL_FreeSurface(surOptions);
      SDL_FreeSurface(surQuit);
      free(strContinue);
      free(strOptions);
      free(strQuit);
      free(posContinue);
      free(posOptions);
      free(posQuit);
      free(event);
      return option;
    }
  }
}
