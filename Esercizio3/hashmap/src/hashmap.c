#include <stdio.h>
#include <stdlib.h>
#include "../../doublylinkedlist/headers/doublylinkedlist.h"
#include "../headers/hashmap.h"
#include "../../hashfunctions/headers/hashfunc.h"

hashmap *create_new_map(int s){
  hashmap *map = (hashmap*)malloc(sizeof(hashmap));
  map -> items = (overflow_list**)malloc(s*sizeof(overflow_list*));
  for(int i = 0; i < s; i++){
    map -> items[i] = create_empty_doubly_linked_list();
  }
  map -> size = s;
  return map;
}

void free_map(hashmap *map){
  for(int i = 0; i < map->size; i++){
    free_list(map -> items[i] -> head);
  }
  free(map);
}

int is_empty(hashmap *map){
  int e = 1;
  if(map != NULL){
    for(int i = 0; i < map->size && e == 1; i++){
      e = empty(map -> items[i]);
    }
  }
  return e;
}

int map_size(hashmap *map){
  int s = 0;
  for(int i = 0; i < map->size; i++){
    s = s + size(map -> items[i]);
  }
  return s;
}

void remove_all_association(hashmap *map){
  for(int i = 0; i < map->size; i++){
    remove_all(map -> items[i]);
  }
}

int is_present(hashmap *map, void *key, HASHFUNC hashfunc,
  CMPFUNC compare){

  int i = hashfunc(key, map->size);
  return (contains_key(map->items[i]->head, key, compare) != NULL);
}

void insert_association(hashmap *map, void *key, void *val, HASHFUNC hash, CMPFUNC compare){
     int i = hash(key, map->size);
     node_t *list = map -> items[i] -> head;
     if(contains_key(list, key, compare)==NULL)
      insert_item(map->items[i], key, val, (CMPFUNC)compare);
}

void *retrieve_value(hashmap *map, void *key, HASHFUNC hash, CMPFUNC compare){
  int i = hash(key, map->size);
  node_t *retrieved;
  node_t *h = map -> items[i] -> head;
  retrieved = contains_key(h, key, compare);
  return retrieved != NULL ? retrieved -> data : NULL;
}

void delete_association(hashmap *map, void *key, HASHFUNC hash, CMPFUNC compare){
  if(map != NULL){
    int i = hash(key, map->size);
    remove_item(map->items[i], key, compare);
  }
}

void **get_all_keys(hashmap *map){
  int elements = map_size(map);
  int curr = 0;
  void **keys = (void**)malloc(elements*sizeof(void*));
  for(int i = 0; i < map->size; i++){
    node_t *temp = map -> items[i] -> head;
    while(temp != NULL){
      keys[curr] = temp -> key;
      curr++;
    }
  }
  return keys;
}

void print_map(hashmap *map, PRNTFUNC print){
  for(int i = 0; i < map->size; i++){
    printf("%d : \n",i);
    print_list(map->items[i], print);
  }
}
