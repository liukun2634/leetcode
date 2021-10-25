## 45. 跳跃游戏 II

### 题目

https://leetcode-cn.com/problems/jump-game-ii/

### 思路：贪心

增加一个reach的位置，表示下一步能够跳到的最大位置。

如果到达不了i，（end < i), 那么就增加step，同时更新当前step 能到达的最大位置。 

```C++
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int step = 0;
        int end = 0, reach = nums[0];
        for(int i = 0; i < n; i++){
            //如果到达不了该点，则需要额外跳一步到达可达最大位置
            if(end < i) {
                step++;
                end = reach;
            } 
            //不断更新下一步可以到达的最大位置
            reach = max(reach, nums[i] + i);
        }
        return step;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)