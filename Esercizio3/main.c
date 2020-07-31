#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doublylinkedlist/headers/doublylinkedlist.h"
#include "hashmap/headers/hashmap.h"
#include "hashfunctions/headers/hashfunc.h"

#define LENGTH 6321078
#define M 1000000

int * getRandom( ) {

   static int  r[10000000];
   /* set the seed */
   srand((unsigned)time(NULL));
   for (int i = 0; i < 10000000; ++i) {
      r[i] = rand() % 10000001;
   }
   return r;
}

static int* new_int(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;
    return result;
}

int cmp_int(const int *a, const int *b)
{
    return (*a)-(*b);
}

int cmp_key(const void *a, const void *b)
{
    printf("ciao\n");
    const node_t *x = (node_t*)a;
    const node_t *y = (node_t*)b;
    return *((int*)(x->key)) - *((int*)(y->key));

}

void print_int(int *val){
  printf("%d\n",*val);
}

hashmap *read_file_and_charge_map(char *f){
  int elements = 0;
  static int keys[LENGTH];
  static int data[LENGTH];
  hashmap *map = create_new_map(M);
  FILE* file = fopen(f, "r");
  if (!file) {
        printf("Can't open file\n");
        return 0;
    }
     int v1;
     int v2;
    while(!feof(file)){
      int n = fscanf(file, "%d,%d", &v1, &v2);
      if(n != 2) {
            if(feof(file)) {
                continue;
            }
            printf("Error while reading file at line %d", elements);
            exit(5);
        }
      keys[elements] = v1;
      data[elements] = v2;
      insert_association(map, &keys[elements], &data[elements],
      (HASHFUNC)hash_with_div_int, (CMPFUNC)cmp_int);
      elements++;
    }
    fclose(file);
    return map;
}
/*
node_t **read_file_and_charge_array(char *f){
  int elements = 0;
  node_t **nodes = (node_t**)malloc(LENGTH * sizeof(node_t*));
  FILE* file = fopen(f, "r");
  printf("Loading records\n");
  if (!file) {
        printf("Can't open file\n");
        return 0;
    }
     int v1;
     int v2;
    while(!feof(file)){
      int n = fscanf(file, "%d,%d", &v1, &v2);
      if(n != 2) {
            if(feof(file)) {
                continue;
            }
            printf("Error while reading file at line %d", elements);
            exit(5);
        }
        node_t *nd = create_node(new_int(v1), new_int(v2));
        nodes[elements] = nd;
        //printf("elements %d\n",elements);
      elements++;
    }
    fclose(file);
    printf("file closed. executing qsrot\n");
    qsort(nodes, 6321078, sizeof(node_t), (CMPFUNC)cmp_key);
    //printf("\n\n%d",map_size(map));
    return nodes;
}
*/
int main(int argc, char const *argv[]) {
  int *keys;
  time_t start = time(0);
  //node_t **map = read_file_and_charge_array("hashes.csv");
  hashmap *map = read_file_and_charge_map("hashes.csv");
  time_t end = time(0);
  printf("\nTime to charge the map: %lf", difftime(end, start));
  time_t number_gen_start = time(0);
  keys  = getRandom();
  time_t number_gen_end = time(0);
  printf("\nTime to generate numbers: %lf", difftime(number_gen_end, number_gen_start));
  printf("\nStart to extract 10000000 numbers from the map\n");
  int retrieved_elements = 0;
  time_t number_extr_start = time(0);
  for(int i = 0; i < 10000000; i++){
    void *retrieved_key = retrieve_value(map, new_int(keys[i]),
    (HASHFUNC)hash_with_div_int,
    (CMPFUNC)cmp_int);
    if(retrieved_key != NULL){
      retrieved_elements++;
    }
  }
  time_t number_extr_end = time(0);
  printf("\nTime to extract numbers: %lf", difftime(number_extr_end, number_extr_start));
  printf("\nRetrieved %d elements\n", retrieved_elements);
  return 0;
}
