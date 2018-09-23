#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int **b;
  int x;
  int y;
}Place;


void FindPlace(int **,int,int,int);
void P(int **,int,Place *,int,int);

int block_id=1;//置いたＬ字型ブロックを個々に識別できるように

int main(int argc,char **argv){
  int i,j,n;
  int **board;//正方格子
  int hole_x,hole_y;//１個のブロックが最初から置かれている正方格子上の場所

  if(argc!=4){//初期化関係
    fprintf(stderr,"Error: Input arguments were incorrect.\n");
    exit(1);
  }
  hole_x = atoi(argv[1]);//１個のブロックで塞いだｘ座標
  hole_y = atoi(argv[2]);//１個のブロックで塞いだｙ座標
  n = atoi(argv[3]); //正方格子のサイズ（２のべき乗にすること）

  if(!(hole_x>=0 && hole_x<n)|| !(hole_y>=0 && hole_y<n)){
    fprintf(stderr,"Error: The coodinates of blank (%d,%d) what you input was incorrect;\nThe acceptable range is 0 to %d.\n",hole_x,hole_y,n);
    exit(2);
  }

  board = (int **)malloc(sizeof(int *)*n);
  for(i=0;i<n;i++) board[i] = (int *)malloc(sizeof(int)*n);

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(i==hole_y&&j==hole_x)board[i][j]=-1;//ブロックが最初に置かれている場所は -1 とする
      else board[i][j] = 0; // 0 の場所にＬ字型ブロックを置いていく
    }
  }

  printf("board_Initialization:\n");
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%2d",board[i][j]);
      if(j!=n-1)printf(" ");
    }
    printf("\n");
  }

  FindPlace(board,n,hole_x,hole_y);//処理本体

  printf("Print_Answer:\n");//出力
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%2d",board[i][j]);
      if(j!=n-1)printf(" ");
    }
    printf("\n");
  }
  for(i=0;i<n;i++) free(board[i]);
  free(board);
  return 0;
}


void FindPlace(int **Board,int size,int h_x,int h_y){
  int i,j,k;
  Place block_place[4] = {};

  if(size <= 2){

    printf("Debug_2_for:\n");//出力
    printf("%d,%d\n",h_x,h_y);
    for(i=0;i<size;i++){
      for(j=0;j<size;j++){
        printf("%2d",Board[i][j]);
        if(j!=size-1)printf(" ");
      }
      printf("\n");
    }

    for(i = 0;i < 2;i++){
      for(j = 0;j < 2;j++){
        if(j == h_x && i == h_y) continue;
        Board[i][j] = block_id;
      }
    }

    printf("Debug_2:\n");//出力
    for(i=0;i<size;i++){
      for(j=0;j<size;j++){
        printf("%2d",Board[i][j]);
        if(j!=size-1)printf(" ");
      }
      printf("\n");
    }

    block_id++;
    return;
  }

  int mid = size / 2;
  int **A,**B,**C,**D;
  A = (int **)malloc(sizeof(int *)*mid);
  B = (int **)malloc(sizeof(int *)*mid);
  C = (int **)malloc(sizeof(int *)*mid);
  D = (int **)malloc(sizeof(int *)*mid);
  for(i = 0;i < mid;i++){
    A[i] = (int *)malloc(sizeof(int) * mid);
    B[i] = (int *)malloc(sizeof(int) * mid);
    C[i] = (int *)malloc(sizeof(int) * mid);
    D[i] = (int *)malloc(sizeof(int) * mid);
  }

  P(Board,mid,block_place,h_x,h_y);

  for(k = 0;k < mid;k++){
    for(j = 0;j < mid;j++){
      A[k][j] = Board[k][j];
      B[k][j] = Board[k][j+mid];
      C[k][j] = Board[k+mid][j];
      D[k][j] = Board[k+mid][j+mid];
    }
  }



  block_place[0].b = A;
  block_place[1].b = B;
  block_place[2].b = C;
  block_place[3].b = D;

  for(i = 0;i < 4;i++){

    printf("Debug_Board:\n");//出力
    for(k=0;k<size;k++){
      for(j=0;j<size;j++){
        printf("%2d",Board[k][j]);
        if(j!=size-1)printf(" ");
      }
      printf("\n");
    }


    FindPlace(block_place[i].b,mid,block_place[i].x,block_place[i].y);

    for(k=0;k<mid;k++){
      for(j=0;j<mid;j++){
        if(i == 0) Board[k][j] = block_place[i].b[k][j];
        if(i == 1) Board[k][j+mid] = block_place[i].b[k][j];
        if(i == 2) Board[k+mid][j] = block_place[i].b[k][j];
        if(i == 3) Board[k+mid][j+mid] = block_place[i].b[k][j];
      }
    }
  }

  /*
  この関数は、再帰呼び出しになるので、Boardは各部分問題の時点での大きさ(size)となる。
  既にブロックが置かれている場所はh_xとh_yで指定する
  Strassen と同様、コードの配置（処理の流れ）は以下のようになるはずである
  極小まで分解されたときの処理（再帰の打ち切り）⇒ 部分問題用の配列確保 ⇒ 再帰に持ち込むための準備の処理 ⇒ 再帰呼び出し
  */
}


void P(int **Board,int mid,Place *block_place,int h_x,int h_y){
  block_place[0].x = mid - 1;
  block_place[0].y = mid - 1;
  block_place[1].x = 0;
  block_place[1].y = mid-1;
  block_place[2].x = mid-1;
  block_place[2].y = 0;
  block_place[3].x = 0;
  block_place[3].y = 0;

  if(h_x < mid && h_y < mid ){
    Board[mid][mid-1] = block_id;
    Board[mid-1][mid] = block_id;
    Board[mid][mid] = block_id++;

    block_place[0].x = h_x;
    block_place[0].y = h_y;
    /*  block_place[1].x = mid-1;
    block_place[1].y = mid;
    block_place[2].x = mid;
    block_place[2].y = mid-1;
    block_place[3].x = mid;
    block_place[3].y = mid;*/

  }
  else if(h_x >= mid && h_y < mid ){
    Board[mid-1][mid-1] = block_id;
    Board[mid][mid-1] = block_id;
    Board[mid][mid] = block_id++;

    block_place[1].x = h_x-mid;
    block_place[1].y = h_y;
    /*block_place[1].x = mid-1;
    block_place[1].y = mid-1;
    block_place[2].x = mid-1;
    block_place[2].y = mid;
    block_place[3].x = mid;
    block_place[3].y = mid;*/
  }
  else if(h_x < mid && h_y >= mid ){
    Board[mid-1][mid-1] = block_id;
    Board[mid-1][mid] = block_id;
    Board[mid][mid] = block_id++;

    block_place[2].x = h_x;
    block_place[2].y = h_y-mid;
    /*block_place[1].x = mid-1;
    block_place[1].y = mid-1;
    block_place[2].x = mid;
    block_place[2].y = mid-1;
    block_place[3].x = mid;
    block_place[3].y = mid;*/
  }
  else if(h_x >= mid && h_y >= mid ){
    Board[mid-1][mid-1] = block_id;
    Board[mid-1][mid] = block_id;
    Board[mid][mid-1] = block_id++;

    block_place[3].x = h_x-mid;
    block_place[3].y = h_y-mid;
    /*block_place[1].x = mid-1;
    block_place[1].y = mid-1;
    block_place[2].x = mid;
    block_place[2].y = mid-1;
    block_place[3].x = mid-1;
    block_place[3].y = mid;*/
  }


}
