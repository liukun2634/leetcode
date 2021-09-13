## 654. 最大二叉树

### 题目

https://leetcode-cn.com/problems/maximum-binary-tree/

### 思路1： 递归 + 后序遍历

二叉树标准三步框架：

```C++
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return constructMaximumBinaryTree(nums, 0, nums.size() - 1);
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums, int left, int right) {
        if(left > right) return nullptr;

        int index = left;
        for(int i = left; i <= right; i++){
            if(nums[index] < nums[i]){
                index = i;
            }
        }
        TreeNode* root = new TreeNode(nums[index]);
        root-> left = constructMaximumBinaryTree(nums, left, index - 1);
        root-> right = constructMaximumBinaryTree(nums, index + 1, right);
        return root;
    }
};
```

缺点就是每次都要遍历数组找最大值，这点可以优化。

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n)

### 思路2：单调栈构造树

```C++
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
           stack<TreeNode*> s;
           int n = nums.size();
           TreeNode* cur = nullptr;
           for(int i = 0; i < n; i++){
               cur = new TreeNode(nums[i]);
               while(!s.empty() && s.top() -> val < cur -> val) {
                   TreeNode* top = s.top();  
                   s.pop();
                   //选择更小的作为其右子节点
                   if(!s.empty() && s.top() -> val < cur -> val) {
                        s.top()->right = top;
                   } else{
                        //否则作为当前节点的左子节点
                        cur -> left = top;
                   } 
               }
               s.push(cur);
           }
           
           //剩余的一些节点
            while(!s.empty()) {
                cur = s.top(); 
                s.pop();
                if(!s.empty()){
                    s.top() -> right = cur;
                }
            }
           return cur;
    }
};
```