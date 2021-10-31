## 33. 搜索旋转排序数组

### 题目

https://leetcode-cn.com/problems/search-in-rotated-sorted-array/

### 思路： 二分搜索

技巧： 根据 nums[0] 来判断 target 在旋转的左半部分，还是右半部分

然后再判断 nums[mid] 是处于左半部分还是在右半部分

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        if(nums[0] == target) return 0;

        while(left <= right){
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) return mid;
            if(nums[0] < target){
                //在旋转的左半部分
                //只有mid 在左半部分的时候，才增加left，否则一直减少right
                if(nums[mid] >= nums[0] && nums[mid] < target){
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else {
                //在旋转的右半部分
                //只有mid 在右半部分的时候，才减少right，否则一直增加left
                if(nums[mid] < nums[0] && nums[mid] > target){
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }

        return -1;
    }
};
```

**复杂度分析**

时间复杂度：O(logn)
空间复杂度：O(1)