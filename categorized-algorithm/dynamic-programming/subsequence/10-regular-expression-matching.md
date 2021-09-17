## 10. 正则表达式匹配

### 题目

https://leetcode-cn.com/problems/regular-expression-matching/

### 思路： 动态规划

双字符串dp 标准模板:
dp[i][j] 是 0- i-1 和 0-j-1 字符串是否匹配

```C++
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        if(n == 0 && n == 0) return true;
        if(n == 0 || m == 0) return false;
        vector<vector<bool>> dp(n + 1, vector<bool> (m  + 1, false));
        dp[0][0] =true;
        for(int j = 2; j <= m; j = j + 2){
            if(p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(s[i - 1] == p[j - 1] || p[j - 1] == '.'){
                    dp[i][j] = dp[i - 1][j - 1];
                    // cout<<i << " " << j<< " " <<dp[i][j] <<endl;
                } else if(p[j - 1] == '*'){
                    if(s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                        dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i][j - 2];
                    } else {
                        dp[i][j] = dp[i][j - 2];
                    }  
                    // cout<<" " << i << " " << j << " " <<dp[i][j] <<endl;
                }
            }
        }
        return dp[n][m];
    }
};
```

优化：

字符串最开始增加" "，从而减少判断和初始化过程

```C++
class Solution {
public:
    bool isMatch(string s, string p) {
        s = " " + s;
        p = " " + p;
        int n = s.size(), m = p.size();

        vector<vector<bool>> dp(n + 1, vector<bool> (m  + 1, false));
        dp[0][0] =true;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(s[i - 1] == p[j - 1] || p[j - 1] == '.'){
                    dp[i][j] = dp[i - 1][j - 1];
                    // cout<<i << " " << j<< " " <<dp[i][j] <<endl;
                } else if(p[j - 1] == '*'){
                    if(s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                        dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i][j - 2];
                    } else {
                        dp[i][j] = dp[i][j - 2];
                    }  
                    // cout<<" " << i << " " << j << " " <<dp[i][j] <<endl;
                }
            }
        }
        return dp[n][m];
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：