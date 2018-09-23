#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*

[ Complete Here!! (Prototype declarations)]

*/
extern void my_srand(void);
extern int my_GetRand(void);
extern int next_rnd2(void);

int Fermat_test(int);

int main(int argc,char *argv[]){
  int status;
  int P;
  int i,n ,flag;
  int judge[2]={0,0};




  if(argc==2){
    n = atoi(argv[1]);
  }
  else{
    printf("Error: Number of testing is required.\n");
    exit(1);
  }



  printf("input number of P(>=4):\n->");
  status = scanf("%d",&P);
  if(status!=1 || P < 4){
    printf("Error: Illegal input is detected.\n");
    exit(0);
  }



  /* [ Complete Here!! (Initialize the seed of your random number generator) ] */



  for(i=0;i<n;i++){
    flag = Fermat_test(P);

    if(flag==1) judge[1]++;
    else judge[0]++;
  }

  printf("Tested %d times. Judged as ...\n",n);
  printf("[Prime number]  %5d times /  [Composite number] %5d times.\n",judge[1],judge[0]);
  if(judge[0]==0) printf("%d may be assumed as a prime number.\n",P);
  else printf("%d is a composite number.\n",P);

  return 0;
}



int Fermat_test(int P){
  int i,n;
  long long int A,x,y;




  for(i=1;i<32 ;i++){
    if( ((P-1)&(1<<i)) != 0 ){
      n=i;
    }
  }
  n++;


  
  //a^{p-1}の底を乱数で生成して初期化
  /* [ Complete Here!! ] */
  while(A < 2){
    my_srand();
    A = my_GetRand() % (P - 1);
  }

  x = A;
  for(i=n-2;i>=0;i--){
    y= x*x%P;/* [ Complete Here!! ] */
    if( y == 1 && x!= 1 && x!= P-1/* [ Complete Here!! ] */ ) return 0;

    if( ((P-1) & (1<<i)) != 0 ){ // b[i]==1
      y= y*A % P;
    }

    x = y;
  }


  if(y == 1) return 1;
  else return 0;
  /* [ Complete Here!! ] */

}
