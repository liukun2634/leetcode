## 111. 二叉树的最小深度

### 题目

https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/

### 思路1：BFS

求最小深度，可以考虑用BFS，套用模板。

树的BFS注意：
- 这里不需要visited数组，因为树是不会返回原来节点的
- 树需要注意压入前判断左右节点是否为null节点

```C++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        //BFS 关键结构
        queue<TreeNode*> q;
        //压入起点
        q.push(root);
        int res = 1;
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i < sz; i++){
                TreeNode* p = q.front();
                q.pop();
                //到达最短叶子，返回
                if( p->left == nullptr && p->right == nullptr){
                    return res;
                }
                //压入新的节点
                if(p->left != nullptr) q.push(p->left);
                if(p->right != nullptr) q.push(p->right);
            }
            //进入下一层
            res++;
        }
        return res;
    }
};
```

queue 中可以同时保存深度的信息 `queue<pair<TreeNode*, int>> q`, 这个技巧可以把相应的状态都能够压入队列中，而不需要额外维护全局值。

优化：

```C++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;

        //BFS 关键结构
        queue<pair<TreeNode*, int>> q;

        //压入起点和深度
        q.push({root, 1});
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i < sz; i++){
                //同时拿到节点和对应深度
                auto [p, depth] = q.front();
                q.pop();

                //到达最短叶子，返回
                if( p->left == nullptr && p->right == nullptr){
                    return depth;
                }

                //压入新的节点
                if(p->left != nullptr) q.push({p->left, depth + 1});
                if(p->right != nullptr) q.push({p->right, depth + 1});

            }
        }
        //不会到达该位置
        return 0;
    }
};
```

**复杂度分析**

N为节点数：

时间复杂度：O(N)
空间复杂度：O(N) 


### 思路2：DFS

同样，该题可以用DFS遍历所有叶子，找到最小的深度。

**复杂度分析**

N为节点数：

时间复杂度：O(N)
空间复杂度：O(H) H 为 logN 
