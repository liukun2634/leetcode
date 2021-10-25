## 5. 最长回文子串

### 题目

https://leetcode-cn.com/problems/longest-palindromic-substring/

### 思路：动态规划 

dp[i][j] 以 i 开始 j 结尾的字符串 是否为回文子串

更新最终结果

```C++
class Solution {
public:
    string longestPalindrome(string s) {
        //dp[i][j] 以 i 开始 j 结尾的字符串 是否为回文子串
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool> (n, false));
        for(int i = 0; i < n; i++){
            dp[i][i] = true;
        }

        string res = s.substr(0, 1);
        int count = 1;
        for(int j = 1; j < n; j++){
            for(int i = 0; i < j; i++){
                //更新dp[i][j]
                if(s[i] == s[j]){
                    if(i + 1 == j) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i][j] || dp[i + 1][j - 1];
                    }
                }
               
                //更新结果
                if(dp[i][j] && j - i + 1 > count){
                    count = j - i + 1;
                    res = s.substr(i, j - i + 1);
                }
            }
        }
        return res;
    } 
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n^2)