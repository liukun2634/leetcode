#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool hasNoDevided(long long& a, vector<long long>& nums, int start, int n){
    for(int i = start; i < n; i = i + 2){
        if(nums[i] % a == 0) return false;
    }
    return true;
}

int main()
{
    int T, n;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin>>n;
        vector<long long> nums(n);
        cin>>nums[0];
        cin>>nums[1];
        long long a = nums[0], b = nums[1];
        for(int i = 2; i < n; i++){
            cin>>nums[i];
            if(i % 2 == 0) a = __gcd(nums[i], a);
            else  b = __gcd(nums[i], b);
        }
        if(hasNoDevided(a, nums, 1, n)) {
            cout<<a<<endl; 
        } else if(hasNoDevided(b, nums, 0, n)) {
            cout<<b<<endl; 
        } else {
            cout<<0<<endl;
        }
    }
    return 0;
}