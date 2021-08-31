### 1743. 从相邻元素对还原数组

#### 题目
https://leetcode-cn.com/problems/restore-the-array-from-adjacent-pairs/

#### 思路

对于数组还原，首先可以考虑用哈希表记录。这题就是使用哈希表来保存与一个数相邻的数，相邻的数可以存在数组里面。其次，该题还原数组可以理解成图的遍历，通过用哈希表来记录相邻节点，通过第一个节点遍历。（遍历可以考虑用DFS或者BFS）

**要点：**
1. 小技巧：遇到还原数组使用哈希表来记录
2. 相邻节点对，考虑图的遍历（DFS 递归+visit，BFS queue）

```cpp
class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs)
    {
        unordered_map<int, vector<int>> relation_map;
        //构建关系map
        for (vector<int> adjacentPair : adjacentPairs) {
            relation_map[adjacentPair[0]].push_back(adjacentPair[1]);
            relation_map[adjacentPair[1]].push_back(adjacentPair[0]);
        }
        //找头元素
        int n = adjacentPairs.size() + 1;
        vector<int> nums(n);
        for (auto relation : relation_map) {
            if (relation.second.size() == 1) {
                nums[0] = relation.first;
                break;
            }
        }
        //还原相邻数组，这里简化了图的遍历方法
        nums[1] = relation_map[nums[0]][0];
        for (int i = 2; i < n; i++) {
            vector<int> adj = relation_map[nums[i - 1]];
            if (adj[0] == nums[i - 2]) {
                nums[i] = adj[1];
            } else {
                nums[i] = adj[0];
            }
        }
        return nums;
    }
};
```

因为这里是只会有一条遍历线的图，所以可以用数组直接遍历，当然还原相邻数组可以套用图的遍历：
https://leetcode-cn.com/problems/restore-the-array-from-adjacent-pairs/solution/mo-ao-mei-ri-yi-ti-liang-chong-sou-suo-b-h8ed/