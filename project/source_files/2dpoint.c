#include "../header_files/2dpoint.h"

bool collision_intpoint (intpoint_t a, intpoint_t b) {
  //a : block, b : player

  if (((get_intpoint_x(a) >= get_intpoint_x(b) && get_intpoint_x(a) <= get_intpoint_x(b) + IMG_WIDTH) || (get_intpoint_x(a) + 16 >= get_intpoint_x(b) && get_intpoint_x(a) + 16 <= get_intpoint_x(b) + IMG_WIDTH))) {

    if (((get_intpoint_y(a) >= get_intpoint_y(b) && get_intpoint_y(a) <= get_intpoint_y(b) + IMG_HEIGHT) || (get_intpoint_y(a) + 16 >= get_intpoint_y(b) && get_intpoint_y(a) + 16 <= get_intpoint_y(b) + IMG_HEIGHT))) {

      return true;

    }

  }

  return false;
}


/* * * * * * Set * * * * * */

floatpoint_t set_floatpoint (float x, float y) {
  floatpoint_t p;
  p.x = x;
  p.y = y;
  return p;
}

void set_floatpoint_x (floatpoint_t *p, float x) {
  p->x = x;
  return;
}

void set_floatpoint_y (floatpoint_t *p, float y) {
  p->y = y;
  return;
}

//---------------

intpoint_t set_intpoint(int x, int y) {
  intpoint_t p;
  p.x = x;
  p.y = y;
  return p;
}

void set_intpoint_x (intpoint_t *p, int x) {
  p->x = x;
  return;
}

void set_intpoint_y (intpoint_t *p, int y) {
  p->y = y;
  return;
}

/* * * * * * Get * * * * * */

float get_floatpoint_x (floatpoint_t p) {
  return p.x;
}

float get_floatpoint_y (floatpoint_t p) {
  return p.y;
}

//----------------

int get_intpoint_x (intpoint_t p) {
  return p.x;
}

int get_intpoint_y (intpoint_t p) {
  return p.y;
}
