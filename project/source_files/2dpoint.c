/*

2dpoint.c : contain every functions for integer 2d points and real 2d points

*/

#include "../header_files/2dpoint.h"

/* SET */

//returns a new point with float coordinates
floatpoint_t set_floatpoint (float x, float y) {
  floatpoint_t p;
  p.x = x;
  p.y = y;
  return p;
}

//change the x coordinate of a floatpoint
void set_floatpoint_x (floatpoint_t *p, float x) {
  p->x = x;
  return;
}

//change the y coordinate of a floatpoint
void set_floatpoint_y (floatpoint_t *p, float y) {
  p->y = y;
  return;
}

//---------------

//returns a new point with integer coordinates
intpoint_t set_intpoint(int x, int y) {
  intpoint_t p;
  p.x = x;
  p.y = y;
  return p;
}

//change the x coordinate of an intpoint
void set_intpoint_x (intpoint_t *p, int x) {
  p->x = x;
  return;
}

//change the y coordinate of an intpoint
void set_intpoint_y (intpoint_t *p, int y) {
  p->y = y;
  return;
}

/* * * * * * Get * * * * * */

//returns the x coordinate of a floatpoint
float get_floatpoint_x (floatpoint_t p) {
  return p.x;
}
//returns the y coordinate of a floatpoint
float get_floatpoint_y (floatpoint_t p) {
  return p.y;
}

//----------------

//returns the x coordinate of an intpoint
int get_intpoint_x (intpoint_t p) {
  return p.x;
}

//returns the y coordinate of an intpoint
int get_intpoint_y (intpoint_t p) {
  return p.y;
}
