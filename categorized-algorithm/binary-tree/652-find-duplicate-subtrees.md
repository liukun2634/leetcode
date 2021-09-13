## 652. 寻找重复的子树

### 题目

https://leetcode-cn.com/problems/find-duplicate-subtrees/

### 思路：递归 +　二叉树序列化 

从题目数据量看，最多只能一次递归遍历，那么就需要额外的方式保存整个树的形式。这里涉及二叉树序列化的技巧，将树转换成string，也就是leetcode 二叉树正常输出的样子。

二叉树序列化可以使用后序遍历，因为需要在知道左右子树后，就能得到当前节点的子树序列化结构。

然后通过哈希表（子树序列化值 + 数目），可以判断是否已经有其他相同的子树存在，由于结果只需要一次，所以只用判断哈希值为2时压入结果。

```C++
class Solution {
public:
    vector<TreeNode*> res;
    unordered_map<string, int> map;
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        traverse(root);
        return res;
    }

    string traverse(TreeNode* p){
        if(p == nullptr) return "#";
        
        string left = traverse(p->left);
        string right = traverse(p->right);
        //后序遍历，先知道最右子树的值后才知道当前子树序列化的值, 注意还需要增加分隔符
        string serial = to_string(p->val) + "," + left + "," + right;

        map[serial]++;

        //达到2时候说存在明重复，计入结果
        if(map[serial] == 2) res.push_back(p);

        return serial;
    }
};
```

**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(N)