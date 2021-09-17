## 538. 把二叉搜索树转换为累加树

### 题目

https://leetcode-cn.com/problems/convert-bst-to-greater-tree/

### 思路1： 递归 +　反序中序遍历

使用全局变量记录当前值，然后观察可以得到先深度优先右子树，根节点最后左子树。

```C++
class Solution {
public:
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        traverse(root);
        return root;
    }

    void traverse(TreeNode* p){
        //1. 返回条件
        if(p == nullptr) return;
        
        //2. 先计算右子树，再root，最后左子树
        traverse(p->right);
        //3. 中序遍历，sum 是全局变量不断增加，并更新root 值
        sum = sum + p->val;
        p->val = sum;
        traverse(p->left); 
    }
};
```
优化成一个函数：

```C++
class Solution {
public:
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        if(root == nullptr) return root;

        convertBST(root->right);
        sum = sum + root->val;
        root->val = sum;
        convertBST(root->left); 
        return root;
    }
};
```

**复杂度分析**

时间复杂度： 每个节点遍历 O(n)
空间复杂度： 树高栈开销， O(n) 最差， 平均O（logn）