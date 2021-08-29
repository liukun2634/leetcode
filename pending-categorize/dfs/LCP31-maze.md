## LCP 31. 变换的迷宫

### 题目

https://leetcode-cn.com/problems/Db3wC1/

### 思路1： DFS + cache

**技巧**

```C++
class Solution {
public:
    int n, m, k;
    //cache 存储到达不了终点的状态
    //状态 由当前步数 step，坐标 x, y 和 是否使用卷轴 used1 和 used2 决定
    unordered_set<string> cache;
    int dirs[5][2] = {{1, 0}, {0, 1}, {0, 0}, {-1, 0}, {0 , -1}};
    bool escapeMaze(vector<vector<string>>& maze) {
        k = maze.size();
        n = maze[0].size();
        m = maze[0][0].size();
        return dfs(maze, 0, 0, 1, false, false, 0, 0);
    }
    
    bool dfs(vector<vector<string>>& maze, int x, int y, int steps, bool used1, bool used2, int x_empty, int y_empty){
        int dist = (n - 1 - x) + (m - 1 - y);
        //剪枝
        if(dist + steps > k ) return false;

        //查看cache
        string key = to_string(steps) + "," +  to_string(x) + "," + to_string(y) + ","+ to_string(used1) + "," + to_string(used2);
        if(cache.count(key)) return false;

        for(auto dir : dirs){
            int x_next = x + dir[0];
            int y_next = y + dir[1];
            if(x_next < 0 || x_next >= n || y_next < 0 || y_next >= m) continue;

            //返回满足条件
            if(x_next == n - 1 && y_next == m - 1) {
                return true;
            }

            //下个坐标判断
            if(maze[steps][x_next][y_next] == '#'){
                if(used2 && x_empty == x_next && y_empty == y_next) {
                    if(dfs(maze, x_next, y_next, steps + 1, used1, used2, x_empty, y_empty)) return true;
                } 
                if(!used1) {
                    if(dfs(maze, x_next, y_next, steps + 1, true, used2, x_empty, y_empty)) return true;
                }
                if(!used2) {
                    if(dfs(maze, x_next, y_next, steps + 1, used1, true, x_next, y_next)) return true;
                }
            } else {
                if(dfs(maze, x_next, y_next, steps + 1, used1, used2, x_empty, y_empty)) return true;
            }  
        }
        //该位置到达不了终点，计入cache
        cache.insert(key);
        return false;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：