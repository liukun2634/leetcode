### 743. 网络延迟时间

#### 题目
https://leetcode-cn.com/problems/network-delay-time/

#### 思路1： Dijkstra算法

从节点k出发，计算到达所有节点的最短距离。然后遍历k到所有节点的距离，取最大值作为最长网络延迟。

技巧：
1. 图的保存使用邻接矩阵 （因为节点是1-n），当然也可以使用邻接表。
2. 用dist[y]表示k达到y最短距离。通过遍历邻接矩阵，不断减小
3. 将节点-1转换为下标存储

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {        
        //初始化邻接矩阵
        vector<vector<int>> g(n, vector<int>(n, INT_MAX/2));
        for(int i = 0; i < times.size(); i++) {
            g[times[i][0]-1][times[i][1]-1] = times[i][2];
        }

        //计算k到各个节点的最短距离 O(n^2))
        vector<bool> visited(n, false);
        vector<int> dist(n, INT_MAX/2);
        dist[k-1] = 0;
        for(int i = 0; i < n; i++) {
            int x = -1;
            //寻找新的距离最短的节点x
            for(int y = 0; y < n; y++) {
                if(visited[y] == false && (x == -1 || dist[y] < dist[x])) {
                    x = y;
                }
            }
            visited[x] = true;
            //更新所有跟x相邻节点的距离
            for(int y = 0; y < n; y++) {
                dist[y] = min(dist[y], dist[x] + g[x][y]);
            }
        }

        //返回距离k的最大的距离
        int res = -1;
        for(int i = 0; i < n; i ++) {
            res = max(res, dist[i]);
        }
        return res == INT_MAX/2? -1 : res;
    }
};
```
#### 思路2： Dijkstra算法 + 最小堆

#### 思路3： Floyd（邻接矩阵）

#### 思路4： Bellman Ford（类 & 邻接表）

#### 思路5： SPFA（邻接表）


