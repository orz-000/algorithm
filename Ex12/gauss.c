#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RAND_MAX 2147483647

extern void my_srand(void);
extern int my_GetRand(void);


int main(){
  int i;
  double x1,x2,g1,g2;
  int n = 500000;
  int data[8] = {};
  my_srand();
  for(i = 0;i < n;i++){
    x1 = (double)my_GetRand() / RAND_MAX;
    x2 = (double)my_GetRand() / RAND_MAX;
    //printf("%f,%f\n",x1,x2 );
    g1 = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2);
    g2 = sqrt(-2 * log(x1)) * sin(2 * M_PI * x2);
    printf("%f,%f\n",g1,g2);
    if(g1 >= -4 && g1 <= -3) data[0]++;
    if(g1 >= -3 && g1 <= -2) data[1]++;
    if(g1 >= -2 && g1 <= -1) data[2]++;
    if(g1 >= -1 && g1 <= 0) data[3]++;
    if(g1 >= 0 && g1 <= 1) data[4]++;
    if(g1 >= 1 && g1 <= 2) data[5]++;
    if(g1 >= 2 && g1 <= 3) data[6]++;
    if(g1 >= 3 && g1 <= 4) data[7]++;

    if(g2 >= -4 && g2 <= -3) data[0]++;
    if(g2 >= -3 && g2 <= -2) data[1]++;
    if(g2 >= -2 && g2 <= -1) data[2]++;
    if(g2 >= -1 && g2 <= 0) data[3]++;
    if(g2 >= 0 && g2 <= 1) data[4]++;
    if(g2 >= 1 && g2 <= 2) data[5]++;
    if(g2 >= 2 && g2 <= 3) data[6]++;
    if(g2 >= 3 && g2 <= 4) data[7]++;
  }

  for(i = 0;i < 8;i++) printf(" %d",data[i]);
  printf("\n");

  return 0;
}
