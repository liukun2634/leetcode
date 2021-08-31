### 413. 等差数列划分

#### 题目

https://leetcode-cn.com/problems/arithmetic-slices/

#### 思路1： 双指针（快慢指针）

关键在于寻找等差数列的长度，然后可以根据长度计算得到子等差数列的个数。

假定长度为 len 的等差数列：
- 包括长度为3的子等差数列一共 len - 2 个
- 包括长度为4的子等差数列一共 len - 4 个
- 包括长度为5的子等差数列一共 len - 5 个
...
- 包括长度为 len 的子等差数列一共 1 个

所以长度为len 的等差数列一共有 (len - 2 + 1) * (len - 3 + 1) / 2  

那么可以通过快慢指针来找寻每个等差数列的长度。

```cpp
class Solution {
public:
    //思路：快慢指针
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) return 0;

        int slow = 0, fast = 2, res = 0;
        while(fast < nums.size()) {
            //更新slow 指针的条件：fast不再满足等比数列
            if(nums[fast] - nums[fast - 1] != nums[fast - 1] - nums[fast - 2]){
                int len = fast - slow; 
                res += (len - 1) * (len - 2) / 2;
                slow = fast - 1;
            }
            fast++;
        }

        //补充：还需要再判断一下是否因为fast到头而结束
        if(nums[fast - 1] - nums[fast - 2] == nums[fast - 2] - nums[fast - 3]){
                int len = fast - slow; 
                res += (len - 1) * (len - 2) / 2;
        }
        return res;
    }
};
```
注意： 最后可能因为fast 到达头而结束循环，但是该等差数列个数并没有计入，所以最后需要再次判断是否为等差数列到头结束。

这里因为最后如果相聚小于2 那么结果为0， 所以无需等差判断，直接增加结果。

**优化：**

```cpp
class Solution {
public:
    //思路：快慢指针
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) return 0;

        int slow = 0, fast = 2, res = 0;
        while(fast < nums.size()) {
            //更新slow 指针的条件：fast不再满足等比数列
            if(nums[fast] - nums[fast - 1] != nums[fast - 1] - nums[fast - 2]){
                int len = fast - slow; 
                res += (len - 1) * (len - 2) / 2;
                slow = fast - 1;
            }
            fast++;
        }

        //补充：如果fast因为到头而结束，需要再增加最末尾的等差数列
        res += (fast - slow - 1) * (fast - slow - 2) / 2;
        return res;
    }
};
```

### 思路2： 动态规划

问题是求子序列，考虑使用**动态规划**来解决。

状态定义: `dp[i]` 表示以 `nums[i]` 结尾的等差数列的个数。

状态转移方程： 
（1）当以`nums[i]`结尾满足等差数列时， 有 `dp[i] = dp[i-1] + 1`
（2）当以`nums[i]`结尾不满足等差数列时, 有 `dp[i] = 0` 

最终返回结果：是所有dp[i]之和

```cpp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        int res = 0;
        vector<int> dp(n, 0);
        for(int i = 2; i < n; i++){
            if(nums[i] - nums[i-1] == nums[i-1] - nums[i-2]){
                dp[i] = dp[i-1] + 1;
            }
            res+= dp[i];
        }
        return res;
    }
};
```

因为`dp[i]` 只与 `dp[i-1]` 有关， 所以可以使用滚动数组进行优化
