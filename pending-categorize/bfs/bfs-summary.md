# BFS 


## 概念

参考： https://labuladong.gitbook.io/algo/mu-lu-ye-3/mu-lu-ye-1/bfs-kuang-jia

**BFS 与 DFS 对比**

BFS 相对 DFS 的最主要的区别是：BFS 找到的路径一定是最短的，但代价就是空间复杂度可能比 DFS 大很多。

- **DFS 和　BFS 都可以找最短距离**，但DFS 是线，BFS 是面；DFS 是单打独斗，BFS 是集体行动。
- BFS 的时间复杂度低，但是空间复杂度高，而 DFS 的空间复杂度较低，时间复杂度更高。


一般来说在找最短路径的时候使用 BFS，其他时候还是 DFS 使用得多一些（主要是递归代码好写）。

**BFS的理解**

本质上就是一幅「图」，让你从一个起点，走到终点，问最短路径。这就是 BFS 的本质，框架搞清楚了直接默写就好。

## 模板

```java
// 计算从起点 start 到终点 target 的最近距离
int BFS(Node start, Node target) {
    Queue<Node> q; // 核心数据结构
    Set<Node> visited; // 避免走回头路

    q.offer(start); // 将起点加入队列
    visited.add(start);
    int step = 0; // 记录扩散的步数

    while (q not empty) {
        int sz = q.size();
        /* 将当前队列中的所有节点向四周扩散 */
        for (int i = 0; i < sz; i++) {
            Node cur = q.poll();
            /* 划重点：这里判断是否到达终点 */
            if (cur is target)
                return step;
            /* 将 cur 的相邻节点加入队列 */
            for (Node x : cur.adj())
                if (x not in visited) {
                    q.offer(x);
                    visited.add(x);
                }
        }
        /* 划重点：更新步数在这里 */
        step++;
    }
}
```

只有当图可以返回时候才需要visited

step 可以理解成 需要返回的结果

优化技巧：
 - step 与节点作为一个pair {node, step} 同时压入队列中


 ## 双向BFS优化