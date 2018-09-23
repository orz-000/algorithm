#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <immintrin.h>
#include <intrin.h>

extern int my_GetRand(void);
extern void my_srand(void);


float calc_original(float, float *, float *,int);
float calc_avx(float, float *, float *, int);

int main(int argc,char **argv){
  int i,num_data;
  double et,st;
  float *a,*b , coef = 2.0; // coef:定数c
  float result,result2;

  if(argc==2) num_data = atoi(argv[1]); //実行時の引数でデータ数を入力
  else num_data = 8; //引数が正しくなければ、とりあえずデータ数を８としておく

  my_srand();

  a = (float *)_mm_malloc(sizeof(float)*num_data,32);/* [ Complete Here !! ] */     // 1次元配列 a と b のメモリ領域を確保
  b = (float *)_mm_malloc(sizeof(float)*num_data,32);/* [ Complete Here !! ] */     // calc_avx()において、これらをベクトルに渡してSIMD演算をする


  printf("Data Initialization.(Random number generation)\n");
  for(i=0;i<num_data;i++){
    a[i] = (float)(my_GetRand()%100)/10000.0 -0.005;
    b[i] = (float)(my_GetRand()%100)/10000.0 -0.005;
  }

  printf("Computing  sum of a[]*(c*b[])\n");
  st = omp_get_wtime();/* [ Complete Here !! ] */    // OpenMPの関数で時間計測
  result = calc_original(coef,a,b,num_data); //通常の計算
  et = omp_get_wtime();/* [ Complete Here !! ] */    // OpenMPの関数で時間計測
  printf("[Original] elapsed time: %12.8f sec.\n",et-st);

  st = omp_get_wtime();/* [ Complete Here !! ] */    // OpenMPの関数で時間計測
  result2 = calc_avx(coef,a,b,num_data);  //AVXバージョン
  et = omp_get_wtime();/* [ Complete Here !! ] */    // OpenMPの関数で時間計測
  printf("[AVX] elapsed time: %12.8f sec.\n",et-st);
  printf("[Answer] orig:%f /  avx:%f\n",result,result2);

  _mm_free(a);
  _mm_free(b);
}


float calc_original(float c,float *v1, float *v2, int n){    // 与えられた式をそのまま実装したもの（あとでOpenMP化せよ）
  int i;
  float sum = 0;

/*[ Complete Here !! ]*/; //あとで、ここに#pragma ...  を１行入れてOpenMP並列化
  for(i = 0; i < n; i++){
    sum += v1[i] *  (sqrt(c)*v2[i]);
  }
  return sum;
}


float calc_avx(float c,float *v1, float *v2, int n){ // AVXによるベクトル演算(SIMD)をここで作る
    int i;
    int num_chunk, vec_size = sizeof(__m256)/sizeof(float);
    float *t,sum;
    __m256 u = {0}, v_c; // u：各ベクトル演算で計算した部分和を足していく　v_c：スカラー変数 c を保持するベクトル

    t = (float *)_mm_malloc(sizeof(float)*8,32);

    v_c =  _mm256_load_ps(&c);/*[ Complete Here !! ]*/  //スカラー変数 c を ベクトル v_c へ放送する


    num_chunk = n / vec_size/*[ Complete Here !! ]*/;         // １回のベクトル演算でまとめて扱える変数はvec_sizeだから、全部でnum_chunk回のベクトル演算をする
    for(i = 0; i < num_chunk; i++){
        __m256 vec_v1 = _mm256_load_ps(&v1[i]);/*[ Complete Here !! ]*/  // 通常のfloat型配列v1をベクトル vec_v1へロード
        __m256 vec_v2 = _mm256_load_ps(&v2[i]);/*[ Complete Here !! ]*/  // 通常のfloat型配列v2をベクトル vec_v2へロード
        __m256 a = _mm256_setzero_ps();
        a = _mm256_mul_ps(_mm256_sqrt_ps(v_c),vec_v2);/*[ Complete Here !! ]*/         //計算式部分。イントリンシック関数を入れ子にすれば１行で書けるが、
        vec_v1 = _mm256_mul_ps(a,vec_v1);
                                                  //分けて書いてもよい。必要に応じて、__m256型のベクトル変数を新たに宣言せよ。

        u = u + vec_v1;/*[ Complete Here !! ]*/              // vec_v1の部分的な結果をuに加える
    }

    _mm256_store_ps(t,u);/* [ Complete Here !! ] */                    // ベクトル u を 通常のfloat型配列 t へストア



    sum = t[0] + t[1] + t[2] + t[3] + t[4] + t[5] + t[6] + t[7];   // for文を書くよりも、実は速く動作する。ここは触らないこと
    _mm_free(t);
    return sum;
}
