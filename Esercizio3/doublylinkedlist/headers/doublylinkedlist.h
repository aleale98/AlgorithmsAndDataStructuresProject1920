struct node_t{
    struct node_t *prev;
    struct node_t *next;
    void *data;
    void *key;
};

typedef struct node_t node_t;

struct overflow_list{
  node_t *head;
  node_t *tail;
};

typedef struct overflow_list overflow_list;

typedef int (*CMPFUNC)(const void *, const void*);
typedef void (*PRNTFUNC)(const void *);

node_t *create_node(void *d, void *k);
overflow_list* create_empty_doubly_linked_list();
void insert_item(overflow_list *l, void *data, void *k, CMPFUNC compare);
void remove_from_beg(overflow_list *l);
void remove_from_end(overflow_list *l);
void remove_item(overflow_list *l, void *k, CMPFUNC compare);
node_t *contains_key(node_t *head, void *k, CMPFUNC compare);
node_t *contains_data(node_t *head, void *d, CMPFUNC compare);
void print_list(overflow_list *l, PRNTFUNC print_int);
int empty(overflow_list *l);
void free_list(node_t *start);
int size(overflow_list *l);
void remove_all(overflow_list *l);
