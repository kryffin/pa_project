#ifndef TDPOINT_H
#define TDPOINT_H

typedef struct IntegerPoint {
  int x;
  int y;
} intpoint_t;

typedef struct FloatPoint_t {
  float x;
  float y;
} floatpoint_t;

/* 2dpoint.c */
floatpoint_t set_floatpoint (float x, float y);
void set_floatpoint_x (floatpoint_t *p, float x);
void set_floatpoint_y (floatpoint_t *p, float y);
intpoint_t set_intpoint (int x, int y);
void set_intpoint_x (intpoint_t *p, int x);
void set_intpoint_y (intpoint_t *p, int y);
float get_floatpoint_x (floatpoint_t p);
float get_floatpoint_y (floatpoint_t p);
int get_intpoint_x (intpoint_t p);
int get_intpoint_y (intpoint_t p);

#endif
