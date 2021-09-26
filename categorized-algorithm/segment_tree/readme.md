# 线段树和树状数组

区域求和问题

学习：
https://leetcode-cn.com/problems/range-sum-query-mutable/solution/guan-yu-ge-lei-qu-jian-he-wen-ti-ru-he-x-41hv/


Binary Indexed Tree 树状数组
Segment Tree 线段树

O(logn)操作复杂度
建造树：O(nlogn) (可以堆一样，优化到 O(n))


区别：
树状数组逻辑上是一棵普通的树，而线段树逻辑上是一颗完全二叉树；
两者时间复杂度级别相同, 但是树状数组的常数明显优于线段树而且代码实现简单；
线段树的空间复杂度在常数上为树状数组的两倍；
一般来讲，凡是可以使用树状数组解决的问题, 使用线段树也可以解决, 但是线段树能够解决的问题树状数组未必能够解决（例如求区间最大/小值）；


树状数组

利用二进制下标，保存从0 开始的子序区间和。相比于前缀和数组，能够O(logn)内实现更新数据。



