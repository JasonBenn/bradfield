#include <stdio.h>
#include <stdlib.h>
#define MAX_RECORD_SIZE 1200 // a "long" row appears to be ~1062 chars

char *loadFile(char *path) {
  printf("loading path: %s\n", path);
  FILE *f = fopen(path, "rb");
  char *table = malloc(1000000000); // TODO: 1 gig currently.

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  //same as rewind(f);

  fread(table, fsize, 1, f);
  fclose(f);

  table[fsize] = '0';

  return table;
  // DECLARE byte currently scanned
  // WHILE file at byte is not EOF
    // fseek MAX_RECORD_SIZE?
    // rewind back to newline char?
    // malloc length of record?
    //

  // malloc numRecords * MAX_RECORD_SIZE
  // put each line into a row in an array
  // return array
}

// IDENTIFY files from file glob passed in on argv1
int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  char *table = loadFile(argv[1]);
  for (int i = 0; i < 10; i++) {
    printf("%c", table[i]);
  }
  printf("\n");
}

// FIRST file
  // IDENTIFY structure of record

// EACH file
  // LOAD into memory, laid out as rows # TODO: also lay out as columns?

// WAIT for query on STDIN

// WITH query
  // EXTRACT $column, $value FROM "SELECT * WHERE $column = $value"

// EACH row
  // IF match
    // PRINT match
