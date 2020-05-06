#ifndef ENGINE_H
#define ENGINE_H
#include "constants.h"
#include <inttypes.h>
typedef struct {
  uint8_t *drawing;
  int height;
  int width;
  int args[MAX_ARG];
} Data;

int engine_init(Data *data);
int engine_create(Data *data);
int engine_draw_point(Data *data, int x, int y, int scale);
int engine_draw_line(Data *data, int x0, int y0, int x1, int y1, int scale);
int engine_draw_rectangle(Data *data, int x0, int y0, int width, int height,
                          int scale);
int engine_draw_circle(Data *data, int center_x, int center_y, int radius,
                       int scale);
int engine_save(Data *data);
int engine_close(Data *data);
#endif