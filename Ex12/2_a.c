#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Complete Here !! (Variables Declaration) */
#define A 48271L
#define M 2147483647L
#define Q (M/A)
#define R (M%A)

static int B[55];
static int next=0;

int next_rnd1(void);
int next_rnd2(void);
int next_rnd3(void);
void init_rnd(void);
void my_srand(void);
int data[100];

int main(){
  int getrand,i;

  my_srand();
  for(i=0;i<100;i++){
    getrand = next_rnd3();
    printf("%d: %d\n",i+1,getrand);
  }

  //for(i=0;i<20;i++) printf("%d ",data[i]); // sample for listing outputs
  printf("\n");
  return 0;
}

int next_rnd1(void){
  static long x=53402397;
  x=x*65539+125654;
  if (x<0){x+=2147483647;x+=1;}
  return x;
  /* Complete Here !!*/

}

int next_rnd2(void){
  static int x=1;
  /* Complete Here !! */
  x=A*(x%Q)-R*(x/Q);
  if (x<0) x=x+M;
  return x;
}

void init_rnd(void){
  int i;
  for (i=0;i<55;i++) {
    B[i] = next_rnd2();/* Complete Here !! */
    //  printf("a:%d\n",B[i]);
  }
}

int next_rnd3(void){
  init_rnd();
  /* Complete Here !!*/
  int i, j, x;
  i=(next+31)%55;
  x=(B[i]-B[next]);
  if (x<0) {
    x+=2147483647; x+=1;}
    B[next]=x;
    next=(next+1)%55;
    return x;
  }

  void my_srand(void){
    time_t stamp;
    struct tm *t;

    stamp = (int)time(NULL);
    t = localtime(&stamp);

    next = t->tm_sec; // seed
  }
