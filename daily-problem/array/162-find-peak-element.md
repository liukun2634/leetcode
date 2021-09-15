## 162. 寻找峰值

### 题目

https://leetcode-cn.com/problems/find-peak-element/

### 思路：二分查找 

判断峰值的方向，如果是两边需要额外判断。

mid一定会返回，所以最后返回值不重要。

```C++
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.size() == 1) return 0;

        int left = 0, right = nums.size() - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(mid - 1 < 0) {
                if(nums[mid] > nums[mid + 1]) {
                    return mid;
                } else{
                    left = mid + 1;
                }
            } else if(mid + 1 >= nums.size()) {
                if(nums[mid] > nums[mid - 1]) {
                    return mid;
                } else{
                    right = mid - 1;
                }
            } else {
                if(nums[mid] > nums[mid + 1] && nums[mid] > nums[mid - 1]){
                    return mid;
                } else if(nums[mid] > nums[mid + 1] && nums[mid] < nums[mid - 1]){
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }
        return left;
    }
};
```
优化：

左闭右开, r 在范围内，就不需要额外的边界考虑。

```C++
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + (r - l)/2;
            if(nums[mid] < nums[mid + 1]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
};
```


**复杂度分析**

时间复杂度：O(logn)
空间复杂度：O(1)