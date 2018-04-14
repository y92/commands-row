#include "commandRows.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  /* If no commands are passed, the program must exit immediately */
  if (argc == 1) exit(0);
  
  /* Separator ";" cannot be at the beginning or at the end of the line */
  if (strcmp(argv[1],";") == 0 || strcmp(argv[argc-1],";") ==0) {
    printError("Bad commands row");
    return 1;
  }

  /* Separator ";" cannot be followed by another one */
  for (int i = 1; i< argc-2; i++) {
    if (strcmp(argv[i],";") == 0 && strcmp(argv[i+1],";") == 0) {
      printError("Bad commands row");
      return 1;
    }
  }
  
  int nbCommands = 1;
  
  for (int i = 1; i< argc; i++) {
    if (strcmp(argv[i],";") == 0) {
      nbCommands++;
    }
  }

  int nbArgs[nbCommands];
  int indexCom[nbCommands];
  indexCom[0] = 1;
  
  for(int i=0; i< nbCommands; i++) nbArgs[i] = 0;
  
  int i =0, j, k = 1;
  while (i < nbCommands) {
    for (j= k+1; j<argc; j++) {
      if (strcmp(argv[j],";") == 0) { i++; indexCom[i] = (k = j+1); break; }
      nbArgs[i]++;
    }
    if (j == argc) break;
  }
  
  const char **comT = calloc(nbCommands, sizeof(char *));
  comT[0] = argv[1];
  k=1;
  
  for (int i=2; i< argc-1; i++) {
    if (strcmp(argv[i],";") == 0) {
      comT[k] = argv[i+1];
      k++;
    }
  }

  
  const char ***argT = calloc(nbCommands, sizeof(char **));
  for (int i =0; i < nbCommands; i++) {
    argT[i] = calloc(1+nbArgs[i], sizeof(char *));
    argT[i][0] = comT[i];
    for (int j=1; j< 1+nbArgs[i]; j++) {
      argT[i][j] = argv[indexCom[i]+1+(j-1)];
    }
  }

  int res = commandRow(nbCommands, comT, argT);

  
  free(comT);
  for (int i=0; i<nbCommands; i++) {
    free(argT[i]);
  }
  free(argT);
  
  return res;
}
