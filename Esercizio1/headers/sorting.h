#pragma once

typedef int (*CMPFUNC)(const void *, const void*);

typedef struct _record {
	int ID;
	char *field2;
	int field3;
	double field4;
}record;

/*
Return the index of the minimum element
*/
int min_search(void **vet, CMPFUNC, int i, int j);

/*
  Implements insert sort
*/
void insert_sort(void **vet, CMPFUNC, int size);

/*
  Implements quick sort
*/
void quick_sort(void **vet, CMPFUNC, int p, int r);

void partition (void **arr, CMPFUNC compare, int low, int high, int *l, int *r);
