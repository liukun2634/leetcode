#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>
#include<algorithm>

using namespace std;

int solve(string s, string f){
    vector<int> dist(26, 26);
    unordered_set<int> set(f.begin(), f.end());
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            int next = 'a' + j;
            if(set.count(next)){
                int ma = max(i, j);
                int mi = min(i, j);
                int distance = min(ma - mi, 26 - ma + mi);
                dist[i] = min(dist[i], distance);
            }
        }
    }
    int res = 0;
    for(char c : s){
        res += dist[c - 'a'];
    }
    return res;
}

int T;
int main(){
    cin>>T;
    for(int t = 1; t <= T; t++){
        string s;
        string f;
        cin>>s;
        cin>>f;
        cout<<"Case #"<<t<<": "<<solve(s,f)<<endl;
    }
}

