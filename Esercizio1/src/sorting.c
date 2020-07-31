#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/sorting.h"
#include <assert.h>
#include <errno.h>

/*
  Function that taken an array and two indexes,
  swaps the two positions of the array.
*/
void swap(void **v, int i, int j)
{
    void *tmp;
    tmp=v[i];
    v[i]=v[j];
    v[j]=tmp;
}

/*
  Insert sort implementation.
*/

void insert_sort(void **vet, CMPFUNC compare, int size)
{
  int j;
  for(int i = 1; i<size; i++)
  {
    void* key = vet[i];
    j = i-1;
    while (j>=0 && (compare(vet[j], key)>0))
    {
      vet[j+1] = vet[j];
      j--;
    }
    vet[j+1] = key;
  }
}

/*
  3 indices l, r, u (left, right, upper bound) with the following invariant
  low <= l <= r <= u <= high

  elements in [low, l) are smaller than pivot
  elements in [l, r) equal
  elements in [r, u] are not examined yet
  elements in (u, high] are greater than pivot
*/

void partition (void **arr, CMPFUNC compare, int low, int high, int *l, int *r)
{
  void *pivot = arr[high];
  *l = low;
  *r = low;
  int u = high;
  while(*r <= u)
  {
    if(compare(arr[(*r)], pivot)<0)
    {
      swap(arr, *l, *r);
      (*l)++;
      (*r)++;
    }
    else if(compare(arr[(*r)], pivot)>0)
    {
      swap(arr, *r, u);
      u--;
    }
    else
    {
      (*r)++;
    }
  }
}

void quick_sort(void **arr, CMPFUNC compare, int low, int high)
{
    if (low < high)
    {
        int i, j;
        int l;
        int r;
        partition(arr, compare, low, high, &l, &r);
        quick_sort(arr, compare, low, l-1);
        quick_sort(arr, compare, r, high);
    }
}
