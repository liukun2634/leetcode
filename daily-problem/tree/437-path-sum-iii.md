## 437. 路径总和 III

### 题目

https://leetcode-cn.com/problems/path-sum-iii/


理解： 树看出有向图， 求路径和

### 思路1： 双重递归

第一次递归，找到所有初始节点。

第二次递归，记录初始节点到叶子节点的路径和，判断是否满足条件。

可以想象为图遍历，第一次递归是找到所有的出发节点，第二次就是DFS了。

```C++
class Solution {
public:
    int res = 0;
    int pathSum(TreeNode* root, int targetSum) {
        traverse(root, targetSum);
        return res;
    }


    void traverse(TreeNode* p, int targetSum){
        if(p == nullptr) return;
        dfs(p, targetSum, 0);
        
        traverse(p->left, targetSum);
        traverse(p-> right, targetSum);
    }

    void dfs(TreeNode* p, int targetSum, int sum){
        if(p == nullptr) return;
        sum += p -> val;
        if(sum == targetSum) res++;
        dfs(p -> left , targetSum, sum);
        dfs(p -> right , targetSum, sum);
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(N) 栈开销


### 思路1： 前缀和

用哈希表保存前缀和的个数。

类似有向图求路径和

```C++
class Solution {
public:
    int res = 0;
    //用哈希表统计 <前缀和, 个数>
    unordered_map<int, int> map;
    int pathSum(TreeNode* root, int targetSum) {
        //前缀和起始为0
        map[0] = 1;
        traverse(root, targetSum, 0);
        return res;
    }

    void traverse(TreeNode* p, int targetSum, int sum){
        if(p == nullptr) return;

        //计算当前的前缀和
        sum += p -> val;
        if(map.count(sum - targetSum)) res += map[sum - targetSum];
        
        //将当前的前缀和加入map中
        map[sum]++;
        //递归调用left 和 right (类似有向图遍历)
        traverse(p->left, targetSum, sum);
        traverse(p->right, targetSum, sum);
        //遍历结束要移除当前的前缀和
        map[sum]--;
    }
};

```


