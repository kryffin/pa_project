#include "header.h"

  /* SET */

void set_menu (menu *m, int nbOptions, char strOptions[nbOptions - 1][20], SDL_Surface surOptions[nbOptions-1], SDL_Rect posOptions[nbOptions - 1], short int control) {
  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < nbOptions; i++) {
    strcpy(m->strOptions[*i], strOptions[*i]);
  }

  set_menu_nbOptions(m, nbOptions);
  set_menu_surOptions(m, nbOptions, &surOptions[nbOptions - 1]);
  set_menu_posOptions(m, nbOptions, &posOptions[nbOptions - 1]);
  set_menu_control(m, control);

  return;
}

void set_menu_nbOptions (menu *m, int nbOptions) {
  m->nbOptions = nbOptions;

  return;
}

void set_menu_strOptions (menu *m, int nbOptions, char strOptions[nbOptions - 1][20]) {
  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < nbOptions; i++) {
    strcpy(m->strOptions[*i], strOptions[*i]);
  }

  free(i);

  return;
}

void set_menu_surOptions (menu *m, int nbOptions, SDL_Surface surOptions[nbOptions - 1]) {
  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < nbOptions; i++) {
    m.&(surOptions + *i) = surOptions[*i];
  }

  free(i);

  return;
}

void set_menu_posOptions (menu *m, int nbOptions, SDL_Rect posOptions[nbOptions - 1]) {
  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < nbOptions; i++) {
    m->posOptions[*i] = posOptions[*i];
  }

  free(i);

  return;
}

void set_menu_control (menu *m, short int control) {
  m->control = control;
}

  /* GET */

int get_menu_nbOptions (menu m) {
  return m.nbOptions;
}

short int get_menu_control (menu m) {
  return m.control;
}

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
int menu_display (menu *titleScreen, TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer, int *mousex, int *mousey) {

  //counters
  int *i, *j = NULL;
  i = (int*)malloc(sizeof(int));
  j = (int*)malloc(sizeof(int));

  //option used as return variable
  int *option = NULL;
  option = (int*)malloc(sizeof(int));
  *option = 0;

  //span for the display
  int *span = NULL;
  span = (int*)malloc(sizeof(int));
  *span = SCREEN_HEIGHT / get_menu_nbOptions(*titleScreen);

  //temporary texture to print the messages
  SDL_Texture *temp = NULL;

  for (*i = 0; *i < get_menu_nbOptions(*titleScreen); i++) {
    titleScreen->&(surOptions + *i) = TTF_RenderText_Solid(font, titleScreen->strOptions[*i], *black); //render the messages

    //messages positions
    titleScreen->posOptions[*i].x = (SCREEN_WIDTH / 2) - (titleScreen->surOptions[*i].clip_rect.w / 2);
    titleScreen->posOptions[*i].y = *span;
    *span += *span;
  }

  //event running the mouse control
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  while (1) {

    //fill the screen with white
    SDL_RenderClear(renderer);

    titleScreen->control = menu_controls(event, mousex, mousey);

    for (*i = 0; *i < get_menu_nbOptions(*titleScreen); i++) {
      if (mouse_hover_menu(*mousex, *mousey, titleScreen->posOptions[*i].x, titleScreen->posOptions[*i].y, titleScreen->surOptions[*i].clip_rect.w, titleScreen->surOptions[*i].clip_rect.h)) {

        switch (get_menu_control(*titleScreen)) {

          case 0:
            SDL_FreeSurface(titleScreen->surOptions[*i]);
            titleScreen->surOptions[*i] = TTF_RenderText_Solid(font, titleScreen->strOptions[*i], *green);
            break;

          case 1:
            SDL_FreeSurface(titleScreen->surOptions[*i]);
            titleScreen->surOptions[*i] = TTF_RenderText_Solid(font, titleScreen->strOptions[*i], *red);
            break;

          case 2:
            SDL_FreeSurface(titleScreen->surOptions[*i]);
            titleScreen->surOptions[*i] = TTF_RenderText_Solid(font, titleScreen->strOptions[*i], *green);
            *option = *i;
            break;

          default:
            for (*j = 0; *j < get_menu_nbOptions(*titleScreen); j++) {
              SDL_FreeSurface(titleScreen->surOptions[*i]);
              titleScreen->surOptions[*i] = TTF_RenderText_Solid(font, titleScreen->strOptions[*i], *black);
            }
            break;

        }

      }
    }

    for (*i = 0; *i < get_menu_nbOptions(*titleScreen); i++) {
      //blitting the options on the window
      temp = SDL_CreateTextureFromSurface(renderer, titleScreen->surOptions[*i]);
      SDL_QueryTexture(temp, NULL, NULL, titleScreen->posOptions[*i].w, titleScreen->posOptions[*i].h);
      SDL_RenderCopy(renderer, temp, NULL, titleScreen->posOptions[*i]);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(200);

    if (*option != 0 || get_menu_control(*titleScreen) == 10) {
      free(i);
      free(j);
      free(span);
      free(event);
      return *option;
    }

  }

}

/*int menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer) {

  int *mousex = NULL;
  mousex = (int*)malloc(sizeof(int));
  int *mousey = NULL;
  mousey = (int*)malloc(sizeof(int));
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
  posContinue->x = (SCREEN_WIDTH / 2) - (surContinue.clip_rect.w / 2);
  posContinue->y = (SCREEN_HEIGHT / 2) - (surContinue.clip_rect.h / 2) - 100;
  posOptions->x = (SCREEN_WIDTH / 2) - (surOptions.clip_rect.w / 2);
  posOptions->y = (SCREEN_HEIGHT / 2) - (surOptions.clip_rect.h / 2);
  posQuit->x = (SCREEN_WIDTH / 2) - (surQuit.clip_rect.w / 2);
  posQuit->y = (SCREEN_HEIGHT / 2) - (surQuit.clip_rect.h / 2) + 100;

  while (1) {

    //fill the screen with white
    SDL_RenderClear(renderer);

    //controls
    *control = menu_controls(event, mousex, mousey);

    if (*mousex <= ((SCREEN_WIDTH / 2) - (surContinue.clip_rect.w / 2)) + surContinue.clip_rect.w
        && *mousex >= ((SCREEN_WIDTH / 2) - (surContinue.clip_rect.w / 2))
        && *mousey <= ((SCREEN_HEIGHT / 2) - (surContinue.clip_rect.h / 2) - 100) + surContinue.clip_rect.h
        && *mousey >= ((SCREEN_HEIGHT / 2) - (surContinue.clip_rect.h / 2) - 100)) {

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

    } else if (*mousex <= ((SCREEN_WIDTH / 2) - (surOptions.clip_rect.w / 2)) + surOptions.clip_rect.w
              && *mousex >= ((SCREEN_WIDTH / 2) - (surOptions.clip_rect.w / 2))
              && *mousey <= ((SCREEN_HEIGHT / 2) - (surOptions.clip_rect.h / 2)) + surOptions.clip_rect.h
              && *mousey >= ((SCREEN_HEIGHT / 2) - (surOptions.clip_rect.h / 2))) {

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

    } else if (*mousex <= ((SCREEN_WIDTH / 2) - (surQuit.clip_rect.w / 2)) + surQuit.clip_rect.w
              && *mousex >= ((SCREEN_WIDTH / 2) - (surQuit.clip_rect.w / 2))
              && *mousey <= ((SCREEN_HEIGHT / 2) - (surQuit.clip_rect.h / 2) + 100) + surQuit.clip_rect.h
              && *mousey >= ((SCREEN_HEIGHT / 2) - (surQuit.clip_rect.h / 2) + 100)) {

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
}*/
