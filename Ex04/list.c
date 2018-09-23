#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int key;
  struct node *next;
  struct node *prev;
} node;
typedef node node;
node *nil;

node* listSearch(int );
void init();
void printlist();
void deletenode(node* );
void deletefirst();
void deletelast();
void deletekey(int);
void insert(int);

node* listSearch(int key){

  node *cur;
  cur = nil -> next;
  while( cur != nil && cur -> key != key){
    cur = cur -> next;
  }
  return cur;
}

void init(){
  nil = (node *)malloc(sizeof(node));
  nil -> next = nil;
  nil -> prev = nil;
}

void printlist(){
  node *cur = nil -> next;
  int isf = 0;
  while(1){
    if( cur == nil) break;
    if( isf++ > 0) printf(" ");
    printf("%d", cur -> key);
    cur = cur -> next;
  }
  printf("\n");
}

void deletenode(node *t){
  if( t == nil) return;
  t -> prev -> next = t -> next;
  t -> next -> prev = t-> prev;
  free(t);
}

void deletefirst(){
  deletenode(nil -> next);
}

void deletelast(){
  deletenode(nil -> prev);
}

void deletekey(int key){
deletenode(listSearch(key));
}

void insert(int key){
  node *x = (node *)malloc(sizeof(node));
  x -> key = key;

  x -> next = nil -> next;
  nil -> next -> prev = x;
  nil -> next = x;
  x -> prev = nil;
}

int main(){
  return 0;
}
