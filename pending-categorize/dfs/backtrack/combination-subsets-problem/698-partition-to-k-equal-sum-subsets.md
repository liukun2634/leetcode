## 698. 划分为k个相等的子集

### 题目

https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/

该题是 将数组分为两个子集的 扩展，前面是转换成 0-1 背包问题，使用动态规划解决。(其实也可以使用回溯 + 记忆化)。那么该题主要就通过回溯 + 不同选择(选择项增多到了k项) 来解决了。

要点1：要求把数组分为k个子集，每个子集的和相同。这点其实按时的是，所有数字的和为sum， 每个子集的和就为 sum / k。

### 思路1：回溯思路 - 数字视角

题目的问题其实就是把将 n 个数字分配到 k 个桶里，我们可以有两种视角：

第一种是这 n 个数字的视角，对于每个数字都要选择进入到 k 个桶中的某一个。**对于每个数字，遍历 k 个桶，尝试放入每个桶，然后再看下一个数字。**


技巧：
- 预处理数组，保证大的数在前面，这样先占掉位置，后面的判断就会减少。

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int num : nums) {
            sum += num;
        }
        if(sum % k != 0) return false;
        int target = sum / k;
        //对nums 要从大到小预处理，否则会超时
        sort(nums.begin(), nums.end(), greater<int>());
        //记录k个子集中每个子集的和
        vector<int> subsets(k, 0);
        return backtrack(0, nums, k, subsets, target);
    }

    bool backtrack(int pos, vector<int>& nums, int k, vector<int>& subsets, int target){
        //每个数字都找到了合适的子集放入
        if(pos == nums.size()) return true;

        for(int i = 0; i < k; i++){
            //只能找寻能放入的子集
            if(subsets[i] + nums[pos] <= target){
                subsets[i] += nums[pos];
                //递归看下一个数字
                if(backtrack(pos + 1, nums, k, subsets, target)) return true;
                subsets[i] -= nums[pos];
            }
        }
        return false;
    }
};
```

**复杂度分析**

时间复杂度：O(k^n) n 个数字，每个数字有k中选择
空间复杂度：O(n)

### 思路2：回溯思路 - 桶的视角

另一种视角就是从桶的角度来考虑，每个桶遍历 nums 中的 n 个数字，然后选择是否将当前遍历到的数字装进自己这个桶里


这里先管好第k个桶再管下一个，所以start 记录的是 i 开始遍历的位置

bucket 记录的是当前桶的值，target 是目标值 sum/k

used 记录已经使用过的数字


```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for(int num : nums) {
            sum += num;
        }
        if(sum % k != 0) return false;
        int target = sum / k;
        //记录数字使用情况
        vector<bool> used(nums.size(), false);
        return backtrack(0, nums, k, used, 0, target);
    }

    bool backtrack(int start, vector<int>& nums, int k, vector<bool>& used, int bucket, int target){
        if(k == 0) return true;
        if(target == bucket) {
            //这里是要点：一个桶装满了，继续装下一个桶
            return backtrack(0, nums, k - 1, used, 0, target);
        }

        for(int i = start; i < nums.size(); i++){
            //保证桶能装的下，才放入
            if(used[i] == false && bucket + nums[i] <= target) {
                used[i] = true;
                //下一个直接从i + 1 开始
                if(backtrack(i + 1, nums, k, used, bucket + nums[i], target)) return true;
                used[i] = false;
            }
        }
        return false;
    }
};
```
**复杂度分析**

时间复杂度：O(k * 2^n)  k个桶，遍历 n 个数字，每个数字都有2种
空间复杂度：O(n)


该思路的时间复杂度相比较第一种要小很多 （当 k 比较大的时候）。

通过将 used 转换成 int state，实现回溯 + 状态压缩 

进而增加记忆化搜索，更之，可以转换使用动态规划来解决。



### 思路3： 回溯思路2 + 状态压缩 

### 思路4： 回溯思路2 + 状态压缩 + 记忆化搜索

### 思路5： 动态规划

https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/solution/hua-fen-wei-kge-xiang-deng-de-zi-ji-by-leetcode/

dp[state] 记录在该state 下 是否能够满足题意 （true / false)

stateSum[state] 在当前state 下 取得的 和