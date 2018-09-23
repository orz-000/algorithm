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
  FILE *fp;
  fp = fopen("rndwalk_3.txt","w");
  node data;
  data.x = 0;
  data.y = 0;
  int i,j,r,rand;
  int fall = 0;
  double res = 0;
  r = 99999;

  for(j = 0;j < N;j++){
    rand = my_GetRand()%5;
    if(rand == 0) data.x++;
    if(rand == 1) data.x--;
    if(rand == 2) data.y++;
    if(rand == 3) data.y--;
    fprintf(fp,"%d %d\n",data.x,data.y);
  }
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
