## 235. 二叉搜索树的最近公共祖先

### 题目

https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

### 思路1: 递归 +　利用二叉搜索树性质 

通过 值来判断是在左子树还是右子树。

```C++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //处理相等情况
        if(root == p || root == q) return root;

        //利用搜索二叉树性质
        int low = min(p -> val,  q -> val);
        int high = max(p -> val, q -> val);

        if(root -> val > low && root -> val < high) return root;
        //去子树中去找
        if(root -> val < low) return lowestCommonAncestor(root -> right, p, q);
        return lowestCommonAncestor(root -> left, p, q);

    }
};
```

**复杂度分析**

时间复杂度：O(n) 遍历每个节点
空间复杂度：O(n) 压栈