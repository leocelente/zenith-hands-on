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

int engine_init(Data *data) {
  data->drawing = NULL;
  data->height = 0;
  data->width = 0;
  return 1;
}
/**
 * @brief creates file
 *
 * @param args [width, height]
 * @return int
 */
int engine_create(Data *data) {
  data->width = data->args[0];
  data->height = data->args[1];
  size_t sz = sizeof(int) * data->width * data->height;
  data->drawing = malloc(sz);
  if (data->drawing == NULL) {
    printf("malloc failed : drawing");
    return 0;
  }
  for (size_t i = 0; i < sz; ++i) {
    // fills with white
    data->drawing[i] = 255;
  }
  printf("\tCreated\n");
  return 1;
}
/**
 * @brief saves file
 *
 * @param data
 * @param args [char* filename]
 * @return int
 */
int engine_save(Data *data) {
  char *filename = "test.pgm";
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
  fprintf(file_handler, "%d %d\n", data->height, data->width);
  // write scale
  fprintf(file_handler, "%d\n", UINT8_MAX);

  // write file contents
  for (size_t i = 0; i < data->height; ++i) {
    for (size_t j = 0; j < data->width; ++j) {
      fprintf(file_handler, " %d ", (data->drawing[i * data->width + j]));
    }
    fprintf(file_handler, "\n");
  }
  fclose(file_handler);
  return 1;
}

int engine_close(Data *data) {
  free(data->drawing);
  return 0;
}

int engine_draw_point(Data *data, int x, int y, int scale) {
  if (x <= data->width && y <= data->height) {
    if (scale >= UINT8_MAX)
      scale = 255;
    if (scale <= 0)
      scale = 0;
    data->drawing[y * data->height + x] = scale;
    return 1;
  } else {
    printf("\tOut of bounds\n");
    return 0;
  }
}

int engine_draw_line(Data *data, int x0, int y0, int x1, int y1, int scale) {
  printf("drawing line");
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
    engine_draw_point(data, x, y, scale);
  }
  if (dx == 0) {
    for (int y = begin_y; y <= end_y; ++y) {
      engine_draw_point(data, begin_x, y, scale);
    }
  }
  printf("\n");
  return 1;
}

int engine_draw_rectangle(Data *data, int x0, int y0, int width, int height,
                          int scale) {
  if (x0 + width > data->width)
    width = data->width - x0;
  if (y0 + height > data->height)
    height = data->height - y0;
  engine_draw_line(data, x0, y0, x0 + width, y0, scale);
  engine_draw_line(data, x0, y0, x0, y0 + height, scale);
  engine_draw_line(data, x0 + width, y0, x0 + width, y0 + height, scale);
  engine_draw_line(data, x0, y0 + height, x0 + width, y0 + height, scale);

  return 1;
}

void drawCircle(Data *data, int xc, int yc, int x, int y, int scale) {
  engine_draw_point(data, xc + x, yc + y, scale);
  engine_draw_point(data, xc - x, yc + y, scale);
  engine_draw_point(data, xc + x, yc - y, scale);
  engine_draw_point(data, xc - x, yc - y, scale);
  engine_draw_point(data, xc + y, yc + x, scale);
  engine_draw_point(data, xc - y, yc + x, scale);
  engine_draw_point(data, xc + y, yc - x, scale);
  engine_draw_point(data, xc - y, yc - x, scale);
}
int engine_draw_circle(Data *data, int center_x, int center_y, int radius,
                       int scale) {
  int x = 0, y = radius;
  int d = 3 - 2 * radius;
  drawCircle(data, center_x, center_y, x, y, scale);
  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    drawCircle(data, center_x, center_y, x, y, scale);
  }
}
