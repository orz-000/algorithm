#include <stdio.h>
#include <stdlib.h>

#define PASSABLE 1       //mazesolve()の戻り値はこれらのどちらかにすること
#define CANNOT_PASS 0

int mazesolve(int,int);

int **Maze;
int **Solution;
int **visited;
int nx,ny;
int s_x,s_y;
int g_x,g_y;
int d[2] = {-1,1};
int searched_id=0;      //探索順番記録用
int sum = 0,len = 0;
FILE *fp;

int main(int argc,char** argv){
  int i,j;
  int check;

  if(argc!=2){
    fprintf(stderr,"error: Give the argument of inputting file for this program.\n");
    exit(1);
  }
  fp = fopen(argv[1],"r");
  if(fp==NULL){
    fprintf(stderr,"error: no such file named '%s'.\n",argv[1]);
    exit(2);
  }

  fscanf(fp,"%d %d",&nx,&ny);
  // Maze[y][x]
  Solution = (int **)malloc(sizeof(int *)*ny);
  Maze = (int **)malloc(sizeof(int *)*ny);
  visited = (int **)malloc(sizeof(int *)*ny);
  for(j=0;j<ny;j++){
    Maze[j]=(int *)malloc(sizeof(int)*nx);
    Solution[j]=(int *)malloc(sizeof(int)*nx);
    visited[j]=(int *)malloc(sizeof(int)*nx);
    for(i=0;i<nx;i++){
      fscanf(fp,"%d", &Maze[j][i]);
      Solution[j][i]=0;
    }
  }

  for(i = 0;i < ny;i++){
    for(j = 0;j < nx;j++){
      visited[i][j] = 0;
    }
  }
  //printf("Where to Start?->");
  fscanf(fp,"%d %d",&s_x,&s_y);
  //printf("Where is the Goal?->");
  fscanf(fp,"%d %d",&g_x,&g_y);
  fclose(fp);
  printf("\n");
  /*
  for(j=0;j<ny;j++){//check input case
  for(i=0;i<nx;i++){
  printf("%d", Maze[j][i]);
  if(i==nx-1)printf(" ");
}
if(j!=ny)printf("\n");
}
*/



check = mazesolve(s_x,s_y);

if(check== CANNOT_PASS){
  printf("There is no way to solve this maze.\n");
}
else{

/*  for(j=0;j<ny;j++){// output the solution
    for(i=0;i<nx;i++){
      printf("%5d", Solution[j][i]);
      if(i==nx-1)printf(" ");
    }

    if(j!=ny-1)printf("\n");
  }
*/

printf("%d,%d\n",sum,len);
}


for(j=0;j<ny;j++){
  free(Maze[j]);
  free(Solution[j]);
}
free(Maze);
free(Solution);

return 0;
}



int mazesolve(int search_x, int search_y){
  sum++;
  int i = 0,j,check;
  visited[search_y][search_x] = 1;
  searched_id++;
  Solution[search_y][search_x] = searched_id;
  if(search_x == g_x && search_y == g_y) {
    //searched_id++;
    //Solution[search_y][search_x] = searched_id;
    return PASSABLE;
  }
  for(i = 0;i < 2;i++){
    if(search_x + d[i] < nx && search_x + d[i] >= 0 && Maze[search_y][search_x + d[i]] == 1 && check != PASSABLE && visited[search_y][search_x + d[i]] == 0) {
      check = mazesolve(search_x + d[i],search_y);
      if(check == PASSABLE){
        //searched_id++;
        //Solution[search_y][search_x] = searched_id;
        if(searched_id > len)len = searched_id;
        return PASSABLE;
      }
    }
//    printf("maze = %d,vis = %d\n",Maze[search_y + d[i]][search_x],visited[search_y][search_x + d[i]]);

    if(search_y + d[i] < ny && search_y + d[i] >= 0 && Maze[search_y + d[i]][search_x] == 1 && check != PASSABLE && visited[search_y + d[i]][search_x] == 0){
      check = mazesolve(search_x,search_y + d[i]);
      if(check == PASSABLE){
        //searched_id++;
        //Solution[search_y][search_x] = searched_id;
        return PASSABLE;
      }
    }
  }
  //printf("none\n");
  Solution[search_y][search_x] = -1;
  searched_id--;
  return CANNOT_PASS;

}
