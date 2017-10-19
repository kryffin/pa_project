#include "header.h"

vector normalize (vector v) {
  float temp = vector_length(v);
  set_vector_x(&v, get_vector_x(v) / temp);
  set_vector_y(&v, get_vector_y(v) / temp);
  return v;
}

vector vector_direction (SDL_Rect a, SDL_Rect b) {
  vector v;
  set_vector_x(&v, b.x - a.x);
  set_vector_y(&v, b.y - a.y);
  return v;
}

float vector_length (vector v) {
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

/* * * * * * Set * * * * * */

vector set_vector (float x, float y) {
  vector v;
  set_vector_x(&v, x);
  set_vector_y(&v, y);
  return v;
}

void set_vector_x (vector *v, float x) {
  v->x = x;
  return;
}

void set_vector_y (vector *v, float y) {
  v->y = y;
  return;
}

/* * * * * * Get * * * * * */

float get_vector_x (vector v) {
  return v.x;
}

float get_vector_y (vector v) {
  return v.y;
}
