#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

long long solve(vector<int>& happiness, vector<pair<int, int>>& intervals);

int T, D, N, K;
int main(){
    cin>>T;
    for(int t = 1; t <= T; t++){
        cin>>D>>N>>K;
        vector<int> happiness(N);
        vector<pair<int, int>> intervals(N);
        for(int i = 0; i < N; i++){
            cin>>happiness[i];
            cin>>intervals[i].first>>intervals[i].second;
        }
        cout<<"Case #"<<t<<": "<<solve(happiness, intervals)<<endl;
    }
}


//Solution 1: Use two multiset to save Kth active intervals and rest active intervals
long long solve(vector<int>& happiness, vector<pair<int, int>>& intervals){
    //Construct array that only put interval start and end
    vector<vector<int>> start(D + 1), end(D + 1);
    for(int i = 0; i < N; i++){
        start[intervals[i].first].push_back(happiness[i]);
        end[intervals[i].second].push_back(happiness[i]);
    }
    //compare set, multiset could save same value
    //Both active and rest cover current i
    multiset<int> active, rest;
    long long res = 0, sum = 0;
    for(int i = 1; i <= D; i++){
        //1. when start == i (insert active)
        for(int x : start[i]){
            active.insert(x);
            sum += x;
            if((int) active.size() > K){
                //remove smallest and add back to rest
                int value = *active.begin();
                sum -= value;
                rest.insert(value); 
                //Should use iterator rather than value, value will remove all same value
                active.erase(active.find(value));
            }
        }
        res = max(res, sum);
        //2. when end == i (remove active)
        for(int x : end[i]){
            //if x in active
            if(active.find(x) != active.end()){
                sum -= x;
                active.erase(active.find(x));
                if(not rest.empty()){
                    //here is rbegin(), move biggest to active
                    int value = *rest.rbegin();
                    sum += value;
                    active.insert(value);
                    rest.erase(rest.find(value)); 
                }
            } else{ //x in rest
                rest.erase(rest.find(x));
            }
        }
    }
    return res;
}

