## 1109. 航班预订统计

### 题目

https://leetcode-cn.com/problems/corporate-flight-bookings/

### 思路： 差分数组

构造差分数组，然后还原结果（还原是求前缀和的过程）。

```C++
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n + 1, 0);
        for(auto booking : bookings){
            diff[booking[0] - 1] += booking[2];
            diff[booking[1]] -= booking[2];
        }

        vector<int> answer(n);
        answer[0] = diff[0];
        for(int i = 1; i < n; i++){
            answer[i] = diff[i] + answer[i - 1]; 
        }
        return answer;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)