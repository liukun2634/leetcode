### 316. 去除重复字母

#### 题目

https://leetcode-cn.com/problems/remove-duplicate-letters/

#### 思路：单调栈
参考：官方题解
https://leetcode-cn.com/problems/remove-duplicate-letters/solution/qu-chu-zhong-fu-zi-mu-by-leetcode-soluti-vuso/

该题不同于其他求最近的最大/最小值模板，而是用到单调栈单调递增的性质来解决问题。

整体思路是通过维护一个单调递增的栈，来保证最后的字典序最小。维护单调栈，可以遵循单调栈的模板。遍历字符串s，然后对于每个字符s[i], 与栈顶元素相比。如果栈顶元素要更大，则栈顶元素出栈，直到寻找到栈顶比当前元素更小的位置。将该字符压入栈中。

然后就是细节上的额外操作，来保证 **对于字符串s中的每个字符都需要出现在新字符串中，且只能出现一次**：
- 在入栈时，如果字符 s[i] 已经存在于栈中，则不能加入字符 s[i]。为此，需要记录每个字符是否出现在栈中。
- 在出栈时，如果字符串在后面的位置上再也没有这一字符，则不能弹出栈顶字符。为此，需要记录每个字符的剩余数量，当这个值为 0 时，就不能弹出栈顶字符了。


```cpp
class Solution {
public:
    string removeDuplicateLetters(string s) {
        //单调栈，记录最后的结果
        stack<char> stk;
        //记录在遍历过程中s中剩余char个数
        unordered_map<char, int> remains;
        //记录哪些元素已经在栈中
        unordered_set<char> vis; 
        for(char c: s) {
            remains[c]++;
        }
        for(int i = 0; i < s.size(); i++){
            //如果不存在于栈才需要判断
            if(!vis.count(s[i])) {
                //判断栈顶是否要出栈
                while(!stk.empty() && stk.top() > s[i] && remains[stk.top()] > 0){
                    vis.erase(stk.top());
                    stk.pop();
                }
                //只有不存在才入栈
                stk.push(s[i]);
                vis.emplace(s[i]);
            } 
            //更新remains
            remains[s[i]]--;
        }
        
        //将栈转换成最后访问结果
        int n = stk.size();
        string res(n, ' ');
        //出栈是逆序
        for(int i = n - 1; i >= 0; i--) {
            res[i] = stk.top();
            stk.pop();
        }
        return res;
    }
};
```
**复杂度分析**

时间复杂度：O(n) n是string长度
空间复杂度：O(C) C是字符集的大小


**优化**

- `stack<char>`可以用 `string` 来直接模拟。
- `unordered_map<char, int>` 和 `unordered_set<char>`可以通过 `i = char - 'a'` 使用 vector<int> 代替。

```cpp
class Solution {
public:
    string removeDuplicateLetters(string s) {
        //string模拟单调栈，即为最后
        string stk;
        //记录元素是否已经在栈中
        vector<int> vis(26); 
        //记录剩余char个数
        vector<int> remains(26);
        for(char ch : s) {
            remains[ch - 'a']++;
        }

        for(char ch : s) {
            //后面只有没被压栈才需要判断
            if(!vis[ch - 'a']) {
                //判断栈顶是否要出栈
                while(!stk.empty() && stk.back() > ch && remains[stk.back() - 'a'] > 0){
                    vis[stk.back() - 'a'] = 0;
                    stk.pop_back();
                }
                //当前元素入栈
                stk.push_back(ch);
                vis[ch - 'a'] = 1;
            } 
            //更新remains
            remains[ch - 'a']--;
        }
        return stk;
    }
};

```

