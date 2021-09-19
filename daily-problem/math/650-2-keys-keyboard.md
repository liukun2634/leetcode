## 650. 只有两个键的键盘

### 题目

https://leetcode-cn.com/problems/2-keys-keyboard/

### 思路1：动态规划

dp[i][j] 为经过最后一次操作后，当前记事本上有 i 个字符，粘贴板上有 j 个字符的最小操作次数。

考虑 dp[i][j] 该如何转移：

最后一次操作是 Paste 操作：此时粘贴板的字符数量不会发生变化，即有 dp[i][j] = dp[i - j][j] + 1

最后一次操作是 Copy All 操作：那么此时的粘贴板的字符数与记事本上的字符数相等（满足 i = j），此时的 dp[i][j] = \min(dp[i][x] + 1) 0 <= x < i

```C++
class Solution {
public:
    int minSteps(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX / 2));        
        dp[1][0] = 0;
        dp[1][1] = 1;
        for(int i = 2; i <= n; i++){
            int mi = INT_MAX / 2;
            for(int j = 0; j <= i / 2; j++){
                //paste
                dp[i][j] = dp[i - j][j] + 1;
                mi = min(mi, dp[i][j]);
            }
            //copy all
            dp[i][i] = mi + 1;
        }

        int res = INT_MAX;
        for(int i = 0; i <= n; i++){
            res = min(res, dp[n][i]);
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：


### 思路2：数学

https://leetcode-cn.com/problems/2-keys-keyboard/solution/gong-shui-san-xie-yi-ti-san-jie-dong-tai-f035/

就是求 n 的质因数， 然后对所有质因数求和

```C++
class Solution {
public:
    int minSteps(int n) {
        int res = 0;
        for(int i = 2; i * i <= n; i++){
            //这里要用while，因为可能存在重复
            while(n % i == 0){
                res += i;
                n = n / i;
            } 
          
        }
        if(n != 1) res += n;
        return res;
    }
};
```