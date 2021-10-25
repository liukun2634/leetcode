## 55. 跳跃游戏

### 题目

https://leetcode-cn.com/problems/jump-game/

### 思路： 贪心

首先题目表示跳跃最大长度，所以尽可能按照最大的跳 

维护一个end = max(end, nums[i] + i)

如果end >= n 说明一定可以跳到最后一步。

如果 end < i 则说明到达不了最后

```C++
class Solution {
public:
    bool canJump(vector<int>& nums) {
         int n = nums.size();
         int end = 0;
         for(int i = 0; i < n; i++){
             if(i > end) return false;
             end = max(end, nums[i] + i);
         }
         return true;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)