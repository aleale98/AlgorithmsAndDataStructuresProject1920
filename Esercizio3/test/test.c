#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../doublylinkedlist/headers/doublylinkedlist.h"
#include "../hashmap/headers/hashmap.h"
#include "../hashfunctions/headers/hashfunc.h"
#include "../../Resources/C/Unity/unity.h"

#define SIZE 3
/*
  Auxiliary functions needed for the insert, deletion and search operations.
  Including comparison functions, print functions and hash functions.
  Tests will be ran on integers number. The same tests can be ran on other
  values making a few changes.
*/

/*
Comparison functions for integer numbers. Needed since struct nodes is
composed of void pointers that has to be casted then.
*/
int cmp_int(const int *a, const int *b)
{
    return (*a)-(*b);
}

/*
 Function that print the content of the pointer.
*/
void print_int(int *val){
  printf("%d\n",*val);
}

/*
  Function to return the pointer to an integer number
*/
static int* new_int(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;
    return result;
}

overflow_list *create_test_list(){
  overflow_list *l = create_empty_doubly_linked_list();
  insert_item(l, new_int(1), new_int(1), (CMPFUNC)cmp_int);
  insert_item(l, new_int(2), new_int(2), (CMPFUNC)cmp_int);
  insert_item(l, new_int(3), new_int(3), (CMPFUNC)cmp_int);
  return l;
}

hashmap *create_test_map(){
  hashmap *map = create_new_map(SIZE);
  insert_association(map, new_int(0), new_int(0), (HASHFUNC)hash_with_div_int,(CMPFUNC)cmp_int);
  insert_association(map, new_int(1), new_int(1), (HASHFUNC)hash_with_div_int,(CMPFUNC)cmp_int);
  insert_association(map, new_int(2), new_int(2), (HASHFUNC)hash_with_div_int,(CMPFUNC)cmp_int);
  insert_association(map, new_int(3), new_int(3), (HASHFUNC)hash_with_div_int,(CMPFUNC)cmp_int);
  return map;
}

/*
Unit testing for doubly linked lists
*/
//------------------- START TESTING ON LISTS -------------------------------

void test_create_empty_list(){
  overflow_list *l = create_empty_doubly_linked_list();
  TEST_ASSERT_EQUAL(NULL, l->head);
  TEST_ASSERT_EQUAL(NULL, l->tail);
  free_list(l->head);
}

void test_insert(){
  overflow_list *l = create_test_list();
  int *expected_keys[] = {new_int(1), new_int(2), new_int(3)};
  int *expected_data[] = {new_int(1), new_int(2), new_int(3)};
  node_t *node = l->head;
  int i = 0;
  while(node != NULL){
    TEST_ASSERT_EQUAL(0, cmp_int(expected_keys[i], node->key));
    TEST_ASSERT_EQUAL(0, cmp_int(expected_data[i], node->data));
    node = node->next;
    i++;
  }
  free(node);
  free_list(l->head);
}

void test_remove_from_beg(){
  overflow_list *l = create_test_list();
  int *expected_keys[] = {new_int(2), new_int(3)};
  int *expected_data[] = {new_int(2), new_int(3)};
  remove_from_beg(l);
  node_t *node = l->head;
  int i = 0;
  while(node != NULL){
    TEST_ASSERT_EQUAL(0, cmp_int(expected_keys[i], node->key));
    TEST_ASSERT_EQUAL(0, cmp_int(expected_data[i], node->data));
    node = node->next;
    i++;
  }
  free(node);
  free_list(l->head);
}

void test_remove_from_end(){
  overflow_list *l = create_test_list();
  int *expected_keys[] = {new_int(1), new_int(2)};
  int *expected_data[] = {new_int(1), new_int(2)};
  remove_from_end(l);
  node_t *node = l->head;
  int i = 0;
  while(node != NULL){
    TEST_ASSERT_EQUAL(0, cmp_int(expected_keys[i], node->key));
    TEST_ASSERT_EQUAL(0, cmp_int(expected_data[i], node->data));
    node = node->next;
    i++;
  }
  free(node);
  free_list(l->head);
}

void test_remove(){
  overflow_list *l = create_test_list();
  int *expected_keys[] = {new_int(1), new_int(3)};
  int *expected_data[] = {new_int(1), new_int(3)};
  remove_item(l, new_int(2), (CMPFUNC)cmp_int);
  node_t *node = l->head;
  int i = 0;
  while(node != NULL){
    TEST_ASSERT_EQUAL(0, cmp_int(expected_keys[i], node->key));
    TEST_ASSERT_EQUAL(0, cmp_int(expected_data[i], node->data));
    node = node->next;
    i++;
  }
  free(node);
  free_list(l->head);
}

void test_contains_key_success(){
  overflow_list *l = create_test_list();
  TEST_ASSERT(contains_key(l->head, new_int(2), (CMPFUNC)cmp_int) != NULL);
  free_list(l->head);
}

void test_contains_key_fail(){
  overflow_list *l = create_test_list();
  TEST_ASSERT_EQUAL(contains_key(l->head, new_int(7), (CMPFUNC)cmp_int), NULL);
  free_list(l->head);
}

void test_empty(){
  overflow_list *l = create_test_list();
  TEST_ASSERT_EQUAL(0, empty(l));
  free_list(l->head);
}

void test_size(){
  overflow_list *l = create_test_list();
  TEST_ASSERT_EQUAL(3, size(l));
  free_list(l->head);
}

void test_remove_all(){
  overflow_list *l = create_test_list();
  remove_all(l);
  TEST_ASSERT_EQUAL(0, size(l));
  free_list(l->head);
}

//------------------- END TESTING ON LISTS -------------------------------

//------------------- START TESTING ON HASHMAP ---------------------------
void test_create_map(){
  hashmap *map = create_new_map(SIZE);
  TEST_ASSERT_EQUAL(SIZE, map->size);
  for(int i = 0; i < map->size; i++){
    TEST_ASSERT_EQUAL(1, empty(map->items[i]));
  }
  free_map(map);
}

void test_is_empty_map(){
  hashmap *map = create_new_map(SIZE);
  TEST_ASSERT_EQUAL(1, is_empty(map));
  free_map(map);
}

void test_insert_map(){
  hashmap *map = create_new_map(SIZE);
  insert_association(map, new_int(1), new_int(1), (HASHFUNC)hash_with_div_int,
     (CMPFUNC)cmp_int);
  int index = hash_with_div_int(new_int(1), SIZE);
  TEST_ASSERT(contains_key(map->items[index]->head, new_int(1), (CMPFUNC)cmp_int) != NULL);
  free_map(map);
}

void test_size_map(){
  hashmap *map = create_test_map();
  TEST_ASSERT_EQUAL(4, map_size(map));
  free_map(map);
}

void test_remove_all_association(){
  hashmap *map = create_test_map();
  remove_all_association(map);
  TEST_ASSERT_EQUAL(0, map_size(map));
  free_map(map);
}

void test_is_present_success(){
  hashmap *map = create_test_map();
  TEST_ASSERT_EQUAL(1, is_present(map, new_int(1), (HASHFUNC)hash_with_div_int,
    (CMPFUNC)cmp_int));
  free_map(map);
}

void test_is_present_fail(){
  hashmap *map = create_test_map();
  TEST_ASSERT_EQUAL(0, is_present(map, new_int(7), (HASHFUNC)hash_with_div_int,
    (CMPFUNC)cmp_int));
  free_map(map);
}

void test_retrieve_value(){
  hashmap *map = create_test_map();
  TEST_ASSERT(retrieve_value(map, new_int(2), (HASHFUNC)hash_with_div_int, (CMPFUNC)cmp_int) != NULL);
  free_map(map);
}
//------------------- END TESTING ON HASHMAP ---------------------------

int main(int argc, char const *argv[]) {
  UNITY_BEGIN();
  //--------- TESTS ON LIST ---------
  RUN_TEST(test_create_empty_list);
  RUN_TEST(test_insert);
  RUN_TEST(test_remove_from_beg);
  RUN_TEST(test_remove_from_end);
  RUN_TEST(test_remove);
  RUN_TEST(test_contains_key_success);
  RUN_TEST(test_contains_key_fail);
  RUN_TEST(test_empty);
  RUN_TEST(test_size);
  RUN_TEST(test_remove_all);
  //--------- TESTS ON LIST ---------

  //--------- TESTS ON HASHMAP ---------
  RUN_TEST(test_create_map);
  RUN_TEST(test_is_empty_map);
  RUN_TEST(test_insert_map);
  RUN_TEST(test_size_map);
  RUN_TEST(test_remove_all_association);
  RUN_TEST(test_is_present_success);
  RUN_TEST(test_is_present_fail);
  RUN_TEST(test_retrieve_value);
  UNITY_END();
  return 0;
}
