#include <stdio.h>
#include <stdlib.h>
#define INF 1000
void DFS(int);
void rDFS(int);
void Mat_reverse(int**);
int min_visited(int*);
int r_min_visited(int*);
void swap(int*, int*);
int partition(int* A,int p, int r);
void quickSort(int* A,int p,int r);
void Find_SCC();
int n;         //number of vertex ( 'V' of graph G(V,E) )
int label = 0;     //the order of vertex visiting
int min;
int c = 0;
int c2 = 0;
int c3[10] = {};
int *visited;  //if vertex_i was visited?
int *r_visited;
int **A;       //Adjacency matrix
int **group;

int main(){
  int start;
  int i, j;
  /* input number of vertex */
  printf("Input the number of data: ");
  scanf("%d", &n);

  /* memory allocation and initialization */
  visited = (int *)malloc(sizeof(int)*n);
  r_visited = (int *)malloc(sizeof(int)*n);
  A = (int **)malloc(sizeof(int *) * n);
  group = (int **)malloc(sizeof(int *) * n);
  for(i=0 ;i < n;i++){
    A[i] = (int *)malloc(sizeof(int )*n);
    group[i] = (int *)malloc(sizeof(int )*n);
    visited[i] = 0;
    r_visited[i] = 0;
  }

  for(i = 0;i < n;i++){
    for(j = 0;j < n;j++){
      group[i][j] = -1;
    }
  }


  printf("Input the Adjacency matrix:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &A[i][j]);
    }
  }

  printf("Input the initial node: 1 to %d\n",n);
  scanf("%d", &start);

  //printf("The edges in the DFS tree with root %d are:\n", start);
  DFS(start-1);

  Mat_reverse(A);

  min = min_visited(visited);

  Find_SCC();

  for(i = 0;i < c2;i++){
    printf("Strongly Connected Decomposition (Group %d):\n",i+1);
    //printf("%d\n",c3[i]-1);
    quickSort(group[i],0,c3[i]-1);
    for(j = 0;j < n;j++){
      if(group[i][j] != -1){
        printf("Vertex. %d\n",group[i][j] + 1);
      }
      else continue;
    }
  }

  /* memory free */
  for(i=0 ;i < n;i++) free(A[i]);
  free(A);
  free(visited);

  return 0;
}

void DFS(int node){
  int t;

  visited[node] = ++label;
  //printf("(%d,%d)\n", node, visited[node]);

  for (t = 0; t < n; t++) {
    if( A[node][t] == 1 && visited[t] == 0 /* Complete Here!! */) {
      DFS(t);/* Complete Here!! */   //Recursive call
    }
  }

}

void rDFS(int node){
  int t;
  r_visited[node] = 1;
  //printf("(%d,%d)\n", node, visited[node]);
  group[c2][c3[c2]] = node;
  c3[c2]++;

  for (t = 0; t < n; t++) {
    if ( A[node][t] == 1 && r_visited[t] == 0 ) {
      //printf("node == %d, t == %d\n",node,t);
      rDFS(t);
    }
  }

}

void Mat_reverse(int **A){

  int i = 0;
  int j = 0;

  for(i = 0;i < n;i++){
    for(j = i+1; j < n;j++){
      if( (A[i][j] == 1 && A[j][i] == 0) || (A[i][j] == 0 && A[j][i] == 1) ){
        swap(&A[i][j],&A[j][i]);
      }
    }
  }

  //printf("Mat_reverse\n");

  for(i = 0;i < n;i++){
    for(j = 0;j < n;j++){
      //printf("%d ", A[i][j]);
    }
    //printf("\n");
  }
  //printf("\n");
}

int min_visited(int *visited){
  int min = INF;
  int i = 0;
  for(i = 0;i < n;i++){
    if(visited[i] < min){
      min = i;
    }
  }
  return min;
}

int r_min_visited(int *visited){
  int min = INF;
  int i = 0;
  for(i = 0;i < n;i++){
    if(r_visited[i] == 0 && visited[i] < min){
      min = i;
    }
  }
  return min;
}

void swap(int *a, int *b){
  int tmp;
  tmp = *b;
  *b = *a;
  *a = tmp;
}

int partition(int* A,int p, int r){
  int i,j;
  int t;
  i = p - 1;
  for(j = p;j < r;j++){
    if(A[j] <= A[r]){
      i++;
      t = A[i]; A[i] = A[j]; A[j] = t;
    }
  }
  t = A[i + 1]; A[i + 1] = A[r]; A[r] = t;
  return i + 1;
}

void quickSort(int* A,int p,int r){
  int q;
  if( p < r){
    q = partition(A,p,r);
    quickSort(A,p,q-1);
    quickSort(A,q+1,r);
  }
}

void Find_SCC(){
    while(min != INF){
      rDFS(min);
      min = r_min_visited(visited);
      c2++;
    }
}
