## 526. 优美的排列

### 题目

https://leetcode-cn.com/problems/beautiful-arrangement/

### 思路1： DFS 回溯算法

全排列，套用回溯算法的框架

```cpp
class Solution {
public:
    int res = 0, n = 0;
    int countArrangement(int _n) {
        n = _n;
        vector<int> nums(n, 0);
        vector<bool> visited(n, false);
        dfs(nums, 0, visited);
        return res;
    }

    void dfs(vector<int>& nums, int pos, vector<bool>& visited){
        //终止条件
        if(pos == n) {
            res++;
            return;
        }
        //遍历所有选择
        for(int i = 0; i < n; i++){
            if(visited[i] == false){
                int devident = max(pos + 1, i + 1);
                int devisor = min(pos + 1, i + 1);
                //满足要求当前位置的要求
                if(devident % devisor == 0){
                    visited[i] = true;
                    nums[pos] = i + 1;
                    //再计算判断下一位值
                    dfs(nums, pos + 1, visited);
                    visited[i] = false;
                }
            }
        }
        return;
    }
};
```

**注意：这里其实根本不需要真正的数组记录， nums可以去掉了**

**复杂度分析**

时间复杂度：O(n!)
空间复杂度：O(n)

#### 优化1: DFS + 状态压缩

由于 n 不超过15, 可以考虑用一个int来代替 visited 数组。

判断是否访问过 ((1 << (num - 1)) & visited) == 0 或者是 (((visited >> (num - 1)) & 1) == 0

```cpp
class Solution {
public:
    int countArrangement(int n) {
        return dfs(n, 1, 0);
    }

    int dfs(int n, int i, int visited){
        //终止条件
        if(i == n + 1) return 1;

        //遍历所有选择
        int res = 0;
        for(int num = 1; num <= n; num++){
            if(((1 << (num - 1)) & visited) == 0){
                //满足要求当前位置的要求
                if(i % num  == 0 || num % i == 0){
                    res += dfs(n, i + 1, visited | (1 << (num - 1)));  //值传递不需要置回来
                }
            }
        }
        return res;
    }
};
```
时间复杂度: O(n!)
空间复杂度：O(n) 栈空间

#### 优化2: DFS + 记忆化 

由于对于某一个pos，可能有相同的 mask 多次到达 （前 pos 部分的值相同，但顺序可能不同），所以增加一个cache 数组，优化时间。

```cpp
class Solution {
public:

    int countArrangement(int n) {
        vector<vector<int>> cache(n + 1, vector<int>(1 << (n + 1), -1));
        return dfs(n, 1, 0, cache);
    }

    int dfs(int n, int i, int visited, vector<vector<int>>& cache){
        //终止条件
        if(i == n + 1) return 1;

        if(cache[i][visited] != -1) return cache[i][visited];

        //遍历所有选择
        int res = 0;
        for(int num = 1; num <= n; num++){
            if(((visited >> (num - 1)) & 1) == 0){
                //满足要求当前位置的要求
                if(i % num  == 0 || num % i == 0){
                    res += dfs(n, i + 1, visited | (1 << (num - 1)), cache); 
                }
            }
        }
        cache[i][visited] = res;
        return res;
    }
};
```

时间复杂度: O(n!)
空间复杂度：O(n*2^n) cache 数组


#### 思路2： 动态规划 （状态压缩）

通过回溯算法，能够同样写出从底向上的动态规划

dp[i][state] 表示只考虑前 i 个数，且当前选择方案为 state 的所有方案数量。

```cpp
class Solution {
public:
    int countArrangement(int n) {
        //state 利用的是 第 0 为 到 n - 1 位，所以这里用的是 1<<n
        int mask = 1 << n;
        vector<vector<int>> dp(n + 1, vector<int>(mask));
        //初始状态
        dp[0][0] = 1;
     
        //只考虑前 i 位
        for(int i = 1; i <= n; i++){
            //所有状态
            for(int state = 0; state < mask; state++){
                //遍历数字
                for(int num = 1; num <= n; num++){
                    //必须要是当前位的state
                    if(((state >> (num - 1)) & 1) != 0) {
                        if(num % i == 0 || i % num == 0){
                            //对 1 << num - 1 取反
                            dp[i][state] += dp[i - 1][state & (~(1 << (num - 1)))];
                        }
                    }
                }
            }
        }
        return dp[n][mask - 1];
    }
};
```

#### 优化： 滚动数组 

由于i 只与 i - 1 相关，这里转换时候需要统计state 有多少个1 来作为i。

```cpp
class Solution {
public:
    int getCnt(int x) {
        int ans = 0;
        while (x != 0) {
            x -= (x & -x); // lowbit
            ans++;
        }
        return ans;
    }

    int countArrangement(int n) {
        //state 利用的是 第 0 为 到 n - 1 位，所以这里用的是 1<<n
        int mask = 1 << n;
        vector<int> dp(mask);
        //初始状态
        dp[0] = 1;
     
        //所有状态
        for(int state = 1; state < mask; state++){
            int i = getCnt(state);
            //遍历数字
            for(int num = 1; num <= n; num++){
                if(((1 << (num - 1)) & state) != 0 && (num % i == 0 || i % num == 0)){
                    //对 1 << num - 1 取反
                    dp[state] += dp[state & (~(1 << (num - 1)))];
                }
            }
        }
        return dp[mask - 1];
    }
};

```