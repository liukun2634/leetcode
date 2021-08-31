### 581. 最短无序连续子数组

#### 题目

https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/

#### 思路1：排序 + 双指针

先排序，然后对比每一位数字，左边第一位不相同到右边第一位不相同的距离即为最短连续无序子数组。

技巧： 
- 排序
- 双指针

**时间复杂度 O(nlogn)**
```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums)
    {
        vector<int> sortedNums(nums);
        sort(sortedNums.begin(), sortedNums.end());
        int left = -1, right = -1;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (sortedNums[i] != nums[i]) {
                left = i;
                break;
            }
        }
        for (int i = n - 1; i > 0; i--) {
            if (sortedNums[i] != nums[i]) {
                right = i;
                break;
            }
        }
        return left == -1 ? 0 : right - left + 1;
    }
};
```

#### 思路2： 双指针 + 利用排序数组的性质  

将整个数组分为三段, A, B, C.其中 A 是满足排序的小数组，C是满足排序的大数组，而B是要计算的无序数组。B满足任意一个数都大于A数组，任意一个数都小于C数组。

以寻找 B 的左边界 left 为例，由于 A 中是升序的， **A 中位置为 i 的元素一定是从该位置往后比较最小的那个数。** 如果i后面有一个数比位置i的数更小，那么说明位置i肯定不属于A。

那么从右向左遍历，用一个minn 记录 i 以后的元素中最小的元素，那么最左边满足不了比minn小的位置就是left。

同样，对于右边界right，从左向右遍历，用一个maxn 记录i之前的元素中最大的原因，那么最右边满足不了比maxn 大的位置就是right。

**技巧:**

- 双指针
- 数组有序性：位置为i的数，一定是从i位置开始中最小的值
- 数组遍历：如果i从1-n，那么n-i-1就是倒序的排序，从而可以一次排序
- 数组赋值：先将left 和right 设置为 -1 （而不是0 和 n-1）， return 时候可以方便比较left 和right 是否被赋值过。

**时间复杂度 O(n)** 
```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums)
    {
        int n = nums.size();
        int left = -1, right = -1;
        int maxn = INT_MIN, minn = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (maxn > nums[i]) {
                right = i;
            } else {
                maxn = nums[i];
            }

            if (minn < nums[n - i - 1]) {
                left = n - i - 1;
            } else {
                minn = nums[n - i - 1];
            }
        }

        return right == -1 ? 0 : right - left + 1;
    }
};
```



