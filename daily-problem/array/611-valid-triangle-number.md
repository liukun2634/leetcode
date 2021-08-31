### 611. 有效三角形的个数

#### 题目

https://leetcode-cn.com/problems/valid-triangle-number/

该题充分利用数组中的几个技巧，排序，二分，双指针。

#### 思路1： 排序 + 二分搜索

二分搜索之前一定要保证数组是有序的，先进行排序。

具体思路就是固定两个小边，通过两个小边的和 `target`，向数组右边去找另一条边。这时候就可以通过二分，一旦大于等于这两个小边的和就不符合，所有小于 `target` 的值都可以作为第三条边。（这里用pos 记录最右满足条件的边的下标，然后下标相减就能计算总共多少条第三条边）

**技巧**
 - 二分法（增加了一个pos 去记录最右小于`target`的位置, 从而保证返回的下标是有效的） 
 
二分法还需要加强练习

```cpp
class Solution {
public:
    int triangleNumber(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int k = binary_search(nums, j + 1, n - 1, nums[i] + nums[j]);
                res += k - j;
            }
        }
        return res;
    }

    int binary_search(vector<int>& nums, int left, int right, int target)
    {
        int pos = left - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                pos = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return pos;
    }
};

```

#### 思路2： 排序 + 双指针

这个思路的关键在于**固定的是最大的边`i`**。先排序，遍历最大边`i`，然后在最大边的左边，通过双指针 `left`和`right`，寻找满足`nums[i] < nums[left] + nums[right]`的所有情况。 如果满足，那么记录满足条件的所有边，次大边 `right`就可以--。如果不满足，说明`left`太小，需要++。 （其实是滑动窗口的思路。

**技巧：**
- 固定的是最大的边
- 排序后，滑动窗口

```cpp
class Solution {
public:
    int triangleNumber(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        for (int i = 2; i < n; i++) {
            int left = 0, right = i - 1;
            while (left < right) {
                if (nums[left] + nums[right] > nums[i]) {
                    res += right - left;
                    right--;
                } else {
                    left++;
                }
            }
        }
        return res;
    }
};
```