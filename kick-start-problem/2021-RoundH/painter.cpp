#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<algorithm>

using namespace std;

int T;
unordered_map<char, int> times = {
    {'U', 0}, 
    {'R', 1}, {'Y', 1}, {'B', 1}, 
    {'O', 2}, {'P', 2}, {'G', 2}, 
    {'A', 3}, 
};

unordered_map<char, unordered_set<char>> colors ={
    {'O', {'R', 'Y'}},
    {'P', {'R', 'B'}},
    {'G', {'B', 'Y'}},
    {'A', {'R', 'Y', 'B', 'O', 'P', 'G'}}
};


int solve(string s, int n, int total){
    for(int i = 1; i < n; i++){
        if(s[i] == s[i - 1]){
            total = total - times[s[i]];
        } else if(colors[s[i]].count(s[i - 1])){
            total = total - times[s[i - 1]];
        } else if(colors[s[i - 1]].count(s[i])){
            total = total - times[s[i]];
        } else if(times[s[i - 1]] == 2 && times[s[i]] == 2) {
            total = total - 1;
        }
    }
    return total;
}


int main(){
    cin>>T;
    for(int t = 1; t <= T; t++){
        int n, total = 0;
        cin >> n;
        string s(n, ' ');
        for(int i = 0; i < n; i++){
            cin>>s[i];
            total += times[s[i]];
        }
        cout<<"Case #"<<t<<": "<<solve(s, n, total)<<endl;
    }
}

