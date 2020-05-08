#ifndef ENGINE_H
#define ENGINE_H
#include "constants.h"
#include <inttypes.h>
typedef struct {
  uint8_t *pixels;
  int height;
  int width;
  int args[MAX_ARG];
  char filename[100];
} Canvas;

int engine_init(Canvas *canvas);
int engine_create(Canvas *canvas);
int _engine_draw_point(Canvas *canvas, int x, int y, int scale);
void engine_draw_point(Canvas *canvas);

int _engine_draw_line(Canvas *canvas, int x0, int y0, int x1, int y1, int scale);
void engine_draw_line(Canvas *canvas);

int _engine_draw_rectangle(Canvas *canvas, int x0, int y0, int width, int height,
                           int scale);
void engine_draw_rectangle(Canvas *canvas);

int _engine_draw_circle(Canvas *canvas, int center_x, int center_y, int radius,
                        int scale);
void engine_draw_circle(Canvas *canvas);

int _engine_draw_disk(Canvas *canvas, int center_x, int center_y, int radius,
                      int scale);
void engine_draw_disk(Canvas *canvas);

int engine_save(Canvas *canvas);
int engine_close(Canvas *canvas);
#endif