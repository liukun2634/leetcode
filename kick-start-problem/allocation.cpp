#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
using namespace std;

int solve(vector<int>& costs, int budget, int n);

int main(){
    int m;
    cin>>m;
    for(int k = 1; k <= m; k++){
        int n, budget;
        cin>>n>>budget;
        vector<int> costs(n);        
        vector<int> buckets(1001, 0);
        for(int i = 0; i < n; i++){
            cin>>costs[i];
            buckets[costs[i]]++;
        }
        cout<<"Case #"<<k<<": "<<solve(buckets, budget, n)<<endl;
    }
} 

//Greedy: buy small one by one as much as posible
//Using counting sort
int solve(vector<int>& buckets, int budget, int n){
    int res = 0;
    for(int i = 1; i < 1001; i++){
        while(buckets[i] > 0) {
            buckets[i]--;
            if(budget - i >= 0){
                res++;
                budget -= i;
            } else{
                return res;
            }
        }
    }
    return res;
}

//DP: TLE when B is 10^5
// int solve2(vector<int>& costs, int budget, int n){
//     vector<int> dp(budget + 1, 0);
//     for(int i = 0; i < n; i++){
//         for(int j = budget; j >= 0; j--){
//             if(costs[i] <= j){
//                 dp[j] = max(dp[j - costs[i]] + 1, dp[j]);
//             } 
//         }
//     }
//     return dp[budget];
// }



