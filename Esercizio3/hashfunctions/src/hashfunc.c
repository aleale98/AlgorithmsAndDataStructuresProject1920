#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/hashfunc.h"

int hash_with_div_int(int *key, int size){
  return *key % size;
}
