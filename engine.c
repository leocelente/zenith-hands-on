/**
 * @file engine.c
 * @author Leonardo Celente (@leocelente)
 * @brief Main Business Logic for creating PGM files
 * @version 0.1
 * @date 2020-04-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "engine.h"
#include "constants.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int engine_init(Canvas *canvas) {
  canvas->pixels = NULL;
  canvas->height = 0;
  canvas->width = 0;
  return 1;
}
/**
 * @brief creates file
 *
 * @param args [width, height]
 * @return int
 */
int engine_create(Canvas *canvas) {
  canvas->width = canvas->args[0];
  canvas->height = canvas->args[1];
  size_t sz = sizeof(int) * canvas->width * canvas->height;
  canvas->pixels = malloc(sz);
  if (canvas->pixels == NULL) {
    printf("malloc failed : pixels");
    return 0;
  }
  for (size_t i = 0; i < sz; ++i) {
    // fills with white
    canvas->pixels[i] = 255;
  }
  printf("\tCreated\n");
  return 1;
}
/**
 * @brief saves file
 *
 * @param canvas
 * @param args [char* filename]
 * @return int
 */
int engine_save(Canvas *canvas) {
  char *filename = canvas->filename;//"test.pgm";//(char *)canvas->args[0];
  FILE *file_handler = NULL;
  printf("\tCreating %s\n", filename);
  file_handler = fopen(filename, "w+");
  if (file_handler == NULL) {
    printf("\tFailed to create file");
    return 0;
  }
  // write magic number
  fprintf(file_handler, "P2\n");
  // write height, width
  fprintf(file_handler, "%d %d\n", canvas->height, canvas->width);
  // write scale
  fprintf(file_handler, "%d\n", UINT8_MAX);
  // write file contents
  for (size_t i = 0; i < canvas->height; ++i) {
    for (size_t j = 0; j < canvas->width; ++j) {
      fprintf(file_handler, " %d ", (canvas->pixels[i * canvas->width + j]));
    }
    fprintf(file_handler, "\n");
  }
  fclose(file_handler);
  return 1;
}

int engine_close(Canvas *canvas) {
  free(canvas->pixels);
  return 0;
}

void engine_draw_point(Canvas *canvas) {
  _engine_draw_point(canvas, canvas->args[0], canvas->args[1], canvas->args[2]);
}
int _engine_draw_point(Canvas *canvas, int x, int y, int scale) {
  if (x < 0 || y < 0)
    return 0;
  if (x <= canvas->width && y <= canvas->height) {
    if (scale >= UINT8_MAX)
      scale = 255;
    if (scale <= 0)
      scale = 0;
    canvas->pixels[y * canvas->height + x] = scale;
    return 1;
  } else {
    printf("\tOut of bounds\n");
    return 0;
  }
}

void engine_draw_line(Canvas *canvas) {
  _engine_draw_line(canvas, canvas->args[0], canvas->args[1], canvas->args[2],
                    canvas->args[3], canvas->args[4]);
}
int _engine_draw_line(Canvas *canvas, int x0, int y0, int x1, int y1, int scale) {
  printf("pixels line");
  int begin_x, end_x, begin_y, end_y;
  if (x0 < x1) {
    begin_x = x0;
    end_x = x1;
  } else {
    begin_x = x1;
    end_x = x0;
  }
  if (y0 < y1) {
    begin_y = y0;
    end_y = y1;
  } else {
    begin_y = y1;
    end_y = y0;
  }

  int dx = end_x - begin_x;
  int dy = end_y - begin_y;

  //   int x = begin_x;
  int y = begin_y;
  //   int p = 2 * dy - dx;
  printf("\tDrawing %d from (%d, %d) to (%d,%d)", scale, begin_x, begin_y,
         end_x, end_y);
  for (int x = begin_x; x < end_x; x++) {
    y = begin_y + dy * (x - begin_x) / dx;
    _engine_draw_point(canvas, x, y, scale);
  }
  if (dx == 0) {
    for (int y = begin_y; y <= end_y; ++y) {
      _engine_draw_point(canvas, begin_x, y, scale);
    }
  }
  printf("\n");
  return 1;
}

void engine_draw_rectangle(Canvas *canvas) {
  _engine_draw_rectangle(canvas, canvas->args[0], canvas->args[1], canvas->args[2],
                         canvas->args[3], canvas->args[4]);
}
int _engine_draw_rectangle(Canvas *canvas, int x0, int y0, int width, int height,
                           int scale) {
  if (x0 + width > canvas->width)
    width = canvas->width - x0;
  if (y0 + height > canvas->height)
    height = canvas->height - y0;
  _engine_draw_line(canvas, x0, y0, x0 + width, y0, scale);
  _engine_draw_line(canvas, x0, y0, x0, y0 + height, scale);
  _engine_draw_line(canvas, x0 + width, y0, x0 + width, y0 + height, scale);
  _engine_draw_line(canvas, x0, y0 + height, x0 + width, y0 + height, scale);

  return 1;
}

void drawCircle(Canvas *canvas, int xc, int yc, int x, int y, int scale) {
  _engine_draw_point(canvas, xc + x, yc + y, scale);
  _engine_draw_point(canvas, xc - x, yc + y, scale);
  _engine_draw_point(canvas, xc + x, yc - y, scale);
  _engine_draw_point(canvas, xc - x, yc - y, scale);
  _engine_draw_point(canvas, xc + y, yc + x, scale);
  _engine_draw_point(canvas, xc - y, yc + x, scale);
  _engine_draw_point(canvas, xc + y, yc - x, scale);
  _engine_draw_point(canvas, xc - y, yc - x, scale);
}
void engine_draw_circle(Canvas *canvas) {
  _engine_draw_circle(canvas, canvas->args[0], canvas->args[1], canvas->args[2],
                      canvas->args[3]);
}
int _engine_draw_circle(Canvas *canvas, int center_x, int center_y, int radius,
                        int scale) {
  int x = 0;
  int y = radius;
  int d = 3 - 2 * radius;
  drawCircle(canvas, center_x, center_y, x, y, scale);
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    drawCircle(canvas, center_x, center_y, x, y, scale);
  }
  return 1;
}

void engine_draw_disk(Canvas *canvas) {
  _engine_draw_disk(canvas, canvas->args[0], canvas->args[1], canvas->args[2],
                    canvas->args[3]);
}
int _engine_draw_disk(Canvas *canvas, int center_x, int center_y, int radius,
                      int scale) {
  for (int x = center_x - radius; x < center_x + radius; ++x) {
    for (int y = center_y - radius; y < center_y + radius; ++y) {
      int dx = center_x - x; // horizontal offset
      int dy = center_y - y; // vertical offset
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        // set pixel color
        _engine_draw_point(canvas, x, y, scale);
      }
    }
  }

  return 1;
}