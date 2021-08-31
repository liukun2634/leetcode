### 1583. 统计不开心的朋友

#### 题目

https://leetcode-cn.com/problems/count-unhappy-friends/

#### 思路： 模拟

技巧：预处理数组 

首先，因为想要快速的知道`x` 与 `y` 的亲近程度，所以通过预处理 `perferences` 数组，用一个哈希表存储 `x` 与 `y` 的亲近程度下标。有两种优化方法：
- 使用一个`unordered_map<string, int>`， string 存储的是 `"xy"` 的字符对。
- 因为下标是连续的，且范围为0..n -1, 可以使用一个二维数组`order`保存

其次，想要快速知道一个 `x`，`u` 所配对的朋友，可以通过一个一维数组 `match`存储其对应的朋友 `y`, `v`。

最后，按照题目要求遍历每个朋友，判断他是否开心。

```cpp
class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        //1. 预处理preference
        vector<vector<int>> order(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n - 1; j++){
                order[i][preferences[i][j]] = j;
            }
        }

        //2. 预处理pairs
        vector<int> match(n);
        for(vector<int> pair : pairs){
            match[pair[0]] = pair[1];
            match[pair[1]] = pair[0];
        }

        //3. 遍历每个朋友，判断是否开心
        int res = 0;
        for(int x = 0; x < n; x++){
            int y = match[x];
            for(int u = 0; u < n; u++) {
                int v = match[u];
                if(x != u && x != v && y != u && y != v){
                    if(order[x][u] < order[x][y] && order[u][x] < order[u][v]){
                        res++;
                        break; //x不开心直接跳出循环
                    }
                }
            }
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n^2)