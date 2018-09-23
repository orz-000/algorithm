#define N 10000000 //逐次計算の段階で、「計算が合っているかどうか？」を確かめるだけなら分割数Nを減らす

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double);

int main(int argc,char *argv[]){
  int i,threads;
  double x1,x2,y1,y2,dx,dS; //積分に用いる変数
  double S=0.0;//Answer for sequential
  double S2=0.0;//Answer for parallel

  double st,et; //実行時間を得るために使う（後で2回のタイマーの差をとる）


  /* Initialization step */
    if(argc==2){
       threads = atoi(argv[1]);
     }
    else threads = omp_get_max_threads();
    omp_set_num_threads(threads);


  printf("Number of processors: %d\n",omp_get_num_procs());
  printf("Max threads: %d\n",omp_get_max_threads());

  dx = 5.0/N; //１計算区間あたりの計算幅




  /* Compute sequentially
  st = omp_get_wtime();
  for(i = 0;i < N;i++){
    x1 = i * dx;
    x2 = (i + 1) * dx;
    y1 = f(x1);
    y2 = f(x2);
    S += ((y1 + y2) * (x2 - x1)) / 2;
  }
  et = omp_get_wtime();

  printf("sequetially: %8.6f sec.\n",et-st);
  printf("S = %f\n",S);//逐次実行の結果
*/



  /* Compute in parallel */
  st = omp_get_wtime();
  #pragma omp parallel for reduction(+:S2) private(x1,x2,y1,y2)
  for(i = 0;i < N;i++){
    x1 = i * dx;
    x2 = (i + 1) * dx;
    y1 = f(x1);
    y2 = f(x2);
    S2 += ((y1 + y2) * (x2 - x1)) / 2;
  }
  et = omp_get_wtime();
  /*
       [ Complete Here !!]
  ※コード自体は逐次実行版と同じものを書き、OpenMP並列化せよ
  */



  printf("Elapsed Time: %8.6f sec.\n",et-st);
  printf("S2 = %f\n",S2);//並列実行の結果
  return 0;
}



double f(double x){//f(x) = x-log(sqrt(3+x))
  return x-log(sqrt(3+x));
}
