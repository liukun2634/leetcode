## 106. 从中序与后序遍历序列构造二叉树

### 题目

https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

### 思路1： 递归（标准构造树模板）

中序和后序同样根前序和中序类似。

因为后序是前序相反的情况，可以对后序数组，从后往前，先右子树，后左子树的顺序，来构建树。 （基本就在前序的基础上改两两处顺序）

```C++
class Solution {
public:
    int end = 0;
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        end = postorder.size() - 1;
        TreeNode* root = buildTree(inorder, postorder, 0, postorder.size() - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int left, int right) {
        if(end < 0) return nullptr;
        if(left > right) return nullptr;
        
        TreeNode* p = new TreeNode(postorder[end]);
        int idx = left;
        for(int i = left; i <= right; i++){
            if(postorder[end] == inorder[i]){
                idx = i;
                break;
            }
        }
        end--;

        p->right = buildTree(inorder, postorder, idx + 1, right);
        p->left = buildTree(inorder, postorder, left, idx - 1);
        
        return p;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：