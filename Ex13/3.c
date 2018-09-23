#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ana_ans 0.266666
#define rand_max 2147483647
extern void my_srand(void);
extern int my_GetRand(void);
extern int next_rnd2(void);

int main(){

  double x,y,r;
  int i,j;
  int n,c,rand;
  c = 0;


  scanf("%d",&n);

  for(i = 0;i < n;i++){
    my_srand();
    x = (double)my_GetRand() / rand_max;
    y = (double)my_GetRand() / rand_max;
    r = x*sqrt(1-x);
    //printf("%f,%f,%f,%d\n",r,x,y,rand);
    if(y < r) c++;
  }

  printf("ans = %f, error = %f\n",(double)c/n,fabs(ana_ans - (double)c/n));
}
