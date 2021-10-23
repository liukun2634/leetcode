## 124. 二叉树中的最大路径和

### 题目

https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/

### 思路： 递归

组合路径的方式

   pp
   |
   a
  / \ 
 b   c

1) pp + a + max(0, b, c) (递归返回上去做判断)
2) b + a + c （当前节点比较）



```C++
class Solution {
public:

    int ans = INT_MIN;
    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return ans;
    }

    int maxGain(TreeNode* p){
        if(p == nullptr) return 0;

        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int left = max(0, maxGain(p -> left));
        int right = max(0, maxGain(p -> right));

         // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
         // a + max(0, b, c) 
        int ret = max(left, right) + p -> val;
        
        //b + a + c 与 a + max(0, b, c) 比较
        ans = max({ans, left + p -> val + right, ret});
        
        // 返回节点的最大贡献值
        return ret;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：