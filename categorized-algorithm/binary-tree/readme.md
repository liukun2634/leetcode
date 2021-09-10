# 二叉树

框架

```Java
/* 二叉树遍历框架 */
void traverse(TreeNode root) {
    //终止条件
    if(root == null) return;
    // 前序遍历
    traverse(root.left)
    // 中序遍历
    traverse(root.right)
    // 后序遍历
}
```

### 理解二叉树

> 快速排序就是个二叉树的前序遍历，归并排序就是个二叉树的后序遍历

1. 快速排序

```java
void sort(int[] nums, int lo, int hi) {
    /****** 前序遍历位置 ******/
    // 通过交换元素构建分界点 p
    int p = partition(nums, lo, hi);
    /************************/

    sort(nums, lo, p - 1);
    sort(nums, p + 1, hi);
}
```

2. 归并排序

```java
void sort(int[] nums, int lo, int hi) {
    int mid = (lo + hi) / 2;
    sort(nums, lo, mid);
    sort(nums, mid + 1, hi);

    /****** 后序遍历位置 ******/
    // 合并两个排好序的子数组
    merge(nums, lo, mid, hi);
    /************************/
}
```

二叉树的算法思想的运用广泛，甚至可以说，只要涉及递归，都可以抽象成二叉树的问题。

### 秘诀

写递归算法的关键是要明确函数的「定义」是什么，然后相信这个定义，利用这个定义推导最终结果，绝不要跳入递归的细节。

比如说让你计算一棵二叉树共有几个节点：
```java
// 定义：count(root) 返回以 root 为根的树有多少节点
int count(TreeNode root) {
    // base case
    if (root == null) return 0;
    // 自己加上子树的节点数就是整棵树的节点数
    return 1 + count(root.left) + count(root.right);
}
```
root 本身就是一个节点，加上左右子树的节点数就是以 root 为根的树的节点总数。

左右子树的节点数怎么算？其实就是计算根为 root.left 和 root.right 两棵树的节点数呗，按照定义，递归调用 count 函数即可算出来.

写树相关的算法，简单说就是，先搞清楚当前 root 节点「该做什么」以及「什么时候做」，然后根据函数定义递归调用子节点，递归调用会让孩子节点做相同的事情。

记住二叉树的三步：
1. 递归返回条件
2. root 节点需要干什么
3. root 节点的left 和 right 需要怎么调用

### 例题

226. 翻转二叉树

```java
class Solution {
    public TreeNode invertTree(TreeNode root) {
        //1. 递归终止条件
        if(root == null) return root;
        //2. 当前root节点要干什么
        TreeNode tmp = root.left;
        root.left = root.right;
        root.right = tmp;
        //3. root.left 和 root.right 要干什么
        invertTree(root.left);
        invertTree(root.right);
        return root;
    }
}
```