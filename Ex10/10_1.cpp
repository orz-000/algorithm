#include<iostream>

using namespace std;

static const int INF = 99999;
static const int n = 183;
static const int coins = 4;
int main(){

  int dp[n+25] = {};
  for(int i = 0; i < n;i++) dp[i] = INF;
  int coin[coins] = {1,5,10,25};
  for(int i = 0;i < coins;i++) dp[coin[i]-1] = 0;



  for(int i = 0;i < n;i++){
    for(int j = 0;j < coins;j++){

  /*    for(int k = 0;k < n;k++){
          cout << dp[k] << ' ';
        }
      cout << endl;
*/
      if(dp[i+coin[j]] > dp[i] + 1) dp[i+coin[j]] = dp[i] + 1;
    }
  }
  cout << "Totally, you used " << dp[n-1] << " coins for " << n << "cents." << endl;
}
