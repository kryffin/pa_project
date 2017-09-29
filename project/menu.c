#include "header.h"

  /* FUNCTIONS */

//function returning the state of the mouse :
/* 0 : no motion
   1 : button down
   2 : button up
   10 : quit
*/
int menu_controls(SDL_Event *event, SDL_Rect *mouse_pos) {
  //controls
  while (SDL_PollEvent(event)) {
    switch(event->type) {
      case SDL_MOUSEMOTION:
        mouse_pos->x = event->motion.x;
        mouse_pos->y = event->motion.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        return 1;
        break;

      case SDL_MOUSEBUTTONUP:
        return 2;
        break;

      case SDL_KEYDOWN:
        if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          return 10;
        }
        break;

      case SDL_QUIT:
        return 10;
        break;

      default:
        break;
    }
  }

  return 0;
}

//returns true if the mouse is hovering the target
bool mouse_hover_menu (SDL_Rect mouse_pos, int targetx, int targety, int width, int height) {
  if(mouse_pos.x >= targetx && mouse_pos.x <= targetx + width && mouse_pos.y >= targety && mouse_pos.y <= targety + height) {
    return true;
  }
  return false;
}

/*display of the menu which returns :
  1 : Continue
  2 : Options
  3 : Quit
*/

int main_menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer, SDL_Rect *mouse_pos, SDL_Texture *cursor) {

  int *control = NULL;
  control = (int*)malloc(sizeof(int));
  int *option = NULL;
  option = (int*)malloc(sizeof(int));
  *option = 0;

  //message surfaces
  SDL_Surface *surContinue = NULL;
  SDL_Surface *surOptions = NULL;
  SDL_Surface *surQuit = NULL;

  SDL_Texture *tempT = NULL;

  //text strings
  char *strFull = NULL;
  strFull = (char*)malloc(9 * sizeof(char));
  sprintf(strFull, "New game");

  char *str43 = NULL;
  str43 = (char*)malloc(8 * sizeof(char));
  sprintf(str43, "Options");

  char *str1610 = NULL;
  str1610 = (char*)malloc(5 * sizeof(char));
  sprintf(str1610, "Quit");

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
  surContinue = TTF_RenderText_Solid(font, strFull, *black);
  surOptions = TTF_RenderText_Solid(font, str43, *black);
  surQuit = TTF_RenderText_Solid(font, str1610, *black);

  //message positions
  posContinue->x = (SCREEN_WIDTH / 2) - (surContinue->clip_rect.w / 2);
  posContinue->y = (SCREEN_HEIGHT / 2) - (surContinue->clip_rect.h / 2) - (SCREEN_HEIGHT / 3);
  posOptions->x = (SCREEN_WIDTH / 2) - (surOptions->clip_rect.w / 2);
  posOptions->y = (SCREEN_HEIGHT / 2) - (surOptions->clip_rect.h / 2);
  posQuit->x = (SCREEN_WIDTH / 2) - (surQuit->clip_rect.w / 2);
  posQuit->y = (SCREEN_HEIGHT / 2) - (surQuit->clip_rect.h / 2) + (SCREEN_HEIGHT / 3);

  while (1) {

    //fill the screen with white
    SDL_RenderClear(renderer);

    //controls
    *control = menu_controls(event, mouse_pos);
    cursor_render(cursor, renderer, *mouse_pos);

    if (mouse_hover_menu(*mouse_pos, posContinue->x, posContinue->y, surContinue->clip_rect.w, surContinue->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strFull, *green);

      } else if (*control == 1){

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strFull, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strFull, *green);
        *option = 1;

      }

    } else if (mouse_hover_menu(*mouse_pos, posOptions->x, posOptions->y, surOptions->clip_rect.w, surOptions->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(font, str43, *green);

      } else if (*control == 1){

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(font, str43, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(font, str43, *green);
        *option = 2;

      }

    } else if (mouse_hover_menu(*mouse_pos, posQuit->x, posQuit->y, surQuit->clip_rect.w, surQuit->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surQuit);
        surQuit = TTF_RenderText_Solid(font, str1610, *green);

      } else if (*control == 1) {

        SDL_FreeSurface(surQuit);
        surQuit = TTF_RenderText_Solid(font, str1610, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surContinue);
        surContinue = TTF_RenderText_Solid(font, strFull, *green);
        *option = 3;

      }

    } else {
      //render the messages
      SDL_FreeSurface(surContinue);
      surContinue = TTF_RenderText_Solid(font, strFull, *black);
      SDL_FreeSurface(surOptions);
      surOptions = TTF_RenderText_Solid(font, str43, *black);
      SDL_FreeSurface(surQuit);
      surQuit = TTF_RenderText_Solid(font, str1610, *black);

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

    SDL_Delay(1000 / SCREEN_FPS);

    //if we escape
    if (*control == 10) {
      *option = 3;
    }

    if (*option != 0) {
      free(control);
      SDL_FreeSurface(surContinue);
      SDL_FreeSurface(surOptions);
      SDL_FreeSurface(surQuit);
      free(strFull);
      free(str43);
      free(str1610);
      free(posContinue);
      free(posOptions);
      free(posQuit);
      free(event);
      return *option;
    }
  }
}

/* resolution options menu */

/* 1 : FullScreen | 2 : 4:3 | 3 : 16:10 | 4 : 16:9 | 5 : Ad | 6 : Back */
int option_menu_display (TTF_Font *font, SDL_Color *black, SDL_Color *green, SDL_Color *red, SDL_Renderer *renderer, SDL_Rect *mouse_pos, SDL_Texture *cursor) {

  int *control = NULL;
  control = (int*)malloc(sizeof(int));
  int *option = NULL;
  option = (int*)malloc(sizeof(int));
  *option = 0;

  //message surfaces
  SDL_Surface *surFull = NULL;
  SDL_Surface *sur43 = NULL;
  SDL_Surface *sur1610 = NULL;
  SDL_Surface *sur169 = NULL;
  SDL_Surface *surAd = NULL;
  SDL_Surface *surBack = NULL;

  SDL_Texture *tempT = NULL;

  //text strings
  char *strFull = NULL;
  strFull = (char*)malloc(9 * sizeof(char));
  sprintf(strFull, "Full Screen");

  char *str43 = NULL;
  str43 = (char*)malloc(8 * sizeof(char));
  sprintf(str43, "640 x 480 (4:3)");

  char *str1610 = NULL;
  str1610 = (char*)malloc(5 * sizeof(char));
  sprintf(str1610, "1440 x 900 (16:10)");

  char *str169 = NULL;
  str169 = (char*)malloc(9 * sizeof(char));
  sprintf(str169, "1920 x 1080 (16:9)");

  char *strAd = NULL;
  strAd = (char*)malloc(8 * sizeof(char));
  sprintf(strAd, "Adjust");

  char *strBack = NULL;
  strBack = (char*)malloc(5 * sizeof(char));
  sprintf(strBack, "Back");

  //text positions
  SDL_Rect *posFull = NULL;
  posFull = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *pos43 = NULL;
  pos43 = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *pos1610 = NULL;
  pos1610 = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *pos169 = NULL;
  pos169 = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posAd = NULL;
  posAd = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posBack = NULL;
  posBack = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  //event running the controls
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //render the messages
  surFull = TTF_RenderText_Solid(font, strFull, *black);
  sur43 = TTF_RenderText_Solid(font, str43, *black);
  sur1610 = TTF_RenderText_Solid(font, str1610, *black);
  sur169 = TTF_RenderText_Solid(font, str169, *black);
  surAd = TTF_RenderText_Solid(font, strAd, *black);
  surBack = TTF_RenderText_Solid(font, strBack, *black);

  int *span = NULL;
  span = (int*)malloc(sizeof(int));
  *span = (SCREEN_HEIGHT / 6);

  //message positions
  posFull->x = (SCREEN_WIDTH / 2) - (surFull->clip_rect.w / 2);
  posFull->y = 0;
  pos43->x = (SCREEN_WIDTH / 2) - (sur43->clip_rect.w / 2);
  pos43->y = (*span * 1);
  pos1610->x = (SCREEN_WIDTH / 2) - (sur1610->clip_rect.w / 2);
  pos1610->y = (*span * 2);
  pos169->x = (SCREEN_WIDTH / 2) - (sur169->clip_rect.w / 2);
  pos169->y = (*span * 3);
  posAd->x = (SCREEN_WIDTH / 2) - (surAd->clip_rect.w / 2);
  posAd->y = (*span * 4);
  posBack->x = (SCREEN_WIDTH / 2) - (surBack->clip_rect.w / 2);
  posBack->y = (*span * 5);

  free(span);

  while (1) {

    //fill the screen with white
    SDL_RenderClear(renderer);

    //controls
    *control = menu_controls(event, mouse_pos);
    cursor_render(cursor, renderer, *mouse_pos);

    if (mouse_hover_menu(*mouse_pos, posFull->x, posFull->y, surFull->clip_rect.w, surFull->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surFull);
        surFull = TTF_RenderText_Solid(font, strFull, *green);

      } else if (*control == 1){

        SDL_FreeSurface(surFull);
        surFull = TTF_RenderText_Solid(font, strFull, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surFull);
        surFull = TTF_RenderText_Solid(font, strFull, *green);
        *option = 1;

      }

    } else if (mouse_hover_menu(*mouse_pos, pos43->x, pos43->y, sur43->clip_rect.w, sur43->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(sur43);
        sur43 = TTF_RenderText_Solid(font, str43, *green);

      } else if (*control == 1){

        SDL_FreeSurface(sur43);
        sur43 = TTF_RenderText_Solid(font, str43, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(sur43);
        sur43 = TTF_RenderText_Solid(font, str43, *green);
        *option = 2;

      }

    } else if (mouse_hover_menu(*mouse_pos, pos1610->x, pos1610->y, sur1610->clip_rect.w, sur1610->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(sur1610);
        sur1610 = TTF_RenderText_Solid(font, str1610, *green);

      } else if (*control == 1) {

        SDL_FreeSurface(sur1610);
        sur1610 = TTF_RenderText_Solid(font, str1610, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(sur1610);
        sur1610 = TTF_RenderText_Solid(font, str1610, *green);
        *option = 3;

      }

    } else if (mouse_hover_menu(*mouse_pos, pos169->x, pos169->y, sur169->clip_rect.w, sur169->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(sur169);
        sur169 = TTF_RenderText_Solid(font, str169, *green);

      } else if (*control == 1) {

        SDL_FreeSurface(sur169);
        sur169 = TTF_RenderText_Solid(font, str169, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(sur169);
        sur169 = TTF_RenderText_Solid(font, str169, *green);
        *option = 4;

      }

    } else if (mouse_hover_menu(*mouse_pos, posAd->x, posAd->y, surAd->clip_rect.w, surAd->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surAd);
        surAd = TTF_RenderText_Solid(font, strAd, *green);

      } else if (*control == 1) {

        SDL_FreeSurface(surAd);
        surAd = TTF_RenderText_Solid(font, strAd, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surAd);
        surAd = TTF_RenderText_Solid(font, strAd, *green);
        *option = 5;

      }

    } else if (mouse_hover_menu(*mouse_pos, posBack->x, posBack->y, surBack->clip_rect.w, surBack->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surBack);
        surBack = TTF_RenderText_Solid(font, strBack, *green);

      } else if (*control == 1) {

        SDL_FreeSurface(surBack);
        surBack = TTF_RenderText_Solid(font, strBack, *red);

      } else if (*control == 2) {

        SDL_FreeSurface(surBack);
        surBack = TTF_RenderText_Solid(font, strBack, *green);
        *option = 6;

      }

    } else {

      //reset the messages
      SDL_FreeSurface(surFull);
      surFull = TTF_RenderText_Solid(font, strFull, *black);
      SDL_FreeSurface(sur43);
      sur43 = TTF_RenderText_Solid(font, str43, *black);
      SDL_FreeSurface(sur1610);
      sur1610 = TTF_RenderText_Solid(font, str1610, *black);
      SDL_FreeSurface(sur169);
      sur169 = TTF_RenderText_Solid(font, str169, *black);
      SDL_FreeSurface(surAd);
      surAd = TTF_RenderText_Solid(font, strAd, *black);
      SDL_FreeSurface(surBack);
      surBack = TTF_RenderText_Solid(font, strBack, *black);

    }

    //blitting the options on the window
    tempT = SDL_CreateTextureFromSurface(renderer, surFull);
    SDL_QueryTexture(tempT, NULL, NULL, &(posFull->w), &(posFull->h));
    SDL_RenderCopy(renderer, tempT, NULL, posFull);

    tempT = SDL_CreateTextureFromSurface(renderer, sur43);
    SDL_QueryTexture(tempT, NULL, NULL, &(pos43->w), &(pos43->h));
    SDL_RenderCopy(renderer, tempT, NULL, pos43);

    tempT = SDL_CreateTextureFromSurface(renderer, sur1610);
    SDL_QueryTexture(tempT, NULL, NULL, &(pos1610->w), &(pos1610->h));
    SDL_RenderCopy(renderer, tempT, NULL, pos1610);

    tempT = SDL_CreateTextureFromSurface(renderer, sur169);
    SDL_QueryTexture(tempT, NULL, NULL, &(pos169->w), &(pos169->h));
    SDL_RenderCopy(renderer, tempT, NULL, pos169);

    tempT = SDL_CreateTextureFromSurface(renderer, surAd);
    SDL_QueryTexture(tempT, NULL, NULL, &(posAd->w), &(posAd->h));
    SDL_RenderCopy(renderer, tempT, NULL, posAd);

    tempT = SDL_CreateTextureFromSurface(renderer, surBack);
    SDL_QueryTexture(tempT, NULL, NULL, &(posBack->w), &(posBack->h));
    SDL_RenderCopy(renderer, tempT, NULL, posBack);

    SDL_RenderPresent(renderer);

    SDL_Delay(1000 / SCREEN_FPS);

    //if we escape
    if (*control == 10) {
      *option = 3;
    }

    if (option != 0) {
      free(control);
      SDL_FreeSurface(surFull);
      SDL_FreeSurface(sur43);
      SDL_FreeSurface(sur1610);
      SDL_FreeSurface(sur169);
      SDL_FreeSurface(surAd);
      SDL_FreeSurface(surBack);
      free(strFull);
      free(str43);
      free(str1610);
      free(str169);
      free(strAd);
      free(strBack);
      free(posFull);
      free(pos43);
      free(pos1610);
      free(pos169);
      free(posAd);
      free(posBack);
      free(event);
      return *option;
    }
  }
}
