/**
 * @file interface.h
 * @author Leonardo Celente (@leocelente)
 * @brief  Supporting library to manage the terminal interface
 * @version 0.1
 * @date 2020-04-28
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "interface.h"
#include <stdio.h>
#include <string.h>
int interface_init() { return INTERFACE_OK; }

int interface_tick(int *args) {
  char cmd[100];
  scanf("%s", cmd);
  if (!strcmp("EXPORT", cmd)) {
    return EXPORT;
  } else if (!strcmp("CREATE", cmd)) {
    return CREATE;
  } else if (!strcmp("LINE", cmd)) {
    return LINE;
  } else if (!strcmp("POINT", cmd)) {
    return POINT;
  } else if (!strcmp("RECT", cmd)) {
    return RECT;
  } else if (!strcmp("EXIT", cmd)) {
    return EXIT;
  } else if (!strcmp("CIRCLE", cmd)) {
    return CIRCLE;
  }else {
    return ERROR;
  }
}
