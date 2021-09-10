## 226. 翻转二叉树

### 题目

https://leetcode-cn.com/problems/invert-binary-tree/

### 思路： 递归 - 先序遍历

标准二叉树递归模版。

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

**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(N) 最坏情况（链表），平均 O(logN)