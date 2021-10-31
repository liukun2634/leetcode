## 5. 最长回文子串

### 题目

https://leetcode-cn.com/problems/longest-palindromic-substring/

### 思路1： 中心扩展

**技巧**

```C++
class Solution {
public:
    int len = 0;
    string res;
    string longestPalindrome(string s) {
        for(int i = 0; i < s.size(); i++){
           longestPalindrome(s, i, i);
           if(i + 1 < s.size() && s[i] == s[i + 1]){
               longestPalindrome(s, i, i + 1);
           }
        }
        return res;
    }

    string longestPalindrome(string s, int left, int right){
        int n = s.size();
        while(left - 1 >= 0 && right + 1 < n && s[left - 1] == s[right + 1]){
            left--;
            right++;
        }
        if(right - left + 1 > len){
            len = right - left + 1;
            res = s.substr(left, len);
        }
        return res;
    }

    
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(1)



### 思路2： 动态规划

```C++
class Solution {
public:
    string longestPalindrome(string s) {
        //dp[i][j] 以 i 开始 j 结尾的字符串的最长回文子串
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool> (n, false));
        for(int i = 0; i < n; i++){
            dp[i][i] = true;
        }

        string res = s.substr(0, 1);
        int count = 1;
        for(int j = 1; j < n; j++){
            for(int i = 0; i < j; i++){
                if(s[i] == s[j]){
                    if(i + 1 == j) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i][j] || dp[i + 1][j - 1];
                    }
                }
               
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