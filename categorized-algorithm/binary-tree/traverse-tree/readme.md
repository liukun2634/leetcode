# 遍历树的方式

https://leetcode-cn.com/problems/binary-tree-inorder-traversal/

1. 递归

添加 val 的位置不同。

2. 迭代

思路： 使用stack 模拟递归过程

思路1：利用中序栈遍历方法，先while找到最left 的指针，再开始pop 栈，通过将res记录放到while 找left的循环中，实现先序遍历。
这里还需注意，除了判断栈为空以外，还需判断p是否为空，从而可以继续pop stack。

该策略适合前序，中序 和 后序（改为先找right指针, 最后翻转数组 || 或者在 right 指针时候判断 right 是否为 nullptr 插入到数组）三种

前序
```C++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> res;
        if(root == nullptr) return res;
        
        TreeNode* p = root;
        while(!stk.empty() || p != nullptr){
            while(p != nullptr) {
                res.push_back(p -> val);
                stk.push(p);
                p = p -> left;
            }

            p = stk.top();
            stk.pop();
            p = p -> right;
        }
        return res;
    }
};
```

后序非倒序：

```C++
class Solution {
public: 
    
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;
        stack<TreeNode*> stk;
        TreeNode* p = root;
        TreeNode* prev = nullptr;
        while(!stk.empty() || p != nullptr){
            while(p != nullptr){
                stk.push(p);
                p = p -> left;
            }
            p = stk.top();
            stk.pop();
            
            if(p -> right == nullptr || p -> right == prev){
                res.push_back(p->val);
                prev = p;
                p = nullptr;
            } else {
                stk.push(p);
                p = p -> right;
            }
        
        }
        return res;
    }
};
```
思路2，单层while 循环，先压入right，再压入left
该策略只适合前序和后序遍历（后序是先压入left，后压入right， 最后翻转数组）

```C++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> res;
        if(root == nullptr) return res;

        stk.push(root);
        //前序遍历另一种方法
        while(!stk.empty()){
            TreeNode* p = stk.top();
            stk.pop();
            res.push_back(p->val);

            //先压入right， 再压入left
            if(p -> right != nullptr) {
                stk.push(p -> right);
            }

            if(p -> left != nullptr){
                stk.push(p -> left);
            }
        }
        return res;
    }
};
```



思路3：三色标记法：

https://leetcode-solution-leetcode-pp.gitbook.io/leetcode-solution/thinkings/tree#shu-de-bian-li-die-dai-xie-fa

先压入右指针，再压入左指针。

根节点根据位置 压入后，中，前 对于前序，中序，后序。

前序遍历
```C++
enum COLOR {
    WHITE = 0,
    GRAY = 1
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;
        
        stack<pair<TreeNode*, COLOR>> stk;
        stk.push({root, WHITE});
        while(!stk.empty()){
            auto [p, color] = stk.top();
            stk.pop();

            if(color == WHITE) {
                //先压入 右节点
                if(p -> right != nullptr) {
                    stk.push({p->right, WHITE});
                }

                //再压入 左节点
                if(p -> left != nullptr) {
                    stk.push({p->left, WHITE});
                }
                //最后压入gray，是先序遍历，最先pop 出来
                stk.push({p, GRAY});
            } else {
                res.push_back(p->val);
            }
        }
        return res;
    }
};
```


中序
```C++
enum COLOR {
    WHITE = 0,
    GRAY = 1
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;
        
        stack<pair<TreeNode*, COLOR>> stk;
        stk.push({root, WHITE});
        while(!stk.empty()){
            auto [p, color] = stk.top();
            stk.pop();

            if(color == WHITE) {
                //先压入 右节点
                if(p -> right != nullptr) {
                    stk.push({p->right, WHITE});
                }
                //压入gray
                stk.push({p, GRAY});
                //压入 左节点
                if(p -> left != nullptr) {
                    stk.push({p->left, WHITE});
                }
            } else {
                res.push_back(p->val);
            }
        }
        return res;
    }
};
```

实现上 WHITE 就表示的是递归中的第一次进入过程，Gray 则表示递归中的从叶子节点返回的过程。