#ifndef CONSTANTS_H
#define CONSTANTS_H
/**
 * @file constants.h
 * @author Leonardo Celente (@leocelente)
 * @brief ERRNO and misc constants
 * @version 0.1
 * @date 2020-04-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#define NULL (void *)0
#ifdef DEBUG
#define LOGD(msg, param) printf("[*] %s : %d\n", msg, param);
#else
#define LOGD(msg, param)
#endif
/*
    interface.h
*/

#define MAX_ARG 5

#define INTERFACE_OK 0
#define INTERFACE_BAD -1
enum Commands { ERROR, EXIT, CREATE, EXPORT, POINT, LINE, RECT, CIRCLE };
/*
    engine.h
*/

#endif