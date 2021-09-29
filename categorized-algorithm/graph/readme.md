# 图

参考： https://labuladong.gitbook.io/algo/mu-lu-ye-1/mu-lu-ye-2/tu

## 图的表示

- 邻接表
- 邻接矩阵

对于邻接表，好处是占用的空间少。

但是，邻接表无法快速判断两个节点是否相邻。

邻接表
如果点的值连续的话，使用`vector<vector<int>>`，否则考虑 `unordered_map<vector<int>>`
拓扑遍历尽可能还是选用邻接表。


## 图的遍历

多叉树的遍历

```C++
/* 多叉树遍历框架 */
void traverse(TreeNode root) {
    if (root == null) return;

    for (TreeNode child : root.children)
        traverse(child);
}
```

图和多叉树最大的区别是，图是可能包含环的，你从图的某一个节点开始遍历，有可能走了一圈又回到这个节点。

如果图包含环，图的遍历就要一个 visited 数组进行辅助。

```C++
Graph graph;
boolean[] visited;

/* 图遍历框架 */
void traverse(Graph graph, int s) {
    if (visited[s]) return;
    // 经过节点 s
    visited[s] = true;
    for (TreeNode neighbor : graph.neighbors(s))
        traverse(neighbor);
    // 离开节点 s
    visited[s] = false;   
}
```

这个 visited 数组的操作很像回溯算法做「做选择」和「撤销选择」，区别在于位置，回溯算法的「做选择」和「撤销选择」在 for 循环里面，而对 visited 数组的操作在 for 循环外面。

在 for 循环里面和外面唯一的区别就是对根节点的处理。

比如下面两种多叉树的遍历：
```C++
void traverse(TreeNode root) {
    if (root == null) return;
    System.out.println("enter: " + root.val);
    for (TreeNode child : root.children) {
        traverse(child);
    }
    System.out.println("leave: " + root.val);
}

void traverse(TreeNode root) {
    if (root == null) return;
    for (TreeNode child : root.children) {
        System.out.println("enter: " + child.val);
        traverse(child);
        System.out.println("leave: " + child.val);
    }
}
```
前者会正确打印所有节点的进入和离开信息，而后者唯独会少打印整棵树根节点的进入和离开信息。

为什么回溯算法框架会用后者？因为回溯算法关注的不是节点，而是树枝。

显然，对于这里「图」的遍历，我们应该把 visited 的操作放到 for 循环外面，否则会漏掉起始点的遍历。

当然，当有向图含有环的时候才需要 visited 数组辅助，如果不含环，连 visited 数组都省了，基本就是多叉树的遍历。

## 判断有向图是否有环

例题：207. 课程表

方法1： DFS +　图的遍历 （visited数组）
通过图的遍历，看是否存在某次遍历访问到之前访问过的节点，确定是否有环。

因为存在多个路径（多个起点），这里需要两个记录访问过的visited:

- visited 记录所有的节点访问情况
- path 记录当前这个路径下访问情况, 类比于正常visited

对于path 要在每次访问后，置回false。而一旦遇到下一次的path 是true，那么则说明存在环。

可以将visited 变为0, 1 和 2。 从而取代使用两个bool 数组。


方法2： BFS +　入度数组

有环的情况，在环中的节点不会被压入队列（因为入度没有0）。所以根据最后遍历的结果，如果遍历节点数要小于所有节点数，那么则可以证明图中有环。

通过入度数组也可以用DFS。

总结一下，DFS 如果不需要入度数组，是通过从图中任意一点出发，扩散出来。判断环时候需要visisted 数组， 拓扑排序需要后序遍历，最后翻转输出。

BFS 是从入度数组为0的时候，扩散出来，遍历所有不是环的节点。判断环时候需要判断最后遍历的个数是否小于所有节点，拓扑排序就是入队的顺序。


## 拓扑排序

直观地说就是，让你把一幅图「拉平」，而且这个「拉平」的图里面，所有箭头方向都是一致的。

很显然，如果一幅有向图中存在环，是无法进行拓扑排序的，因为肯定做不到所有箭头方向一致；反过来，如果一幅图是「有向无环图」，那么一定可以进行拓扑排序。

有向无环图（DAG）才有拓扑排序，非DAG图没有拓扑排序一说。

「拓扑排序」的一个附加效果是：能够顺带检测有向图中是否存在环，这个知识点非常重要，如果在面试的过程中遇到这个问题，要把这一点说出来。具有类似附加功能的算法还有：Bellman-Ford 算法附加的作用是可以用于检测是否有负权环

例题：210. 课程表 2

实现方式：

1. BFS + 入度数组

找出入度为 0 的节点，压入队列，开始BFS。

2. DFS + 后序遍历 + 翻转

你记住拓扑排序就是后序遍历反转之后的结果，且拓扑排序只能针对有向无环图，进行拓扑排序之前要进行环检测，这些知识点已经足够了。

### 单源最短路径

https://leetcode-cn.com/problems/network-delay-time/solution/gong-shui-san-xie-yi-ti-wu-jie-wu-chong-oghpz/

dp[i] 是从 start到 i的最短距离。

则有 dp[i] = min(dp[j] + j 到 i 的权值)

如果是有向图，则可以通过BFS拓扑排序方式，利用上面的递推公式，求得start 点到所有点的最短距离

但如果是无向图，且图中存在圈，那么就不能利用拓扑排序，而可以使用Bellman-Ford（动态规划，可判断负圈） / Dijkstra(贪心， 无法处理负圈)

### Bellman Ford

遍历所有的边，每次更新
dp[i] = min(dp[j] + j 到 i 的权重)

外层最多是V- 1次（顶点数）


### Dijkstra

这里因为带权，所以使用优先队列代替BFS 的 队列的方式。

前提条件是非负权图，因为是贪心算法。

可以求一个点到其他所有点的最短路径。

```C++
using PII = pair<int,int>;

int INF = 0x3f3f3f3f;

//返回其他节点距离start节点的最短距离
//neighbors 存储：from, to, cost
//n 为节点数 (1 - n)
//start 是起始节点
vector<int> dijkstra(vector<vector<int>>& neighbors, int n, int start){
    //1. 构建邻接矩阵(值为权重)， 也可以换成邻接表（需要额外的class 同时保存 to 和 cost）   
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF)); 

    for(auto& neighbor : neighbors){
        int from = neighbor[0];
        int to = neighbor[1];
        int cost = neighbor[2];
        graph[from][to] = cost;
        //如果是无向图
        //graph[from][to] = cost;
    }

    //2. 使用的数据结构
    //小顶堆（默认是大顶堆）
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    //保存与start 的距离, 默认均为最大值
    vector<int> dp(n + 1, INF);
    //3. 初始化
    pq.push({0, start});

    //4. 遍历 (区别： 优先队列只 pop 堆顶，而BFS 队列遍历是配for遍历一层)
    while(not pq.empty()){
        int dist = pq.top().first;
        int idx = pq.top().second;
        pq.pop();

        //关键判断：计算过该节点，跳过, 要小于号，否则第一个节点就被continue了
        if(dist > dp[idx]) continue; 

        //更新当前的值
        dp[idx] = dist;

        //遍历相邻节点
        for(int i = 1; i <= n; i++){
            //压入距离更新后更短的节点
            if(graph[idx][i] + dist < dp[i]){
                pq.push({graph[idx][i] + dist, i});
            }
        }
    }
    return dp;
}
```

其中，更新值的位置也可以放到相邻节点里更新， 这主要关系到的是第一个的初始化节点是在循环外面，还是在循环里面进行赋值。

```C++
    dp[start] = 0; //对start节点额外赋值
    pq.push({0, start});

    while(not pq.empty()){
        int dist = pq.top().first;
        int idx = pq.top().second;
        pq.pop();

        //关键判断：计算过该节点，跳过, 要小于号，否则第一个节点就被continue了
        if(dist > dp[idx]) continue; 

        //遍历相邻节点
        for(int i = 1; i <= n; i++){
            //压入距离更新后更短的节点
            if(graph[idx][i] + dist < dp[i]){
                //不同位置主要影响第一个节点初始化：更新下一个值
                dp[i] = graph[idx][i] + dist;
                pq.push({dp[i], i});
            }
        }
    }
```


