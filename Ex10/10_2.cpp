#include <iostream>

using namespace std;

static const int card_num = 13;
static const int max_cost = 50;
int main(){
  int power[card_num+1] = {};
  int cost[card_num+1] = {};
  int dp[card_num+1][max_cost+1] = {{}};
  int ans[card_num+1] = {};
  int c = 0;
  for(int i = 1;i <= card_num;i++){
    cin >> power[i] >> cost[i];
  }

  //cout << &dp[0][0] << " " << &cost[4] << endl;

  for(int i = 1;i <= card_num;i++){
    for(int j = 1;j <= max_cost;j++){
      //cout << "i,j = " << i << ", " << j << endl;
      //cout << dp[i-1][j-cost[i]] + power[i] << ", " << dp[i-1][j] << endl;;
      if(j >= cost[i]) dp[i][j] = max(dp[i-1][j-cost[i]] + power[i],dp[i-1][j]);
      else dp[i][j] = dp[i-1][j];
    }
  }


  for(int i = 0;i <= card_num;i++){
    cout << power[i] << ' ';
    for(int j = 0;j <= max_cost;j++){
      cout << dp[i][j] << ' ';
    }
    cout << endl;
  }



  for(int i = card_num;i >= 1;i--){
    if(ans[i] == 1) cout << "Card " << i << " (pow: " << power[i] << ", cost: " << cost[i] << ") is used.\n" << endl;
    else cout << "Card " << i << " is not used.\n" << endl;
  }
  cout << "My Besk deck has " << c << " cards (Cost: " << max_cost << ", Power: " << dp[card_num][max_cost] << ')' << endl;
}
