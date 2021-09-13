# 构造二叉树

## 思路1： 递归

增加一个双指针left 和 right，标明需要构造的二叉树范围

依然遵循二叉树递归的三步：

1. 当left > right 则直接返回null
2. 生成 root 节点
3. 计算left 和 right 的区域，然后连接 root -> left 和 root -> right 节点

构造树的递归框架

```C++
 TreeNode* buildTree(vector<int>& arr) {
     //根节点
     TreeNode* root = buildTree(0, arr.size() - 1);
     return root;
 }

 TreeNode* buildTree(vector<int>& arr, int left, int right) {
     //1. 返回条件
     if(left > right) return nullptr;
     
     //2. root 节点处理 （前序遍历）
     TreeNode* p = new TreeNode(preorder[start]);

     //...这里省略更新新的left 和right的过程

     //3. 连接左子树和右子树
     p->left = buildTree(newLeft, newRight);
     p->right = buildTree(newLeft, newRight);

     //返回构造的节点
     return p;
 }
```


