#include <iostream>

#define INF  99999

using namespace std;

int n;
int i,j;
int p1[12][12] = {};
int p2[12] = {};
int p3[12] = {};
int rank[12] = {};
int d[12][12] = {};
int mint = INF;
int u,v;
int array[100][100][100] = {{{}}};
int visited[12][12] = {};
int end[12] = {};
int sum = 0;

//int *p;
//int *rank;
//p = (int *)malloc(sizeof(int) * n);
//rank = (int *)malloc(sizeof(int) * n);

void makeset(int );
int findset(int );
bool same(int ,int);
void link(int,int);
void unite(int,int);
int boruvska();
void prim(int,int);


int main(){
  int k;
  array[0][0][0] = 10;
  //scanf("%d",&n);
  cin >> n;
  for(i = 0;i < n;i++){
    for(j = 0;j < n;j++){
      //scanf("%d",&array[0][i][j]);
      cin >> array[0][i][j];
      for(k = 1;k < n;k++){
        array[k][i][j] = array[0][i][j];
      }
    }
  }

  /*for(i = 0;i < n;i++){
  for(j = 0;j < n;j++){
  for(k = 0;k < n;k++){
  cout << array[i][j][k]; //printf("%d ",array[i][j][k]);
  cout << " ";
}
cout << endl;//printf("\n");
}
cout << endl;//printf("\n\n");
}*/

cout << endl;
cout << "sum == " << boruvska() << endl;  //printf("\nsum == %d\n",boruvska());

return 0;
}




void prim(int set,int c){
  //printf("set = %d\n",set);
//  cout << set << endl;
  cout << c << endl;;
  mint = INF;
  u = -1;
  for(i = 0;i < n;i++){
    if( d[set][i] < mint && visited[set][i] != 1){
      if(findset(i) != findset(p1[set][i]) || c == 1){
        mint = d[set][i];
        u = i;
      }
    }
  }
  if( u == -1){
    end[set] = 1;
    return;
  }
  visited[set][u] = 1;
  p3[u] = p1[set][u];
  //printf("set = %d,u = %d,p[u] = %d\n",set,u,p1[set][u]);
  cout << "set = " << set << ", u = " << u << ", p[u] = " << p1[set][u] << ", d[set][u] = "<< d[set][u] << endl;
  sum += d[set][u];
  d[set][u] = 0;
  unite(u,p1[set][u]);

  for(v = 0;v < n;v++){
    if(visited[set][v] != 1 && array[set][u][v] != INF && findset(u) != findset(v)){
      //printf("aa\n");
      if(array[set][u][v] < d[set][v]){
        //cout << "aa" << endl;
        d[set][v] = array[set][u][v];
        p1[set][v] = u;
        //  printf("p1[set][v] = %d,set = %d,v = %d\n",p1[set][v],set,v);
      }
    }
  }
}

int boruvska(){
  bool flag = false;


  for(i = 0;i < n;i++){
    for(j = 0;j < n;j++){
      p1[i][j] = -1;
      d[i][j] = INF;
    }
  }
  for(i = 0;i < n;i++){
    makeset(i);
    d[i][i] = 0;
    p3[i] = -1;
  }
  p3[0] = 0;
  int c = 0;
  while(1){
    c++;
    for(j = 0;j < n;j++){
      //printf("j = %d\n",j);
      prim(j,c);
    }
    for(i = 0;i < n;i++){
      if(end[i] != 1) break;
      flag = true;
    }
    if(flag) break;
  }

  return sum;
}



void makeset(int x){
  p2[x] = x;
  rank[x] = 0;
}

int findset(int x){
  if( x != p2[x] ){
    p2[x] = findset(p2[x]);
  }
  return p2[x];
}

bool same(int x,int y){
  return findset(x) == findset(y);
}

void link(int x,int y){
  if( rank[x] > rank[y] ){
    p2[y] = x;
  }
  else {
    p2[x] = y;
    if( rank[x] == rank[y]){
      rank[y]++;
    }
  }
}


void unite(int x,int y){
  link(findset(x),findset(y));
}
