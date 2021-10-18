# 遍历树的方式


1. 递归

添加 val 的位置不同。

2. 迭代

思路： 使用stack 模拟递归过程

思路1：利用中序栈遍历方法，先while找到最left 的指针，再开始pop 栈，通过将res记录放到while 找left的循环中，实现先序遍历。
这里还需注意，除了判断栈为空以外，还需判断p是否为空，从而可以继续pop stack。

该策略适合前序，中序 和 后序（改为先找right指针）三种
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

思路2，单层while 循环，先压入right，再压入left
该策略只适合前序和后序遍历（后序是先压入left，后压入right）

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
