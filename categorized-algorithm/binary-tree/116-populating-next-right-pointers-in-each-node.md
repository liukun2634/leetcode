## 116. 填充每个节点的下一个右侧节点指针

### 题目

https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/

### 思路1： 递归 - 先序遍历

标准递归模板：

额外增加链接两个节点的方法

```Java
class Solution {
    public Node connect(Node root) {
        if(root == null) return null;
        if(root.left != null) {
            root.left.next = root.right;
        }
        connectTwoNodes(root.left, root.right);
        return root;
    }

    public void connectTwoNodes(Node p1, Node p2){
        if(p1 != null && p1.left != null) {
            p1.left.next = p1.right;
            connectTwoNodes(p1.left, p1.right);
        }
        if(p2 != null && p2.left != null) {
            p2.left.next = p2.right;
            connectTwoNodes(p2.left, p2.right);
        }
        if(p1 != null && p2 != null && p1.right != null) {
            p1.right.next = p2.left;
            connectTwoNodes(p1.right, p2.left);
        }
    }
}
```

优化成两个节点的判断 （递归要写好也不容易，考虑层级的不同时候，递归判断数目就不同）：

```Java
class Solution {
    public Node connect(Node root) {
        if(root == null) return null;
        connectTwoNodes(root.left, root.right);
        return root;
    }

    public void connectTwoNodes(Node p1, Node p2){
        //1. 返回条件
        if(p1 == null || p2 == null) return;

        //2. 连接 root 的两个节点
        p1.next = p2;

        //3. 调用left right
        connectTwoNodes(p1.left, p1.right);
        connectTwoNodes(p2.left, p2.right);
        connectTwoNodes(p1.right, p2.left);
    }
}
```


**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(N)最差，O(logN)平均

### 思路2： 层序遍历