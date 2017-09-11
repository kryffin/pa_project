/********************************/
/***** Langton's Ant by Niko ****/
/* Finished : August 13th, 2017 */
/******* Made in 4 hours ********/
/********************************/

#include "header.h"

/* FUNCTIONS */

void turn_right (ant *a) {

  if (a->dir == 3) a->dir = 0;
  else a->dir = a->dir + 1;

  return;
}

void turn_left (ant *a) {

  if (a->dir == 0) a->dir = 3;
  else a->dir = a->dir - 1;

  return;
}

void move (ant *a) {

  switch (a->dir) {

    case 0:
      //up
      a->pos.y -= 1;
      break;

    case 1:
      //right
      a->pos.x += 1;
      break;

    case 2:
      //down
      a->pos.y += 1;
      break;

    case 3:
      //left
      a->pos.x -= 1;
      break;

  }

  return;
}

void color_palette (SDL_Surface *surface, Uint32 *colors[]) {
  //Uint32 *colors[10];

  *colors[0] = SDL_MapRGB(surface->format, 255, 255, 255); //white
  *colors[1] = SDL_MapRGB(surface->format, 255, 0, 0); //red
  *colors[2] = SDL_MapRGB(surface->format, 0, 255, 0); //green
  *colors[3] = SDL_MapRGB(surface->format, 0, 0, 255); //blue
  *colors[4] = SDL_MapRGB(surface->format, 255, 255, 0); //yellow
  *colors[5] = SDL_MapRGB(surface->format, 255, 0, 255); //purple
  *colors[6] = SDL_MapRGB(surface->format, 0, 255, 255); //cyan
  *colors[7] = SDL_MapRGB(surface->format, 0, 0, 0); //black
  *colors[8] = SDL_MapRGB(surface->format, 125, 125, 125); //gray
  *colors[9] = SDL_MapRGB(surface->format, 255, 125, 0); //orange

  return;
}

void draw (SDL_Surface *surface, SDL_MouseButtonEvent mouse, Uint32 pixel) {
  short int x, y;
  for (x = mouse.x - 4; x <= mouse.x + 4; x++) {
    for (y = mouse.y - 4; y <= mouse.y + 4; y++) {
      put_pixel_color(surface, x, y, pixel);
    }
  }
  return;
}

Uint32 get_pixel_color (SDL_Surface *surface, int x, int y) {

  //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32 *)surface->pixels;

  //Get the requested pixel
  return pixels[ ( y * surface->w ) + x ];
}

void put_pixel_color (SDL_Surface *surface, int x, int y, Uint32 pixel) {

    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

void behavior (ant *a, SDL_Surface *surface, Uint32 palette[]) {

  if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[0]) {
    //white
    //put red turn right and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[1]);
    turn_right(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[1]) {
    //red
    //put green turn right and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[2]);
    turn_right(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[2]) {
    //green
    //put blue turn right and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[3]);
    turn_right(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[3]) {
    //blue
    //put yellow turn left and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[4]);
    turn_left(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[4]) {
    //yellow
    //put purple turn right and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[5]);
    turn_right(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[5]) {
    //purple
    //put cyan turn left and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[6]);
    turn_left(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[6]) {
    //cyan
    //put black turn left and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[7]);
    turn_left(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[7]) {
    //black
    //put gray turn right and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[8]);
    turn_right(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[8]) {
    //gray
    //put orange turn left and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[9]);
    turn_left(a);
    move(a);
  } else if (get_pixel_color(surface, a->pos.x, a->pos.y) == palette[9]) {
    //orange
    //put white turn right and move
    put_pixel_color(surface, a->pos.x, a->pos.y, palette[0]);
    turn_right(a);
    move(a);
  }

  return;
}

int main () {

  /* VARIABLES */

  //window
  SDL_Surface *screen = NULL; //surface of the screen
  SDL_Rect side;
  side.x = 0;
  side.y = 0;
  side.w = 683;
  side.h = 768;

  //text string
  char str[35] = "";

  //colors for the back
  int white, gray;

  //event running the controls
  SDL_Event event;

  //loop controller
  bool exit = false;

  //steps counter
  unsigned long int steps = 0; //between 0 and 4294967295

  //array of the colors
  Uint32 colors[10];

  //ant initialization at the center looking up
  ant a, b, c, d, e, f;
  a.dir = 0;
  a.pos.x = 683 / 2;
  a.pos.y = SCREEN_HEIGHT / 2;

  b.dir = 0;
  b.pos.x = 683 / 2;
  b.pos.y = SCREEN_HEIGHT / 2;

  c.dir = 0;
  c.pos.x = 683 / 2;
  c.pos.y = SCREEN_HEIGHT / 2;

  d.dir = 0;
  d.pos.x = (683 / 2) + 683;
  d.pos.y = SCREEN_HEIGHT / 2;

  e.dir = 0;
  e.pos.x = (683 / 2) + 683;
  e.pos.y = SCREEN_HEIGHT / 2;

  f.dir = 0;
  f.pos.x = (683 / 2) + 683;
  f.pos.y = SCREEN_HEIGHT / 2;

  /*************/

  //SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error while SDL initialization : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_WM_SetCaption("Langton's Ant", NULL);

  //screen initialization to 1000x800
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN);
  if (screen == NULL) {
    printf("Error during SetVideoMode : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //color palette
  colors[0] = SDL_MapRGB(screen->format, 255, 255, 255); //white
  colors[1] = SDL_MapRGB(screen->format, 255, 0, 0); //red
  colors[2] = SDL_MapRGB(screen->format, 0, 255, 0); //green
  colors[3] = SDL_MapRGB(screen->format, 0, 0, 255); //blue
  colors[4] = SDL_MapRGB(screen->format, 255, 255, 0); //yellow
  colors[5] = SDL_MapRGB(screen->format, 255, 0, 255); //purple
  colors[6] = SDL_MapRGB(screen->format, 0, 255, 255); //cyan
  colors[7] = SDL_MapRGB(screen->format, 0, 0, 0); //black
  colors[8] = SDL_MapRGB(screen->format, 125, 125, 125); //gray
  colors[9] = SDL_MapRGB(screen->format, 255, 125, 0); //orange

  //back colors
  white = SDL_MapRGB(screen->format, 255, 255, 255);
  gray = SDL_MapRGB(screen->format, 125, 125, 125);

  //filling the first screen with white
  SDL_FillRect(screen, NULL, white);

  SDL_FillRect(screen, &side, gray);

  while (!exit) {

    //managing the controls : q & escape to exit
    while (SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            //'q' key for left
            case SDLK_ESCAPE:
            case SDLK_q:
              exit = true;
              break;

            default:
              break;
          }
          break;

        case SDL_MOUSEBUTTONDOWN:
          draw(screen, event.button, colors[7]);
          break;

        default:
          break;
      }
    }

    /* ANT BEHAVIOR */

    behavior(&a, screen, colors);
    behavior(&b, screen, colors);
    behavior(&c, screen, colors);
    behavior(&d, screen, colors);
    behavior(&e, screen, colors);
    behavior(&f, screen, colors);

    /* STEPS */

    //adding steps if we can
    if (steps < 4294967295) {
      steps++;
    } else {
      exit = true;
    }

    //writing the steps
    sprintf(str, "Langton's Ant | Steps : %lu", steps);

    //printing the steps on the caption
    //SDL_WM_SetCaption(str, NULL);

    /* * * */

    SDL_Flip(screen);

    //SDL_Delay(1);
  }

  return EXIT_SUCCESS;
}
