#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>


#define MAX_VALUE    15000 //乱数で得られる値の最大値

unsigned long getrusageval(void);
void start_timer(unsigned int *);
unsigned get_elapsed_time(unsigned int *);
unsigned int start_tm;

unsigned long getrusageval(void){
  struct rusage tr;
  struct timeval tv;
  getrusage(RUSAGE_SELF, &tr);
  tv = tr.ru_utime;
  return ((unsigned long)tv.tv_sec)*1000000+tv.tv_usec;
}

void start_timer(unsigned int *start_tm){
  *start_tm = (unsigned int)getrusageval();
  return;
}

unsigned int get_elapsed_time(unsigned int *start_tm){
  unsigned int stop_tm = (unsigned int)getrusageval();
  return (stop_tm>=*start_tm)? (stop_tm-*start_tm) : (stop_tm);
}

void selection(int*,int);
void merge(int*,int,int);

int *B;  //mergesortで必要となる外部領域


/*時間計測関数の外部参照（以降の演習も以下３行はコピー＆ペーストする*/

extern void start_timer(unsigned int *);
extern unsigned get_elapsed_time(unsigned int *);
extern unsigned int start_tm;
/*いつもコピーする部分ここまで*/

int main(int argc, char *argv[]){
  int i, j, n, t, k;
  float ave = 0;
  int *A;
  FILE *fp;
  /*if (argc != 2) {//データサイズが引数として与えられていない
  fprintf(stderr, "Error: argument which indicates the problem size is required.\n");
  exit(1);
}*/

//n = atoi(argv[1]);
A=(int *)malloc(sizeof(int)*(n+1));
B=(int *)malloc(sizeof(int)*(n+1));
fp = fopen("selectionSort_time.txt","w");


for(k = 0;k < 6;k++){
  for(j = 0; j < 10; j++){
    //printf("%d\n",k);
    if(k == 0) n = 50000;
    else if(k == 1) n = 100000;
    else if(k == 2) n = 150000;
    else if(k == 3) n = 200000;
    else if(k == 4) n = 250000;
    else if(k == 5) n = 300000;


    // rand関数でデータを初期化（現状はこのまま使ってよい）
    srand(n);
    for (i = 1; i <= n; i++) {
      t=rand();
      if (t < MAX_VALUE) A[i] = t;
      else A[i] = t % MAX_VALUE;
      #ifdef DEBUG
      printf(" A[%5d] = %5d \n", i , A[i]);
      #endif
    }
    //データ初期化ここまで

    //printf("%d\n",j);
    //printf("a\n");
    start_timer(&start_tm);//時間計測開始
    //printf("b\n");
    //selection(A, n); //selection sort
    merge(A, 1, n); //merge sort
    //printf("c\n");
    // タイマーを止めて、計測時間を表示（今回はこのまま使ってもよい。今後必要に応じて、関数呼出の切り分け等をすること）
    //printf("%5d : elapsed time is %10.3f milliseconds. \n", n, get_elapsed_time(&start_tm)*1.0e-3);
    ave +=  get_elapsed_time(&start_tm)*1.0e-3;

    #ifdef DEBUG
    for (i = 1; i <= n; i++) {
      printf(" A[%5d] = %5d \n", i, A[i]);
    }
    #endif


  }
  ave /= 10;
  printf("%d %f\n",n, ave);
}
free(A);
free(B);
fclose(fp);
return 0;
}


//selection sortの本体を書く
void selection(int *A, int n){
  //printf("%d\n",n);
  int i, j, min, t;
  for (i=1;i<n;i++){
    min=i;
    for (j=i+1; j<=n; j++)
    if (A[j]< A[min]) min=j;
    t=A[min];
    A[min]=A[i];
    A[i]=t;
  }
}

//再帰版merge sortの本体を書く
void merge(int *A, int left, int right){//退避用の外部変数はB[]を使ってください（既に宣言済み）

  int i,j,k,mid;
  if (right>left) {
    mid=(right+left)/2;
    merge(A,left,mid);
    merge(A,mid+1,right);
    for (i=left;i<=mid;i++) B[i]=A[i];
    for (i=mid+1,j=right;i<=right;i++,j--)B[i]=A[j];
    i=left;j=right;
    for (k = left; k <= right; k++)
    if (B[i]<B[j]) A[k]=B[i++];
    else A[k]=B[j--];
  }


}
