#include <stdio.h>
#include <stdlib.h>

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

void quickSort(int* A,int n,int p,int r){
  int q;
  if( p < r){
    q = partition(A,p,r);
    quickSort(A,n,p,q-1);
    quickSort(A,n,q+1,r);
  }
}


int main(){
int i;
int A[10] = {4,7,8,5};
//printf("qq");
quickSort(A,9,0,3);
for(i = 0;i < 4;i++) printf(" %d\n",A[i]);
  return 0;
}
