## 32. 最长有效括号

### 题目

https://leetcode-cn.com/problems/longest-valid-parentheses/

### 思路1：栈

遇到括号，就要想到用栈来解决。这里栈中压入的是未匹配的index。

注意，一开始一定要压入一条数据 -1。 可以用于右括号的判断。

如果左括号，压入index，
如果右括号，则抛出栈顶，同时对栈进行判断：
1、 如果栈为空，那么说明没有匹配的左括号。将当前index 压入，重新从该节点计算有效括号。
2、 如果栈不为空，那么则有匹配的左括号，计算与栈顶index 的差值

```C++
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        int n = s.size();
        int res = 0;
        stk.push(-1);
        for(int i = 0; i < n; i++){
            if(s[i] == '('){
                stk.push(i);
            } else{
                stk.pop();
                if(stk.empty()){
                    //说明到这里为止开始重新统计最长字符串长度
                    stk.push(i);
                } else {
                    //存在匹配的左括号，计算长度
                    res = max(res, i - stk.top());
                }
            }
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)


### 思路2：动态规划

dp[i] 其中第 i 个元素表示以下标为 i 的字符结尾的最长有效子字符串的长度。

如果 s[i] == ')'  s[i-1] == '(' , dp[i] = dp[i - 2] + 2
如果 s[i] == ')'  s[i -1] == ')' && s[i - dp[i - 1] - 1] = '('

dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2


```C++
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);
        int res = 0;
        for(int i = 1; i < n; i++){
            if(s[i] == ')'){
                if(s[i - 1] == '('){ 
                    dp[i] = (i >= 2? dp[i - 2] : 0) + 2;
                } else if(i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '('){
                    dp[i] = dp[i - 1] + (i - dp[i - 1] >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                res = max(res, dp[i]);
            }
        }
        return res;
    }
};
```


**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)