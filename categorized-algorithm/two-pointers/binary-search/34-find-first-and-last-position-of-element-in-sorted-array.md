### 34. 在排序数组中查找元素的第一个和最后一个位置

#### 题目

https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#### 思路1：二分搜索

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        ans.push_back(left_bound(nums, target));
        ans.push_back(right_bound(nums, target));
        return ans;
    }

    int left_bound(vector<int>& nums, int target){
        int left = 0, right = nums.size() - 1;
        while(left <= right) {
            int mid = left + (right - left) /2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if(left >= nums.size() || nums[left] != target) 
            return -1;
        return left;
    }

    int right_bound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = right - 1;
            }
        }
        if(right < 0 || nums[right] != target) 
            return -1;
        return right;
    }
};

```
