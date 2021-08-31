### 300. 最长递增子序列

#### 题目

https://leetcode-cn.com/problems/longest-increasing-subsequence/

#### 思路1： 动态规划

最长递增子序列（Longest Increasing Subsequence，简写 LIS）是最经典的序列DP。

1、定义状态：**dp[i] 是以nums[i]结尾的最长递增子序列的长度**

2、状态转移方程：dp[i] = max(dp[i], dp[j] + 1) (当nums[i] > nums[j], j = 0...i -1)

3、初始状态：dp[i] = 1

4、最终结果：res = max(res, dp[i]) (i = 0...n-1)

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
         //1. 定义状态： 以nums[i]结尾的最长递增子序列的长度，
         //2. 初始状态:  默认为1
        vector<int> dp(n, 1);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++){
                //3. 状态转移方程
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        //4. 处理返回值
        int res = dp[0];
        for(int i = 1; i < n; i++) {
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n^2) 
空间复杂度：O(n)


#### 思路2:  辅助数组 +　二分查找

https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/zui-chang-shang-sheng-zi-xu-lie-dong-tai-gui-hua-2/

定义一个辅助数组：tails[k] 的值代表长度为 k+1 子序列 的尾部的最小元素值。

思路：在遍历计算每个 tails[k]，不断更新长度为 [1 , k] 的子序列尾部元素值，始终保持每个尾部元素值最小

区间中存在 tails[k] > nums[i] ： 将第一个满足 tails[k] > nums[i] 执行 tails[k] = nums[i]；因为更小的 nums[i] 后更可能接一个比它大的数字。

区间中不存在 tails[k]　>　nums[i] ： 意味着 nums[i] 可以接在前面所有长度的子序列之后，因此肯定是接到最长的后面（长度为 res ），新子序列长度为 res + 1。

因为 tails[k] 是单调递增的，所以可以用**二分搜索**。 **这里的 tails[k] 就像是维护的一个单调栈的思路，不过操作不是抛出，而是更新栈顶。**

初始状态：
tail[k]  = 0

最终结果
res = tail[k]中不为0的最大k值

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> tails(n, 0);

        int res = 0;
        int k = -1;
        for(int i = 0; i < n; i++){
            int left = 0, right = k;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(tails[mid] < nums[i]){
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if(left == k + 1) {    //不存在
               res++;
               k++;
               tails[left] = nums[i]; 
            } else {               //存在
               tails[left] = nums[i]; 
            }     
        }
        return res;
    }

};
```

优化：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> tails(n, 0);

        int res = 0;
        for(int i = 0; i < n; i++){
            int left = 0, right = res;
            while(left < right){
                int mid = left + (right - left) / 2;
                if(tails[mid] < nums[i]){
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            if(left == res)  res++;
            tails[left] = nums[i];  
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(nlogn) 
空间复杂度：O(n)

形象的理解：
https://labuladong.gitbook.io/algo/mu-lu-ye-2/mu-lu-ye-1/dong-tai-gui-hua-she-ji-zui-chang-di-zeng-zi-xu-lie