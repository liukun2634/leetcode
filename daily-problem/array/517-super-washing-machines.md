## 517. 超级洗衣机

### 题目

https://leetcode-cn.com/problems/super-washing-machines/

### 思路：贪心 

https://leetcode-cn.com/problems/super-washing-machines/solution/jie-du-yi-xia-zi-ji-li-jie-de-guan-fang-ydl19/

```C++
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int sum = 0;
        int n = machines.size();
        for(int num :  machines){
            sum += num;
        }
        if(sum % n != 0) return -1;
        int avg = sum / n;
        int res = 0;
        sum = 0;
        for(int num : machines){
            sum += (num - avg);
            res = max({res, abs(sum), num - avg});
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：