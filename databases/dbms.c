#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 64000
#define MAX_RECORD_SIZE 1500
#define MAX_INPUT 100

char table[MAX_RECORDS][MAX_RECORD_SIZE];

void loadFile(char *path) {
  printf("loading path: %s\n", path);

  FILE *stream = fopen(path, "rb");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int numRows = 0;
  int bytesLoaded = 0;
  int i = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    bytesLoaded += (int) read;
    strncpy(table[i++], line, MAX_RECORD_SIZE);
    numRows++;
  }
  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  loadFile(argv[1]);

  // GET query from stdin
  char input[MAX_INPUT];
  printf("query: ");
  fgets(input, MAX_INPUT, stdin);

  // PARSE query
  char *column = strtok(input, ":");
  char *searchTerm = strtok(NULL, ":");

  printf("column: %s, searchTerm: %s\n", column, searchTerm);

  char *result;
  for (int i = 0; i < MAX_RECORDS; i++) {
    result = strstr(table[i], searchTerm);
    if (result != NULL) {
      printf("%s\n", result);
    }
  }
}
