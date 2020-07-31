#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Resources/C/Unity/unity.h"
#include "../headers/sorting.h"
#include <assert.h>

#define SIZE 6

static int* new_int(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;
    return result;
}

static double* new_double(double n) {
    double* result = (double*) malloc(sizeof(double*));
    *result = n;
    return result;
}

static char* new_string(char* s)
{
  char *result = (char*)malloc(sizeof(char*));
  strcpy(result, s);
  return result;
}

int cmp_int(const int *a, const int *b)
{
    return (*a)-(*b);
}


 int cmp_double(double *a, double *b)
{
  if((*a)>(*b))
    return 1;
  else if((*a)==(*b))
    return 0;
  else
    return -1;
}

int cmpstring (char *a, char *b ) {
    return strcmp(a, b);
}

static void** create_int_array()
{
  void **vet = malloc(SIZE * sizeof(int*));
  vet[0] = new_int(1);
  vet[1] = new_int(11);
  vet[2] = new_int(21);
  vet[3] = new_int(5);
  vet[4] = new_int(28);
  vet[5] = new_int(0);
  return vet;
}

static void **create_double_array()
{
  void **vet = malloc(SIZE * sizeof(float*));
  vet[0] = new_double(1.5);
  vet[1] = new_double(2.7);
  vet[2] = new_double(.5);
  vet[3] = new_double(1.4);
  vet[4] = new_double(9.0);
  vet[5] = new_double(11.0);
  return vet;
}

static void **create_string_array()
{
  void **vet = (void**)malloc(SIZE * sizeof(char*));
  vet[0] = new_string("ciao");
  vet[1] = new_string("a");
  vet[2] = new_string("zaino");
  vet[3] = new_string("a");
  vet[4] = new_string("quick");
  vet[5] = new_string("cico");
  return vet;
}


static void free_array_space(void **vet, int size)
{
  for(int i = 0; i < size; i++)
  {
    free(vet[i]);
  }
  free(vet);
}

static void run_quick_sort_on_int()
{
	void **vet = create_int_array();
  int ordered_vet[] = {0, 1, 5, 11, 21, 28};
  quick_sort(vet, (CMPFUNC)cmp_int, 0, SIZE-1);
  for(int i = 0; i < SIZE; i++)
  {
    TEST_ASSERT_EQUAL(ordered_vet[i], *(int*)vet[i]);
  }
  free_array_space(vet, SIZE);
}

static void run_insert_sort_on_int()
{
  void **vet = create_int_array();
  int ordered_vet[] = {0, 1, 5, 11, 21, 28};
  insert_sort(vet, (CMPFUNC)cmp_int, SIZE);
  for(int i = 0; i < SIZE; i++)
  {
    TEST_ASSERT_EQUAL(ordered_vet[i], *(int*)vet[i]);
  }
  free_array_space(vet, SIZE);
}

static void run_quick_sort_on_double()
{
  void **vet = create_double_array();
  double ordered_vet[] = {.5, 1.4, 1.5, 2.7, 9.0, 11.0};
  quick_sort(vet, (CMPFUNC)cmp_double, 0, SIZE-1);
  for(int i = 0; i < SIZE; i++)
  {
    TEST_ASSERT_EQUAL(ordered_vet[i], *(double*)vet[i]);
  }
  free_array_space(vet, SIZE);
}

static void run_insert_sort_on_double()
{
  void **vet = create_double_array();
  double ordered_vet[] = {.5, 1.4, 1.5, 2.7, 9.0, 11.0};
  insert_sort(vet, (CMPFUNC)cmp_double, SIZE);
  for(int i = 0; i < SIZE; i++)
  {
    TEST_ASSERT_EQUAL(ordered_vet[i], *(double*)vet[i]);
  }
  free_array_space(vet, SIZE);
}

static void run_quick_sort_on_string()
{
  void **vet = create_string_array();
  const char *a[SIZE];
  a[0] = "a";
  a[1] = "a";
  a[2] = "ciao";
  a[3] = "cico";
  a[4] = "quick";
  a[5] = "zaino";
  quick_sort(vet, (CMPFUNC)cmpstring, 0, SIZE-1);
  for(int i = 0; i < SIZE; i++)
  {
    TEST_ASSERT_EQUAL(*(a[i]), *(char*)vet[i]);
  }
  free_array_space(vet, SIZE);
}

static void run_insert_sort_on_string()
{
  void **vet = create_string_array();
  const char *a[SIZE];
  a[0] = "a";
  a[1] = "a";
  a[2] = "ciao";
  a[3] = "cico";
  a[4] = "quick";
  a[5] = "zaino";
  insert_sort(vet, (CMPFUNC)cmpstring, SIZE);
  for(int i = 0; i < SIZE; i++)
  {
    TEST_ASSERT_EQUAL(*(a[i]), *(char*)vet[i]);
  }
  free_array_space(vet, SIZE);
}

static void run_quick_sort_on_null()
{
  void **vet = NULL;
  quick_sort(vet, (CMPFUNC)cmp_int, 0, 0);
  TEST_ASSERT_NULL(vet);
}

int main(int argc, char const *argv[]) {

  UNITY_BEGIN();
  RUN_TEST(run_quick_sort_on_int);
  RUN_TEST(run_insert_sort_on_int);
  RUN_TEST(run_quick_sort_on_double);
  RUN_TEST(run_insert_sort_on_double);
  RUN_TEST(run_quick_sort_on_string);
  RUN_TEST(run_insert_sort_on_string);
  RUN_TEST(run_quick_sort_on_null);
  //RUN_TEST(dumb_test);
  UNITY_END();
  return 0;
}
