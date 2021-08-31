## 5856. 完成任务的最少工作时间段

### 题目

https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/

该题是 881-救生艇 的不限制2个人的题。

### 思路1： 回溯算法

回溯 +剪枝

每个数找到一个合适的`rest`桶 放入，最后计算使用桶的个数。

剪枝条件： 1. 使用的桶的数目超过之前答案
          2. 前面一个桶的数目还是sessionTime

```C++
class Solution {
public:
    int res = INT_MAX;
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        sort(tasks.begin(), tasks.end(), greater<int>());
        vector<int> rests(n, sessionTime);
        backtrack(0, tasks, rests, sessionTime);
        return res;
    }
    
    void backtrack(int start, vector<int>& tasks, vector<int>& rests, int sessionTime){
        int n = tasks.size();
        if(start == n) {
            int days = 0;
            for(int rest : rests){
                if(rest < sessionTime){
                    days++;
                }
            }
            res = min(res, days);
            return;
        }
        
        for(int i = 0; i < n; i++){
            if(i != 0 && rests[i] == sessionTime && rests[i - 1] == sessionTime) return;
            if(i > res) return;
            if(tasks[start] <= rests[i]) {
                rests[i] = rests[i] - tasks[start];
                backtrack(start + 1, tasks, rests, sessionTime);
                rests[i] = rests[i] + tasks[start];
            }
            
        }
    }
};
```

**复杂度分析**

时间复杂度：O(n * k ^ n) - 剪枝
空间复杂度：O(n) 栈空间

### 思路2： 状态压缩 + 动态规划

由于 n 比较小， 可以使用状态压缩，来表明 第i个数是否已经放入。

这里涉及一个**子集枚举**的技巧，根据当前状态，枚举出所有可能子集，然后计算结果。 

```C++
//枚举 x 的所有子集
for(int i = x; i > 0; i = (i - 1) & x) {
  ...
}
```


dp[i] 表示 状态为i 时，需要的最少天数。


```C++
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        int m = (1 << n);
        //sums保存所有子集状态的和
        vector<int> sums(m, 0);
        for(int i = 1; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i & (1 << j)){
                    sums[i] = sums[i ^ (1 << j)] + tasks[j];
                }
            }
        }

    
        vector<int> dp(m, 1e9);
        dp[0] = 0;
        for(int i = 1; i < m; i++){
            for(int j = i; j ; j = (j - 1) & i){
                //如果子集和超过要求，则继续查看其他子集
                if(sums[j] > sessionTime) continue;
                dp[i] = min(dp[i], dp[i ^ j] + 1);
            }
        }
        return dp[m - 1];
    }
};
```






