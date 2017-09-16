#include "header.h"

  /* FUNCTIONS */

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

//returns true if the mouse is hovering the target
bool mouse_hover_menu (int mousex, int mousey, int targetx, int targety, int width, int height) {
  if(mousex >= targetx && mousex <= targetx + width && mousey >= targety && mousey <= targety + height) {
    return true;
  }
  return false;
}

/*display of the menu which returns :
  1 : Continue
  2 : Options
  3 : Quit
*/

int main_menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer, int *mousex, int *mousey) {

  int *control = NULL;
  control = (int*)malloc(sizeof(int));
  int option = 0;

  //message surfaces
  SDL_Surface *surContinue = NULL;
  SDL_Surface *surOptions = NULL;
  SDL_Surface *surQuit = NULL;

  SDL_Texture *tempT = NULL;

  //text strings
  char *strContinue = NULL;
  strContinue = (char*)malloc(9 * sizeof(char));
  sprintf(strContinue, "New game");

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

    if (mouse_hover_menu(*mousex, *mousey, posContinue->x, posContinue->y, surContinue->clip_rect.w, surContinue->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strContinue, *green);

      } else if (*control == 1){

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strContinue, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strContinue, *green);
        option = 1;

      }

    } else if (mouse_hover_menu(*mousex, *mousey, posOptions->x, posOptions->y, surOptions->clip_rect.w, surOptions->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(font, strOptions, *green);

      } else if (*control == 1){

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(font, strOptions, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(font, strOptions, *green);
        option = 2;

      }

    } else if (mouse_hover_menu(*mousex, *mousey, posQuit->x, posQuit->y, surQuit->clip_rect.w, surQuit->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surQuit);
        surQuit = TTF_RenderText_Solid(font, strQuit, *green);

      } else if (*control == 1) {

        SDL_FreeSurface(surQuit);
        surQuit = TTF_RenderText_Solid(font, strQuit, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strContinue, *green);
        option = 3;

      }

    } else {
      //render the messages
      SDL_FreeSurface(surContinue);
      surContinue = TTF_RenderText_Solid(font, strContinue, *black);
      SDL_FreeSurface(surOptions);
      surOptions = TTF_RenderText_Solid(font, strOptions, *black);
      SDL_FreeSurface(surQuit);
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
