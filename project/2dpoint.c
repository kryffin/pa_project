#include "header.h"

/* * * * * * Set * * * * * */

floatpoint set_floatpoint (float x, float y) {
  floatpoint p;
  p.x = x;
  p.y = y;
  return p;
}

void set_floatpoint_x (floatpoint *p, float x) {
  p->x = x;
  return;
}

void set_floatpoint_y (floatpoint *p, float y) {
  p->y = y;
  return;
}

//---------------

intpoint set_intpoint (int x, int y) {
  intpoint p;
  p.x = x;
  p.y = y;
  return p;
}

void set_intpoint_x (intpoint *p, int x) {
  p->x = x;
  return;
}

void set_intpoint_y (intpoint *p, int y) {
  p->y = y;
  return;
}

/* * * * * * Get * * * * * */

float get_floatpoint_x (floatpoint p) {
  return p.x;
}

float get_floatpoint_y (floatpoint p) {
  return p.y;
}

//----------------

int get_intpoint_x (intpoint p) {
  return p.x;
}

int get_intpoint_y (intpoint p) {
  return p.y;
}
