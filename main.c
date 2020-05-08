/**
 * @file main.c
 * @author Leonardo Celente (@leocelente)
 * @brief Creates PGM images based on a set of commands
 * @version 0.1
 * @date 2020-04-28
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "engine.h"
#include "interface.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

  // begin interface
  if (interface_init() != INTERFACE_OK) {
    // handle error
  } else
    LOGD("init_interface", 1);

  // begin engine
    Canvas canvas;
    engine_init(&canvas);


  int is_done = 0;
  while (!is_done) {
    int command = interface_tick(&canvas);
    switch (command) {
    case EXIT:
      is_done = 1;
      printf("\tExiting...\n");
      break;
    case ERROR:
      printf("\tUnknown command... try again\n");
    case CREATE:
      printf("Resolution: %d x %d", canvas.args[0],canvas.args[1]);
      engine_create(&canvas);
      break;
    case EXPORT:
      engine_save(&canvas);
      break;
    case POINT:
        engine_draw_point(&canvas);
      break;
    case LINE:
      engine_draw_line(&canvas);
      break;
    case RECT:
      engine_draw_rectangle(&canvas);
      break;
    case CIRCLE:
      engine_draw_circle(&canvas);
      break;
      case DISK:
      engine_draw_disk(&canvas);
    }
  }
  engine_close(&canvas);
  //  close
  return 0;
}
