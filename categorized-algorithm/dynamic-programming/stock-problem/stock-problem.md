## 877. 石子游戏

### 题目

https://leetcode-cn.com/problems/stone-game/

### 思路： 区间dp

定义 dp[l][r] 为考虑区间 [l,r]，在双方都做最好选择的情况下，先手与后手的最大得分差值为多少。

```Java
class Solution {
    public boolean stoneGame(int[] piles) {
        int n = piles.length;
        int[][] dp = new int[n + 2][n + 2];
        for(int len = 1; len <= n; len++){
            for(int l = 1; l + len - 1 <= n; l++){
                int r = l + len - 1;
                int a = piles[l - 1] - dp[l + 1][r];
                int b = piles[r - 1] - dp[l][r - 1];
                dp[l][r] = Math.max(a, b);
            }
        }
        return dp[1][n] > 0;
    }
}
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n^2)