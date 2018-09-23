#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int n;
int p[100] = {};
int rank[100] = {};
//int *p;
//int *rank;
//p = (int *)malloc(sizeof(int) * n);
//rank = (int *)malloc(sizeof(int) * n);

void makeset(int x){
  p[x] = x;
  rank[x] = 0;
}

int findset(int x){
  if( x != p[x] ){
    p[x] = findset(p[x]);
  }
  return p[x];
}

bool same(int x,int y){
  return findset(x) == findset(y);
}

void link(int x,int y){
  if( rank[x] > rank[y] ){
    p[y] = x;
  }
  else {
    p[x] = y;
    if( rank[x] == rank[y]){
      rank[y]++;
    }
  }
}


void unite(int x,int y){
  link(findset(x),findset(y));
}



int main(){
  scanf("%d",&n);
  return 0;
}
