## 207. 课程表

### 题目

https://leetcode-cn.com/problems/course-schedule/

### 思路1： DFS + 图的遍历

该题就是判断是否有环。

通过图的遍历，看是否存在某次遍历访问到之前访问过的节点，确定是否有环。

因为存在多个路径（多个起点），这里需要两个记录访问过的visited:

- visited 记录所有的节点访问情况
- path 记录当前这个路径下访问情况, 类比于正常visited

对于path 要在每次访问后，置回false。而一旦遇到下一次的path 是true，那么则说明存在环。

-> 这里也可以用0， 1， 2进行区分

```C++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //构造邻接表
        vector<vector<int>> graph(numCourses, vector<int>());
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
            if(!traverse(graph, i, visited, path)) return false;
        }
        return true;
    }

    bool traverse(vector<vector<int>>& graph, int s, vector<bool>& visited, vector<bool>& path){
        //当前路径存在环, 无法完成课程
        if(path[s]) {
            return false;
        }
        if(visited[s]) return true;

        visited[s] = true;
        path[s] = true;
        for(int next : graph[s]){
            if(!traverse(graph, next, visited, path)) return false;
        }
        path[s] = false;
        return true;
    }
};
```

**复杂度分析**

时间复杂度：O(n+m) 由于有visited，每个节点，每个路径只会访问一次。所以时间复杂度为两者和。
空间复杂度：O(n+m)