## 1162. 地图分析

### 题目

https://leetcode-cn.com/problems/as-far-from-land-as-possible/

### 思路1：朴素BFS 

从每个海出发，找到最近的陆地 （BFS 标准模板），然后取距离。把最大的距离记为结果。

```C++
class Solution {
public:
    static constexpr int MAX_N = 100 + 5;
    int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool visited[MAX_N][MAX_N];
    int maxDistance(vector<vector<int>>& grid) {   
        int res = -1;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                 if(grid[i][j] == 0) {
                     int step = bfs(grid, i, j);
                     res = max(res, step);
                 }
            }
        }
        return res;
    }

    int bfs(vector<vector<int>>& grid, int i, int j) {
        memset(visited, 0, sizeof visited);
        queue<tuple<int, int, int>> q;
       
        q.push({i, j, 0});
        visited[i][j] = true;

        while(!q.empty()){
            int sz = q.size();
            for(int k = 0; k < sz; k++){
                auto [x0, y0, step] = q.front();
                q.pop();

                if(grid[x0][y0] == 1) { return step;}
                
                for (int t = 0; t < 4; t++) {
                    int x1 = x0 + direction[t][0];
                    int y1 = y0 + direction[t][1];
                    if( x1 < 0 || y1 < 0 || x1 >= grid.size() || y1 >= grid[0].size() || visited[x1][y1])
                        continue; 
                    visited[x1][y1] = true;
                    q.push({x1, y1, step + 1});
                }
            }
        }
        return -1; 
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：