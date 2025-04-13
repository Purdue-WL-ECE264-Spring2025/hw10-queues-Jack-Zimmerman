#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node * nn = (struct list_node*)malloc(sizeof(struct list_node));
  nn->value = value;
  nn->next = NULL;
 
  return nn;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node * nn = new_node(value);
 
  nn->next = list->head;
  list->head = nn;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node * nn = new_node(value);
  struct list_node * tnode = list->head;
   
  if (tnode == NULL){
    list->head = nn;
    return;
  }
    
  //iterate to end
  while (tnode->next){
    tnode = tnode->next;  
  }

  //set next at end to be new inset;
  tnode->next = nn;
}

size_t remove_from_head(struct linked_list *list) {
  struct list_node * lost_node = list->head;

  list->head = list->head->next;

  //dont forget to free
  size_t value = lost_node->value;

  free(lost_node);

  return value;
}

size_t remove_from_tail(struct linked_list *list) {  
  struct list_node * tnode = list->head;
  //iterate to end
  while (tnode->next != NULL){
    tnode = tnode->next;
  } 

  size_t value = tnode->value;
  free(tnode);
  tnode = NULL;

  return value;

}

void free_list(struct linked_list list) {

  if (!list.head){
    return;
  }

  while(list.head->next){
    struct list_node * tlost = list.head;

    list.head = list.head->next;
    
    free(tlost); 
  }

  free(list.head);
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
