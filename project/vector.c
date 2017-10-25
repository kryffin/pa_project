#include "header.h"

vector_t normalize (vector_t v) {
  float temp = vector_length(v);
  set_vector_x(&v, get_vector_x(v) / temp);
  set_vector_y(&v, get_vector_y(v) / temp);
  return v;
}

vector_t vector_direction (SDL_Rect a, SDL_Rect b) {
  vector_t v;
  set_vector_x(&v, b.x - a.x);
  set_vector_y(&v, b.y - a.y);
  return v;
}

float vector_length (vector_t v) {
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

/* * * * * * Set * * * * * */

vector_t set_vector (float x, float y) {
  vector_t v;
  set_vector_x(&v, x);
  set_vector_y(&v, y);
  return v;
}

void set_vector_x (vector_t *v, float x) {
  v->x = x;
  return;
}

void set_vector_y (vector_t *v, float y) {
  v->y = y;
  return;
}

/* * * * * * Get * * * * * */

float get_vector_x (vector_t v) {
  return v.x;
}

float get_vector_y (vector_t v) {
  return v.y;
}
