#ifndef ERROR_H
#define ERROR_H


#include <sys/file.h>
#include <stdio.h>

#define printError(...)			\
  flock(2,LOCK_EX);				\
  fprintf(stderr,"\e[38;5;1m");			\
  fprintf(stderr,__VA_ARGS__);			\
  fprintf(stderr,"\e[0m\n");			\
  flock(2,LOCK_UN);

#endif
