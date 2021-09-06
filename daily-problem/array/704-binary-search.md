## 704. 二分查找

### 题目

https://leetcode-cn.com/problems/binary-search/

### 思路1：标准二分查找 

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(nums[mid] < target){
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if(left >= nums.size() || nums[left] != target) return -1;
        return left;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：