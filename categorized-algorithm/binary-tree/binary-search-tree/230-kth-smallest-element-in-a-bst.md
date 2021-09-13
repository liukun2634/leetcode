## 230. 二叉搜索树中第K小的元素

### 题目

https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/

### 思路1： 递归 

利用搜索树中序遍历就是sorted 数组的性质，使用额外的数组保存，返回第k个。

依然使用二叉树递归的标准三步模板：

```C++
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> arr;
        traverse(arr, root);
        return arr[k - 1];
    }

    void traverse(vector<int>& arr, TreeNode* p){
        //1.返回条件
        if(p == nullptr) return;
        //2. 左右子树的调用
        traverse(arr, p->left);
        //3. 中序遍历，记录结果
        arr.push_back(p->val);
        traverse(arr, p->right);
        return;
    }
};
```
优化：其实不需要额外数组保存结果，只需要计数到第k个就可以了。

```C++
class Solution {
public:
    int res = 0;
    int kthSmallest(TreeNode* root, int k) {
        traverse(root, k);
        return res;
    }
    int idx = 0;
    void traverse(TreeNode* p, int k){
        //剪枝
        if(p == nullptr || idx > k) return;
        traverse(p->left, k);
        //利用搜索树的性质，中序遍历，达到第k个，即为结果
        idx++;
        if(idx == k) {
            res = p->val;
        }
        traverse(p->right, k);
    }
};
```

**复杂度分析**

时间复杂度：O(N) 每个节点都被递归到
空间复杂度：O(N) 最差情况， 二叉树平均 O(logN)