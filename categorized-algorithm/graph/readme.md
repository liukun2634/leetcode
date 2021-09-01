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


