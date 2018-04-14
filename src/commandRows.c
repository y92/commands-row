#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "error.h"


int commandRow(int n, const char **comT, const char ***argT) {

  pid_t pid[n];
  int pipes[n-1][2];
  const int nb_pipes = n-1;

  for (int i = 0; i <nb_pipes; i++) {
    if (pipe(pipes[i]) < 0) {
      printError("pipe[%d] %s",i,strerror(errno));
      exit(1);
    }
  }

  for (int i = 0; i<n; i++) {

    if ((pid[i] = fork()) < 0) {
      printError("fork[%d] %s",i,strerror(errno));
      exit(1);
    }

    else if (pid[i] == 0) {

      for (int j=0; j < nb_pipes; j++) {
	if (j == i-1) continue;
	close(pipes[j][0]);
      }

      for (int j=0; j < nb_pipes; j++) {
	if (j == i) continue;
	close(pipes[j][1]);
      }

      if (i < nb_pipes) {
	if (dup2(pipes[i][1], 1) < 0) {
	  printError("dup2[%d](1): %s",i,strerror(errno));
	  exit(3);
	}
      }

      if (i > 0) {
	if (dup2(pipes[i-1][0],0) <0) {
	  printError("dup2[%d](1): %s",i,strerror(errno));
	  exit(3);
	}
      }

      if (argT[i]) {
	execvp(comT[i], argT[i]);
      }
      execlp(comT[i], comT[i], NULL);
      printError("exec[%d] Cannot execute %s: %s",i,comT[i],strerror(errno));
      exit(2);
    }


    else {
      if (i > 0) close(pipes[i-1][0]);
      if (i < nb_pipes) close(pipes[i][1]);
    }
  }

  for (int i=0; i<n; i++) wait(NULL);

  return 0;
}


