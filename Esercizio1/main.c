
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include "headers/utility.h"
#include "headers/sorting.h"

#define LENGTH 20000000

int cmp_int(const record *a, const record *b)
{
    return (a->field3)-(b->field3);
}

int cmp_double(const void *f, const void *s)
{
  record *a = (record*)f;
  record *b = (record*)s;
  if((a->field4)>(b->field4))
    return 1;
  else if((a->field4)<(b->field4))
    return -1;
  else
    return 0;
}

int cmp_string (const void * f, const void * s ) {
    record *a = (record*)f;
    record *b = (record*)s;
    //printf("%s %s", a->field2, b->field2);
    return strcmp(a->field2, b->field2);
}

void free_data(void **v, int size)
{
  for(int i = 0; i<size; i++)
  {
    free(v[i]);
  }
  free(v);
}

int ordered(CMPFUNC compare, void **v, int size)
{
  int ord = -1;
  int i = 0;
  for(i = 0; i < size-2; i++)
  {
    ord = compare(v[i], v[i+1]);
    if(ord > 0)
    {
      printf("Exiting at round %d\n",i);
      return i;
    }
  }
  if(ord>0)
    return i;
  return ord;
}

void quick_sort_int(void **v, int size)
{
  void **temp = (void **)malloc(sizeof(record)*size);
  memcpy(&temp, &v, sizeof(v));
  time_t start = time(0);
  printf("inizio ad ordinare int\n");
  quick_sort(temp, (CMPFUNC)cmp_int, 0, size-1);
  time_t end = time(0);
  printf("Tempo impiegato per ordinare int %f \n", difftime(end, start));
  printf("Sorted %d\n", ordered((CMPFUNC)cmp_int, temp, size));
}

void quick_sort_double(void **v, int size)
{
  void **temp = (void **)malloc(sizeof(record)*size);
  memcpy(&temp, &v, sizeof(v));
  time_t start = time(0);
  printf("inizio ad ordinare float\n");
  quick_sort(temp, (CMPFUNC)cmp_double, 0, size-1);
  time_t end = time(0);
  printf("Tempo impiegato per ordinare float %f \n", difftime(end, start));
  printf("Sorted: %d\n", ordered((CMPFUNC)cmp_double, temp, size));
}

void quick_sort_string(void **v, int size)
{
  void **temp = (void **)malloc(sizeof(record)*size);
  memcpy(&temp, &v, sizeof(v));
  printf("Inizio ad ordinare string\n");
  time_t start = time(0);
  quick_sort(temp, (CMPFUNC)cmp_string, 0, size-1);
  time_t end = time(0);
  printf("Tempo impiegato per ordinare string %f \n", difftime(end, start));
  printf("Sorted: %d\n", ordered((CMPFUNC)cmp_string, temp, size));
}

int main(int argc, char *argv[])
{
    void** r = (void**)malloc(sizeof(record)*LENGTH);
    r = load_data("records.csv");
    printf("\nInizio ordinamento\n");
    quick_sort_int(r, LENGTH);
    quick_sort_string(r, LENGTH);
    quick_sort_double(r, LENGTH);
    insert_sort(r, (CMPFUNC)cmp_int, 10000);
    return 0;
}
