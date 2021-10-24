### 236. 二叉树的最近公共祖先

https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/

### 思路： 递归

最近公共节点特性：左右子树各包含一个目标节点。

使用递归返回最近公共祖先

1. 如果左和右返回节点都不为nullptr，说明该节点就是最近公共节点，返回。
2. 否则 返回一边不为nullpt的节点，直到找到公共节点

```C++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root -> left, p, q);
        TreeNode* right = lowestCommonAncestor(root -> right, p, q);
        if(left != nullptr && right != nullptr) return root;
        if(left != nullptr) return left;
        return right;
    }
};
```

**复杂度分析**

时间复杂度：O(N) 所有节点遍历到
空间复杂度：O(N) 最差压栈


### 思路： 哈希表记录

用哈希表记录一个节点的所有父节点。

然后判断p 和 q 的父节点最早重复的 - > 可以扩展到 n 个节点 情况