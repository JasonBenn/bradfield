#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 64000
#define MAX_RECORD_SIZE 1500
#define MAX_INPUT 100

char table[MAX_RECORDS][MAX_RECORD_SIZE];
int numRows = 0;

void loadFile(char *path) {
  printf("loading path: %s\n", path);

  FILE *stream = fopen(path, "rb");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int bytesLoaded = 0;
  int i = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    bytesLoaded += (int) read;
    strncpy(table[i++], line, MAX_RECORD_SIZE);
    numRows++;
  }
  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}

void chomp(char *str) {
  int end = strlen(str) - 1;
  if (str[end] == '\n' || str[end] == '\r')
    str[end] = '\0';
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
  char *value = strtok(NULL, ":");
  chomp(value);

  char *result;
  int resultsCount = 0;
  for (int i = 0; i < numRows; i++) {
    result = strstr(table[i], value);
    if (result != NULL) {
      printf("%s\n", result);
      resultsCount++;
    }
  }
  printf("%i/%i results\n", resultsCount, numRows);
}
