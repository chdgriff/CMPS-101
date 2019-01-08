// Lex.c - Takes lines from a command line file and outputs a file sorted
// Chris Griffis <chdgriff>
// pa2

#include "List.h"
#include <stdlib.h>
#include <string.h>

#define FILE_LEN 100
#define CHAR_LEN 60

int main(int argc, char* argv[]) {
  FILE *in, *out;
  char buffer[CHAR_LEN];
  char **lines;
  int lineCount;

  List L;
  int inserted, fileLength;

  if (argc != 3) {
    printf("Usage Lex.c: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if ( in == NULL) {
    printf("Lex.c Error: unable to open %s for reading\n", argv[1]);
    exit(1);
  }
  if (out == NULL) {
    printf("Lex.c Error: unable to open file %s for writing\n", argv[2]);
    exit(1);
  }


  fileLength = FILE_LEN;
  lines = malloc(fileLength * sizeof(char *)); // mallocs array for pointers to each line
  lineCount = 0;
  while (fgets(buffer, CHAR_LEN, in) != NULL) {
    if (lineCount == fileLength) { // if array is full realloc by 2 times size
      fileLength *= 2;
      lines = realloc(lines, fileLength * sizeof(char *));
    }
    lines[lineCount] = malloc(CHAR_LEN * sizeof(char)); // Mallocs space for line
    strcpy(lines[lineCount++], buffer); // copies string into array
  }

  L = newList();
  for (int i = 0; i < lineCount; i++) { // Loops through each line in array
    inserted = 0;
    while (inserted == 0) {
      if (length(L) == 0) { // if empty List
        prepend(L, 0);
        inserted = 1;
        moveFront(L);
      }
      else if (strcmp(lines[i], lines[get(L)]) < 0) { // If less than cursor
        if (index(L) == 0) { // If cursor is at front
          prepend(L, i);
          inserted = 1;
        }
        else { // If cursor is in the middle
          movePrev(L);
          if (strcmp(lines[i], lines[get(L)]) > 0) { // If greater than new cursor
            insertAfter(L, i);
            inserted = 1;
          }
        }
      }
      else if (strcmp(lines[i], lines[get(L)]) > 0) { // If greater than cursor
        if (index(L) == length(L)-1) { // If cursor is at back
          append(L, i);
          inserted = 1;
        }
        else { // If greater than new cursor
          moveNext(L);
          if (strcmp(lines[i], lines[get(L)]) < 0) {
            insertBefore(L, i);
            inserted = 1;
          }
        }
      }
      else { // If equal to cursor
        insertBefore(L, i);
        inserted = 1;
      }
    }
  }

  moveFront(L);
  while (index(L) != -1) {
    fprintf(out, "%s", lines[get(L)]);
    moveNext(L);
  }

  for (int i = 0; i < lineCount; i++) free(lines[i]); // frees each line
  free(lines); // frees whole array

  freeList(&L);
  fclose(in);
  fclose(out);
}
