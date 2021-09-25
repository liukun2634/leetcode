#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
using namespace std;


int solve(vector<vector<int>>& plates);
// void backtrack(vector<vector<int>>& plates, vector<int>& start, int count, int sum, int& res);

int n, m, p;
int main() {
    int t;
    cin>>t;
    for(int k = 1; k <= t; k++){
        cin>>n>>m>>p;
        vector<vector<int>> plates(n, vector<int>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin>>plates[i][j];
            }
        }
        cout<<"Case #"<<k<<": "<<solve(plates)<<endl;
    }
}


//DP : similar with 0-1 Knapsack Problem
int solve(vector<vector<int>>& plates){
    //DP denotes the maximum sum that can be obtained using the first i stacks when we need to pick j plates in total
    vector<vector<int>> dp(n + 1 , vector<int>(p + 1, 0));
    
    //pre-calculete sum
    vector<vector<int>> sum(n, vector<int>(m + 1, 0));
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= m; j++){
            sum[i][j] = sum[i][j - 1] + plates[i][j - 1];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= p; j++){
            //pick x from stack i into result 
            for(int x = 0; x <= min(j, m); x++){
                dp[i][j] = max(dp[i][j], sum[i - 1][x] + dp[i - 1][j - x]);
            }
        }
    }

    return dp[n][p];
}


// Backtrack: TLE when 1 ≤ N ≤ 50.
// int solve(vector<vector<int>>& plates){
//     int res = 0;
//     vector<int> start(n, 0);
//     for(int i = 0; i < n; i++){
//         start[i]++;
//         backtrack(plates, start, 1, plates[i][0], res);
//         start[i]--;
//     }
//     return res;
// }

// void backtrack(vector<vector<int>>& plates, vector<int>& start, int count, int sum, int& res){
//     if(count == p){
//         res = max(sum, res);
//         return;
//     }

//     for(int i = 0; i < n; i++){
//         if(start[i] < m) {
//             int j = start[i];
//             start[i]++;
//             backtrack(plates, start, count + 1, sum + plates[i][j], res);
//             start[i]--;
//         }
//     }
// }



