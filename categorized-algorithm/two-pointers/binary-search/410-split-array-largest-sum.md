### 410. 分割数组的最大值

#### 题目

https://leetcode-cn.com/problems/split-array-largest-sum/

#### 思路1： 二分搜索

关键要变换一下思路：限制一个最大子数组和max，来反推最大子数组和为 max 时，至少可以将 nums 分割成几个子数组。

所以题目其实就是 题目1011。

推算复杂度, 因为 f 函数的复杂度 O(N) , 二叉查找的复杂度 O(logN),  总的时间复杂度O(N * log S)

```cpp
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int left = 0, right = 0;
        for(auto num : nums) {
            left = max(left, num);
            right += num;
        }

        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(f(nums, mid) > m) {
                left = mid + 1; 
            } else {
                right = mid - 1;
            }
        }
        return left;
    }

    //x 固定连续子数组最大值
    //f(x) 可以分割的子数组数
    int f(vector<int>& nums, int max) {
        int count = 1; //count从1开始
        int sum = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(sum + nums[i] > max) {
                count++;
                sum = 0;
            }
            sum += nums[i];
        }
        return count;
    }
};

```



#### 思路2： 动态规划