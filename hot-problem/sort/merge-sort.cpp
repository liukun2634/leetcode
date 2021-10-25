#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;


void merge(vector<int>& nums, int left, int mid, int right){
    vector<int> temp1(nums.begin() + left, nums.begin() + mid + 1); //注意这里需要到mid + 1, 不放入mid + 1
    vector<int> temp2(nums.begin() + mid + 1, nums.begin() + right + 1); //注意这里需要到right + 1

    int index1 = 0, index2 = 0;

    //避免最后的index判断, 如果不写就需要对index 额外判断
    temp1.push_back(INT_MAX);
    temp2.push_back(INT_MAX);
    for(int i = left; i <= right; i++){
        if(temp1[index1] < temp2[index2]){
            nums[i] = temp1[index1++];
        } else {
            nums[i] = temp2[index2++];
        }
    }
}


void merge_sort(vector<int>& nums, int left, int right){
    if(left >= right) return;

    int mid = left + (right - left) / 2;
    merge_sort(nums, left, mid);
    merge_sort(nums, mid + 1, right);

    //后序遍历
    merge(nums, left, mid, right);
}


int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    merge_sort(nums, 0, nums.size() - 1);

    for (int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }

    return 0;
}