### 576. 出界的路径数

#### 题目

https://leetcode-cn.com/problems/out-of-boundary-paths/

**归类为小岛问题**

#### 思路1：动态规划 

1、 定义状态: dp[i][j][k] 表示从坐标 (i, j) 在 k 步之内能够出界的路径数

2、转移方程：
   如果 (i，j) 移动一步就出界了，那么dp[i][j][k] ++;
   如果 (i, j) 移动到另外一个位置(x,y), 那么 dp[i][j][k] = dp[i][j][k] + d[x][y][k - 1]

3、初始状态为 0

4、返回值 dp[i][j][maxMove]

思考： 动态规划的实现，本质是将问题进行反向，原问题是让我们求从特定位置出发，出界的路径数量。实现时，我们则是从边缘在状态出发，逐步推导回起点的出界路径数量为多少。 

**技巧**

1. 二维数组移动，可以使用direction数组来保存移动方向
2. 动态规划如果进行边界判断，可以增加下标，这里需要增加两边的下标即 i 是 0 - m + 1, j 是 0 - n + 1
3. 注意：10e8 = 10^9，为什么选用的是 MOD = 10^9 + 7 是， 因为 % MOD 只要最后对保存的结果整除后，就能够保证 两个值MOD 后的值相加不会超过int， 两个 MOD 后的值相乘不会超过 long long


```cpp
class Solution {
public:
    const int MOD = 1000000007;
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove + 1)));
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for(int k = 1; k <= maxMove; k++){
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    for(auto direction : directions) {
                        int x = i + direction[0];
                        int y = j + direction[1];
                        if (x < 0 || x >= m || y < 0 || y >= n){
                            dp[i][j][k] = (dp[i][j][k] + 1) % MOD;
                        } else {
                            dp[i][j][k] = (dp[i][j][k] + dp[x][y][k - 1]) % MOD;
                        }
                    }
                }
            }
        }
        return dp[startRow][startColumn][maxMove];
    }
};
```

**复杂度分析**

时间复杂度：O(mn * maxMove)
空间复杂度：O(mn * maxMove)


**状态压缩** 

由于k 只于 k-1 有关，所以可以考虑状态压缩。但需要有个temp 数组在遍历 k 的时候 存储中间状态，然后最后在赋值给dp。

#### 思路2：记忆化搜索

cache + DFS

要点：

- 函数调用之间，可使用全局变量
- cache 函数 初始化为 -1 标记为没有缓存

```cpp
class Solution {
public:
    const int MOD = 1000000007;
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m, n;
    int findPaths(int _m, int _n, int maxMove, int startRow, int startColumn) {
        m = _m, n = _n;
        vector<vector<vector<int>>> cache(m, vector<vector<int>>(n, vector<int>(maxMove + 1, -1))); 
        return dfs(maxMove, startRow, startColumn, cache);
    }

    int dfs(int move, int i, int j, vector<vector<vector<int>>>& cache){
        //终止条件1：到达边界
        if (i < 0 || j < 0 || i >= m || j >=n ) return 1;
        //终止条件2：没有步数了
        if (move == 0) return 0; 
        //终止条件3：存在cache
        if(cache[i][j][move] != -1) return cache[i][j][move];

        int res = 0;
        for (auto dir : directions) {
            res += dfs(move - 1, i + dir[0], j + dir[1], cache);
            res %= MOD;
        }
        cache[i][j][move] = res;
        return res;
    }
};
```

