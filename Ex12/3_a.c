#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RAND_MAX 2147483647
#define N 101001000

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


int main(){
  my_srand();
  int i,j,r,p,rand;
  int fall = 0;
  double res = 0;
  int direct[4] = {};
  r = 35;
  p = 10000;

  for(i = 0;i < r;i++){
    for(j = 0;j < N;j++){
      rand = my_GetRand()%5;
      direct[rand]++;
      if(direct[rand] > r){
        fall++;
        //printf("over r\n");
        break;
      }
    }
    for(j = 0;j < 4;j++) direct[j] = 0;
  }
  res = (double)fall / (double)p * 100;
  printf("res = %f\n",res);
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
