## 787. K 站中转内最便宜的航班

### 题目

https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/


### 思路1： Bellman Ford 

该题是有限制条件下的求图中的单源最短路径，可以考虑Bellman Ford来计算。先考虑用邻接矩阵的方式。

（因为有了额外的限制，Dijkstra 贪心求最短路径就不行了）

dp[i] 是从src 到 i 所需要的最短路径。

其实可以增加一个状态k，这里采用tmp的数组，实现滚动数组。

**1. 邻接矩阵保存**

```C++
class Solution {
public:
    const int MAX_N = INT_MAX / 2 - 1;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<int>> costs(n, vector<int>(n, MAX_N));
        for(auto flight : flights){
            costs[flight[0]][flight[1]] = flight[2];
        }

        vector<int> dp(n, MAX_N);
        dp[src] = 0;
        for(int limit = 0; limit < k + 1; limit++){
            vector<int> tmp(dp);
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(dp[j] > tmp[i] + costs[i][j]){
                        dp[j] = tmp[i] + costs[i][j];
                    }
                }
            }
        }

        return dp[dst] >= MAX_N ? -1 : dp[dst];
    }
};
```

**复杂度分析**

时间复杂度：O(n^2 * k)
空间复杂度：O(n^2)


### 思路2： BFS遍历 + 剪枝

BFS 拓扑遍历是最为通用的做法。

但这里需要剪枝才能，所以还是借用了动态规划的dp[i].

相比于bellman-ford, BFS 是通过一个队列的保存下一次遍历的相邻节点，而不是每次都遍历所有节点，性能上相比有提高。

**1. 邻接矩阵保存**

```C++
class Solution {
public:
    const int MAX_N = INT_MAX / 2 - 1;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<int>> costs(n, vector<int>(n, MAX_N));
        for(auto flight : flights){
            costs[flight[0]][flight[1]] = flight[2];
        }

        queue<pair<int, int>> q;
        q.push({src, 0});
        vector<int> dist(n, MAX_N); //dist用于剪枝，保存src到当前节点的距离最小值
        dist[src] = 0;

        for(int limit = 0; limit < k + 1; limit++){
            int sz = q.size();
            for(int i = 0; i < sz; i++){
                //cost 是limit步骤到当前节点的花销
                auto [cur, cost] = q.front();
                q.pop();
                //生成next
                for(int next = 0; next < n; next++){
                    if(cost + costs[cur][next] < dist[next]){
                        dist[next] = cost + costs[cur][next] ;
                        q.push({next, dist[next]});
                    }
                }

            }
        }
        return dist[dst] >= MAX_N ? -1 : dist[dst];
    }
};
```

**2. 邻接表保存**

```C++
class Solution {
public:
    const int MAX_N = INT_MAX / 2 - 1;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<pair<int, int>>> costs;
        for(auto flight : flights){
            costs[flight[0]].push_back({flight[1], flight[2]});
        }

        queue<pair<int, int>> q;
        q.push({src, 0});
        vector<int> dist(n, MAX_N); //dist用于剪枝，保存src到当前节点的距离最小值
        dist[src] = 0;

        for(int limit = 0; limit < k + 1; limit++){
            int sz = q.size();
            for(int i = 0; i < sz; i++){
                //cost 是limit步骤到当前节点的花销
                auto [cur, cost] = q.front();
                q.pop();
                //生成next
                for(auto& [next, nextCost] : costs[cur]){
                    if(cost + nextCost < dist[next]){
                        dist[next] = cost + nextCost;
                        q.push({next, dist[next]});
                    }
                }

            }
        }
        return dist[dst] >= MAX_N ? -1 : dist[dst];
    }
};
```