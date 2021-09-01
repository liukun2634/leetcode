## 210. 课程表 II

### 题目

https://leetcode-cn.com/problems/course-schedule-ii/

### 思路1：DFS + 图的后序遍历

拓扑排序 是图的后序遍历翻转的结果。

这里利用 课程表 1 结构，只是在最后将结果记录返回值。最后对返回值 `reverse` 就是拓扑排序的结果。

```C++
class Solution {
public:
    vector<int> res;
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //构造邻接表
        vector<vector<int>> graph(numCourses);
        for(auto prerequisite : prerequisites){
            int from = prerequisite[1];
            int to = prerequisite[0];
            graph[from].push_back(to);
        }

        //visited 记录所有的节点访问情况
        vector<bool> visited(numCourses, false);
        //path 记录当前这个路径下访问情况, 类比于正常visited
        vector<bool> path(numCourses, false);
        for(int i = 0; i < numCourses; i++){
              //存在环
              if(!traverse(graph, i, visited, path)) {
                  res.clear();
                  return res;
              }
        }
        //将后序遍历翻转就是拓扑排序
        reverse(res.begin(), res.end());
        return res;
    }

    bool traverse(vector<vector<int>>& graph, int s, vector<bool>& visited, vector<bool>& path){
        //存在环
        if(path[s]) return false;

        if(visited[s]) return true;

        visited[s] = true;
        path[s] = true;
        for(int next : graph[s]){
            if(!traverse(graph, next, visited, path)) return false;
        }
        path[s] = false;
        //后序遍历
        res.push_back(s);
        return true;
    }
};
```

**复杂度分析**

时间复杂度：O(n+m) 由于有visited，每个节点，每个路径只会访问一次。所以时间复杂度为两者和。
空间复杂度：O(n+m)


### 思路2：BFS + 入度数组

使用BFS之前，需要额外增加一个入度数组，这样从入度为0的节点开始，利用队列进行BFS。

如果遍历到下一个节点，就将下一个节点入度--，如果入度为0了，那么就可以将这个节点加入队列中，直到队列为空。

对于有环的情况，在环中的节点不会被压入队列（因为入度没有0）。所以根据最后遍历的结果，如果遍历节点数要小于所有节点数，那么则可以证明图中有环。


```C++
class Solution {
public:
    vector<int> res;
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //邻接表
        vector<vector<int>> graph(numCourses, vector<int>());
        //入度
        vector<int> degree(numCourses, 0);
        for(auto prerequisite : prerequisites){
            int from = prerequisite[1];
            int to = prerequisite[0];
            graph[from].push_back(to);
            degree[to]++;
        }

        queue<int> q;
        //入度为0的先压入
        for(int i = 0; i < numCourses; i++){
            if(degree[i] == 0){
                q.push(i);
            }
        }

        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i < sz; i++){
                int cur = q.front();
                q.pop();

                //计入最后结果
                res.push_back(cur);

                for(int next : graph[cur]){
                    degree[next]--;
                    //新的入度为0 的压入
                    if(degree[next] == 0) {
                        q.push(next);
                    }
                }
            }
        }

        //如果有环的不会被压入队列，同时也不会被计入结果，所以大小要小于所有节点数
        if(res.size() < numCourses) res.clear();
        return res;
    }
};
```