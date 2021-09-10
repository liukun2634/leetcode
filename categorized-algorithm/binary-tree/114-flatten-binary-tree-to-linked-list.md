## 114. 二叉树展开为链表

### 题目

https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/


### 思路1：递归 - 后序遍历

标准二叉树递归三部曲：

```java
class Solution {
    public void flatten(TreeNode root) {
        //1. 返回条件
        if(root == null) return;
        //2. 调用 left 和 right
        flatten(root.left);
        flatten(root.right);
        //3. 后序遍历 root 处理逻辑
        TreeNode left = root.left;
        TreeNode right = root.right;
        root.right = left;
        root.left = null;
        TreeNode p = root;
        while(p.right != null) {
            p = p.right;
        }
        p.right = right;
    }
}
```


### 思路2：递归优化

通过一个函数返回末尾指针

```java
class Solution {
    public void flatten(TreeNode root) {
        if(root == null) return;
        traverse(root);
    }

    //返回合并链表的最后节点
    public TreeNode traverse(TreeNode root){
        TreeNode tail = root;
        TreeNode right = root.right;
        if(root.left != null) {
            tail.right = root.left;
            tail = traverse(root.left);
        }
        if(right != null) {
            tail.right = right;
            tail = traverse(right);
        }
        root.left = null;
        return tail;
    }
}
```

继续优化成一个方法, 额外增加一个全局变量存之前排列好。

```java
class Solution {
    TreeNode last = null;
    public void flatten(TreeNode root) {
        //1. 返回条件
        if(root == null) return;
        //2. 调用 left 和 right (注意这里的顺序先right 后 left)
        flatten(root.right);
        flatten(root.left);
        //3. 后序遍历 root 处理逻辑
        root.right = last;
        root.left = null;
        last = root;
    }
}
```

**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(N) 最差 O(logN)平均 

### 思路3：递归 - 先序遍历 + 额外list




**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(N) 额外的list空间

### 思路4：迭代 - 寻找前驱节点



**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(1) 