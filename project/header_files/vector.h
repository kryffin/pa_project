#ifndef VECTOR_H
#define VECTOR_H

#include <SDL2/SDL.h>
#include <math.h>

typedef struct Vector {
  float x;
  float y;
} vector_t;

/* vector.c */
vector_t normalize (vector_t v);
vector_t vector_direction (SDL_Rect a, SDL_Rect b);
float vector_length (vector_t v);
vector_t set_vector (float x, float y);
void set_vector_x (vector_t *v, float x);
void set_vector_y (vector_t *v, float y);
float get_vector_x (vector_t v);
float get_vector_y (vector_t v);

#endif
