## 789. 逃脱阻碍者

### 题目

https://leetcode-cn.com/problems/escape-the-ghosts/

### 思路： 贪心 + 曼哈顿距离

判断各个点到target的曼哈顿距离，如果有 ghost 比 (0, 0)更短，那么就false。
 
```cpp
class Solution {
public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int dist = distance(0, 0, target[0], target[1]);
        for(auto ghost : ghosts){
            if(distance(ghost[0], ghost[1], target[0], target[1]) <= dist) return false;
        }
        return true;
    }

    int distance(int x1, int y1, int x2, int y2){
        return abs(x1 - x2) + abs(y1 - y2);
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)