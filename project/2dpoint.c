#include "header.h"

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
