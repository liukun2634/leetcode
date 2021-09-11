## 600. 不含连续1的非负整数

### 题目

https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/

### 思路：动态规划 


```C++
class Solution {
public:
    int findIntegers(int n) {
        vector<int> dp(31);
        dp[0] = dp[1] = 1;
        for(int i = 2; i < 31; i++){
            //计算每个位置为1时，存在的合理个数
            dp[i] = dp[i-1] + dp[i-2];
        }

        int pre = 0, res = 0;
        for(int i = 29; i >= 0; i--){
            if((n & (1 << i)) != 0) {
                res += dp[i + 1];
                //如果存在连续1，说明后面的所有情况都被计算过了，直接跳出循环
                if(pre == 1) break;
                pre = 1;
            } else {
                pre = 0;
            }
            //加上自身的一个
            if(i == 0) res++;
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：