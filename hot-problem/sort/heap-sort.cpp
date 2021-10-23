#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void sink(vector<int>& nums, int idx, int N)
{
    while ((idx * 2 < N && nums[idx * 2] < nums[idx]) || ( idx * 2 + 1 < N && nums[idx * 2 + 1] < nums[idx])) {
        if (idx * 2 + 1 >= N || nums[idx * 2] < nums[idx * 2 + 1]) {
            swap(nums[idx * 2], nums[idx]);
            idx = idx * 2;
        } else {
            swap(nums[idx * 2 + 1], nums[idx]);
            idx = idx * 2 + 1;
        }
    }
}



void heap_sort(vector<int>& nums)
{
    int n = nums.size();
    //1. 建堆过程 O(n)
    for (int i = n / 2; i > 0; i--) {
        sink(nums, i, n);
    }
    //2. 不断删除堆顶到末尾, 缩减元素，从而排序 
    // O(nlogn) 
    int last = n - 1;
    for(int i = n - 1; i > 0; i--){
        swap(nums[1], nums[i]);
        sink(nums, 1, i);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n + 1);
    //下标从 1 开始
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    heap_sort(nums);

    for (int i = 1; i <= n; i++) {
        cout << nums[i] << " ";
    }

    return 0;
}