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
    Data data;
    engine_init(&data);


  int is_done = 0;
  while (!is_done) {
    int command = interface_tick(data.args);
    switch (command) {
    case EXIT:
      is_done = 1;
      printf("\tExiting...\n");
      break;
    case ERROR:
      printf("\tNot a valid command");
    case CREATE:
      data.args[0] = 120;
      data.args[1] = 140;
      engine_create(&data);
      break;
    case EXPORT:
      engine_save(&data);
      break;
    case POINT:
        engine_draw_point(&data, data.width/2, data.height/2, 122);
        engine_draw_point(&data, 0, 0, 180);
      break;
    case LINE:
      engine_draw_line(&data, 1,1, 50,50, 1);
      break;
    case RECT:
      engine_draw_rectangle(&data, 1,1, 50,50, 50);
      break;
    case CIRCLE:
      engine_draw_circle(&data, 120, 140, 10, 80);
    }
  }
  engine_close(&data);
  //  close
  return 0;
}
