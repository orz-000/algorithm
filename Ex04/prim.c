
void prim(int cur){

  while(1){
    min = INF;
    u = -1;
    for(i = 0;i < n;i++){
      if( d[i] < min && visited[i] != 1){
        min = d[i]
        u = cur * i;
      }
    }
    if( u == -1) break;
    visited[cur] = 1;

    for(v = 0;v < n;v++){
      if(visited[v] != 1 && array[u][v] != INF){
        if(array[u][v] < d[v]){
          d[v] = array[u][v];
          p1[v] = u;
        }
      }
    }
  }
}
