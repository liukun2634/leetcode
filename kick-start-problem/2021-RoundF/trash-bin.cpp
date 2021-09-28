#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;
using LL = long long;

LL solve(int N, string s);

int T, N;
int main()
{
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        string s;
        cin >> s;
        cout << "Case #" << t << ": " << solve(N, s) << endl;
    }
}

//Solution: Use L and R represent distance to left trash bin and right trash bin
//result is long long 
LL solve(int N, string s)
{
    vector<int> L(N);
    vector<int> R(N);
    int left = -1;
    for(int i = 0; i < N; i++){
        if(s[i] == '0'){
            L[i] = left == - 1? N : i - left;
        } else {
            L[i] = 0;
            left = i;
        }
    }
    int right = -1;
    for(int i = N - 1; i >= 0; i--){
        if(s[i] == '0'){
            R[i] = right == - 1? N : right - i;
        } else {
            R[i] = 0;
            right = i;
        }
    }
    
    LL res = 0;
    for(int i = 0; i < N; i++){
        res += min(L[i], R[i]);
    }
    return res;
}

