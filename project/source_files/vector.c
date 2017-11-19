/*

vector.c : contain the functions for the vectors

*/

#include "../header_files/vector.h"

//returns the normalized vector
vector_t normalize (vector_t v) {
  float temp = vector_length(v);
  set_vector_x(&v, get_vector_x(v) / temp);
  set_vector_y(&v, get_vector_y(v) / temp);
  return v;
}

//return a direction vector between a and b
vector_t vector_direction (SDL_Rect a, SDL_Rect b) {
  vector_t v;
  set_vector_x(&v, b.x - a.x);
  set_vector_y(&v, b.y - a.y);
  return v;
}

//returns the length of a vector
float vector_length (vector_t v) {
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

/* SET */

//create a new vector
vector_t set_vector (float x, float y) {
  vector_t v;
  set_vector_x(&v, x);
  set_vector_y(&v, y);
  return v;
}

//set the x coordinate
void set_vector_x (vector_t *v, float x) {
  v->x = x;
  return;
}

//set the y coordinate
void set_vector_y (vector_t *v, float y) {
  v->y = y;
  return;
}

/* GET */

//get the x coordinate
float get_vector_x (vector_t v) {
  return v.x;
}

//get the y coordinate
float get_vector_y (vector_t v) {
  return v.y;
}
