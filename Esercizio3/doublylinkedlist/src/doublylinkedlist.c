#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../headers/doublylinkedlist.h"

node_t *create_node(void *k, void *d){
  node_t *n = (node_t*)malloc(sizeof(node_t));
  n -> data = d;
  n -> key = k;
  n -> next = NULL;
  n -> prev = NULL;
  return n;
}

overflow_list *create_empty_doubly_linked_list(){
  overflow_list *l = (overflow_list*)malloc(sizeof(overflow_list*));
  l -> head = NULL;
  l -> tail = NULL;
  return l;
}
//O(1)
void insert_item(overflow_list *l, void *k, void *v, CMPFUNC compare){
    node_t *n = create_node(k, v);
    if(l->head == NULL){
      l->head = l->tail = n;
    }else{
      l->tail->next = n;
      n->prev = l->tail;
      l->tail = n;
    }
}

//O(1)
void remove_from_beg(overflow_list *l){
  node_t *temp;
  if(l->head == NULL){
    printf("Trying to delete from empty list\n");
  }else{
    temp = l->head;
    l->head = l->head->next;
    if(l->head!=NULL){
      l->head->prev = NULL;
    }
    temp->next=NULL;

    free(temp);
  }
}
//O(1)
void remove_from_end(overflow_list *l){
  node_t *temp;
  if(l->tail==NULL){
    printf("Trying to delete on empty list\n");
  }else{
    temp = l->tail;
    l->tail->prev->next = NULL;
    l->tail = temp->prev;
    free(temp);
  }
}

void remove_item(overflow_list *l, void *k, CMPFUNC compare){
  node_t *temp = contains_key(l->head, k, compare);
  if(temp == l->head){
    remove_from_beg(l);
  }else if(temp == l->tail){
    remove_from_end(l);
  }else{
    if(temp!=NULL){
      if(temp->prev!=NULL){
        temp->prev->next = temp -> next;
      }
      if(temp->next!=NULL){
        temp->next->prev = temp->prev;
      }
      free(temp);
    }
  }
}

void print_list(overflow_list *l, PRNTFUNC print_item){
  if(l!=NULL && l->head != NULL && l->tail != NULL){
    node_t *h = l -> head;
      while(h != NULL){
      printf("Key: ");
      print_item(h->key);
      printf("Data: ");
      print_item(h->data);
      h = h->next;
    }
  }else{
    printf("Empty list\n");
  }
}

//returns: true if the key exists in the list
//         false otherwise
/*
node_t *contains_key(node_t *head, void *k, CMPFUNC compare){
    if (head == NULL){
      return NULL;
    }
    if (compare(head->key, k)==0){
      return head;
    }
    else{
      return contains_key(head->next, k, compare);
    }
}
*/
node_t *contains_key(node_t *head, void *k, CMPFUNC compare){
  //node_t *temp = head;
  while(head!=NULL && compare(k, head->key) != 0){
    head = head->next;
  }
  return head != NULL ? head : NULL;
}
//returns: true if the data exists in the list
//         false otherwise
node_t *contains_data(node_t *head, void *d, CMPFUNC compare){
  if (head == NULL){
    return NULL;
  }
  if (compare(head->data, d)==0){
    return head;
  }
  else{
    return contains_data(head->next, d, compare);
  }
}

int empty(overflow_list *l){
  return l->head == NULL && l->tail == NULL;
}

void free_list(node_t *start){
  while (start != NULL)
    {
        node_t* temp = start;
        start = start -> next;
        free(temp);
    }
}

int size(overflow_list *l){
  node_t *temp = l -> head;
  int list_size = 0;
  while (temp != NULL) {
    list_size++;
    temp = temp -> next;
  }
  return list_size;
}

void remove_all(overflow_list *l){
  node_t *temp;
  while (l->head != NULL) {
    temp = l->head;
    l->head = temp->next;
    free(temp);
  }
}
