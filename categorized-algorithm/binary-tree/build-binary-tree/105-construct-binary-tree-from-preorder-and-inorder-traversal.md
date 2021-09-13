## 105. 从前序与中序遍历序列构造二叉树

### 题目

https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

### 思路1：递归 （标准构造树模板）

理解： 

对于任意一颗树而言，前序遍历的形式总是
[ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]
即根节点总是前序遍历中的第一个节点。

而中序遍历的形式总是
[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]

思路： 

对于前序遍历，提供一个全局start 指针，指向当前构建的节点。

对于中序遍历，利用前序遍历的根节点值，维护两个指针left 和 right，用于分割需要构建的子树区间。

```C++
class Solution {
public:
    int start = 0;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* root = buildTree(preorder, inorder, 0, inorder.size() - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, int left, int right) {
        if(start >= inorder.size()) return nullptr;
        if(left > right) return nullptr;
        
        TreeNode* p = new TreeNode(preorder[start]);
        //找寻中间分割的下标 （可以使用哈希表替换）
        int idx = left;
        for(int i = left; i <= right; i++){
            if(preorder[start] == inorder[i]){
                idx = i;
                break;
            }
        }
        start++;

        p->left = buildTree(preorder, inorder, left, idx - 1);
        p->right = buildTree(preorder, inorder, idx + 1, right);
        return p;
    }
};
```

**复杂度分析**

时间复杂度：O(N) 使用哈希表替换后的复杂度
空间复杂度：O(N)