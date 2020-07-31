typedef struct _hashmap{
  overflow_list **items;
  int size;
}hashmap;

typedef int (*HASHFUNC)(const void *, int);

/*
Fisso m < |U| e lo chiamo size
*/
hashmap *create_new_map(int size);
void free_map(hashmap *map);
int is_empty(hashmap *map);
int map_size(hashmap *map);
void remove_all_association(hashmap *map);
int is_present(hashmap *map, void *key, HASHFUNC hashfunc, CMPFUNC compare);
void insert_association(hashmap *map, void *key, void *val, HASHFUNC hash, CMPFUNC compare);
void *retrieve_value(hashmap *map, void *key, HASHFUNC hash, CMPFUNC compare);
void delete_association(hashmap *map, void *key, HASHFUNC hash, CMPFUNC compare);
void **get_all_keys(hashmap *map);
void print_map(hashmap *map, PRNTFUNC print);
