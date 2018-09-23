#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  int money[4] = {25,10,5,1};
  int pay[4] = {};
  int rest[4] = {};
  int charge,i,charge_origin;
  int sum = 0;
  printf("Input numbers of each cent(coin).\n");
  printf("->");
  scanf("%d%d%d%d",&rest[0],&rest[1],&rest[2],&rest[3]);
  printf("Input how many cents should you pay?\n");
  printf("->");
  scanf("%d",&charge_origin);
  charge = charge_origin;
  for(i = 0;i < 4;i++){

    while(1){
      if(charge >= money[i] && rest[i] > 0){
        pay[i]++;
        rest[i]--;
        charge -= money[i];
      }
      else break;
    }
  }

  if(charge > 0) printf("Error: you cannot pay for this value.\n");
  else{

    for(i = 0;i < 4;i++){
      sum += pay[i];
      printf("[%dcent] %d used.\n",money[i],pay[i]);
    }

    printf("Totally, you used %d coins for %d cents.\n",sum,charge_origin);
  }
  return 0;
}
