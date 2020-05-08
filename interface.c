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
#include "constants.h"
#include "engine.h"
#include "slre.h"
#include <regex.h>
#include <stdio.h>

int interface_init() { return INTERFACE_OK; }
static int compile_regex(regex_t *r, const char *regex_text) {
  int status = regcomp(r, regex_text, REG_EXTENDED | REG_NEWLINE);
  if (status != 0) {
    char error_message[100];
    regerror(status, r, error_message, 100);
    printf("Regex error compiling '%s': %s\n", regex_text, error_message);
    return 1;
  }
  return 0;
}

static int match_regex(regex_t *r, const char *to_match) {
  /* "P" is a pointer into the string which points to the end of the
     previous match. */
  const char *p = to_match;
  /* "N_matches" is the maximum number of matches allowed. */
  const int n_matches = 1;
  /* "M" contains the matches found. */
  regmatch_t m[n_matches];

  int nomatch = regexec(r, p, n_matches, m, 0);
  if (nomatch) {
    // printf("No  matches.\n");
    return 0;
  } else
    return 1;

  return 0;
}
int interface_tick(Canvas *canvas) {
  /**
   * @brief I commented the more precise regex because:
   *  1. it fails
   *  2. it seems that the "standard" (GNU C Lib) library in regex.h is actually
   * a POSIX sytax only lib so normal regex (Perl syntax) generates undefined
   * behavior and fails matching. Not very clear.
   *
   * https://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples
   * I also ripped off those helper functions from here:
   * https://www.lemoda.net/c/unix-regex/
   */
  const char *regexs[CMD_COUNT] = {
      "^EXIT",
      "^CREATE", //( ([0-9]+)){2}",
      "^EXPORT", //( ([a-z A-Z]+.(pgm|PGM)))",
      "^POINT",  //( ([0-9]+)){3}",
      "^LINE",   //( ([0-9]+)){5}",
      "^RECT",   //( ([0-9]+)){5}",
      "^CIRCLE", //( ([0-9]+)){4}",
      "^DISK"    //( ([0-9]+)){4}"
  };

  const char *scanstr[CMD_COUNT] = {"%s",
                                    "%s %d %d",
                                    "%s %s",
                                    "%s %d %d %d",
                                    "%s %d %d %d %d %d",
                                    "%s %d %d %d %d %d",
                                    "%s %d %d %d %d",
                                    "%s %d %d %d %d"};
  char cmd[100];
  fgets(cmd, 100, stdin);
  int cmd_ret = ERROR;

  for (size_t i = 0; i < CMD_COUNT; ++i) {
    regex_t regex;
    compile_regex(&regex, regexs[i]);
    if (match_regex(&regex, cmd)) {
      char c[20];
      if (i == EXPORT) {
        sscanf(cmd, scanstr[EXPORT], c, &canvas->filename);
      } else {
        sscanf(cmd, scanstr[i], c, &canvas->args[0], &canvas->args[1],
               &canvas->args[2], &canvas->args[3], &canvas->args[4]);
      }
      cmd_ret = i;
    }
  }
  return cmd_ret;
}
