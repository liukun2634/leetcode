#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;

int solve(vector<int>& nums);
int f(vector<int>& nums, int diff);

int N, K;
int main(){
    int T;
    cin>>T;
    for(int t = 1; t <= T; t++){
        cin>>N>>K;
        vector<int> nums(N);
        for(int i = 0; i < N; i++){
            cin>>nums[i];
        }
        cout<<"Case #"<<t<<": "<<solve(nums)<<endl;
    }
}


//Binary search
int solve(vector<int>& nums) {
    int left = 1, right = 0;
    for(int num : nums){
        right = max(right, num);
    }

    while(left <= right){
        int mid = left + (right - left) / 2;
        if(f(nums, mid) <= K){
            right = mid - 1;
        } else{
            left = mid + 1;
        }
    }

    return left;
}

int f(vector<int>& nums, int diff){
    int count = 0;
    for(int i = 1; i < N; i++){
        count += ((nums[i] - nums[i - 1] + diff - 1) / diff) - 1;
    }
    return count;
}


//Priority Queue: Set 2 WA
//continuous halving of the maximum difference is sub-optimal.

// int solve(vector<int>& nums){
//     priority_queue<int> pq;

//     for(int i = 1; i < n; i++){
//         pq.push(nums[i] - nums[i - 1]);
//     }

//     while(k > 0){
//         int top = pq.top();
//         pq.pop();
//         //edge case
//         if(top == 1) return 1;

//         if(top % 2 == 0){
//             pq.push(top / 2);
//             pq.push(top / 2);
//         } else {
//             pq.push(top / 2);
//             pq.push(top / 2 + 1);
//         }
//         k--;
//     }
//     return pq.top();
// }