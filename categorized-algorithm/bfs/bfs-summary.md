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

原理：两个队列，一个从起点出发，一个从终点出发。

实现方式1：

两个队列还需要分别增加一个`hashmap<key, value>` ，一方面可以判断是否存在于已访问的集合中，同时又能快速拿到该节点需要走过的步数。但可以省去visited了，因为map可以记录该信息。

该结构参考： https://leetcode-cn.com/problems/open-the-lock/solution/gong-shui-san-xie-yi-ti-shuang-jie-shuan-wyr9/

实现方式2：

关于如何存储，两个队列，还可以用两个hashset，不需要队列和map组合，只不过在遍历时候需要额外的一个hashset存储中间结果（控制入队）。

该结构参考： https://labuladong.gitbook.io/algo/mu-lu-ye-3/mu-lu-ye-1/bfs-kuang-jia

**双向 BFS 局限，必须知道终点在哪里。**

双向BFS模板：

```C++

int doubleDirectionBFS() {
    //双向BFS
    queue<string> q1;
    queue<string> q2;
    unordered_map<string, int> m1;
    unordered_map<string, int> m2;

    //压入起点和终点
    q1.push(start);
    q2.push(target);
    m1.emplace(start, 0);
    m2.emplace(target, 0);

    //搜索
    while(!q1.empty() && !q2.empty()){
        int step = -1;
        if(q1.size() < q2.size()){
            step = bfs(q1, m1, m2);
        } else {
            step = bfs(q2, m2, m1);
        }
        if(step != -1) return step;
    }
    return -1;
}

int bfs(queue<string>& q, unordered_map<string, int>& m, unordered_map<string, int>& other){
    int sz = q.size();
    for(int i = 0; i < sz; i++){
        string cur = q.front();
        q.pop();
        int step = m[cur];

        if(other.count(cur)) return step + other[cur];

        vector<string> nexts = generateNext(cur);
        for(string next : nexts) {
            //如果没访问过，入队同时更新map
            if(!m.count(next)){
                q.push(next);
                m.emplace(next, step + 1);
            }
        }
    }
    return -1;
}

vector<string> generateNext(string cur){
    vector<string> res;
    return res;
}

```



 ## 多源BFS