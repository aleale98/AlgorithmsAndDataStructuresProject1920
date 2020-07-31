#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../headers/sorting.h"

#define LENGTH 20000000
#define MAX_BUF_LEN 1024

void **load_data(char *f)
{
  void** r = (void**)malloc(sizeof(record)*LENGTH);
  printf("Array created\n");
  int ID;
  char f2[1024];
  int f3;
  double f4;
  int elements=0;
  FILE* file = fopen(f, "r");
  printf("Loading records\n");
  if (!file) {
        printf("Can't open file\n");

        return 0;
    }
    time_t start = time(0);
    int i = 0;
    while(!feof(file) && i < LENGTH){
      record* rec = (record*) malloc(sizeof(record));
      int n = fscanf(file, "%d,%[^,],%d,%lf", &ID, f2, &f3, &f4);
      if(n != 4) {
            if(feof(file)) {
                continue;
            }
            printf("Error while reading file at line %d", elements);
            exit(5);
        }
      rec -> ID = ID;
      rec -> field2 = strdup(f2);
      rec -> field3 = f3;
      rec -> field4 = f4;
      r[elements] = rec;
      elements++;
      i++;
    }
    fclose(file);
    printf("File loaded. Closing file\n");
    time_t end = time(0);
    printf("%f", difftime(end, start));
    return r;
}
