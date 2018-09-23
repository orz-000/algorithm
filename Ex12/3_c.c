#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RAND_MAX 2147483647
#define N 10000

#define A 48271L
#define M 2147483647L
#define Q (M/A)
#define R (M%A)

static int B[55];
static int next=0;

int next_rnd1(void);
extern void my_srand(void);
extern int my_GetRand(void);
extern int next_rnd2(void);

typedef struct node{
  int x;
  int y;
}node;


int main(){
  my_srand();
  int i,j,r,p,rand;
  int fall = 0;
  double sum_x = 0;
  double sum_y = 0;
  double res = 0;
  r = 99999;
  p = 10000;
  node data[p];
  for(i = 0;i < p;i++){
    data[i].x = 0;
    data[i].y = 0;
  }
  for(i = 0;i < p;i++){
    for(j = 0;j < N;j++){
      rand = my_GetRand()%5;
      if(rand == 0) data[i].x++;
      if(rand == 1) data[i].x--;
      if(rand == 2) data[i].y++;
      if(rand == 3) data[i].y--;
    }
    sum_x += data[i].x;
    sum_y += data[i].y;
  }
  sum_x /= p;
  sum_y /= p;
  printf("%f,%f\n",sum_x,sum_y);
  return 0;
}


int next_rnd1(void){
  static long x=53402397;
  x=x*65539+125654;
  if (x<0){x+=2147483647;x+=1;}
  //printf("%ld\n",x);
  return x;
  /* Complete Here !!*/

}
