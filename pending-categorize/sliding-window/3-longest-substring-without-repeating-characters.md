### 3. 无重复字符的最长子串

#### 题目

https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/

#### 思路： 滑动窗口

相比于字符串的框架，这里更加简单，只有一个字符串数组，不在需要need 和 valid 来进行判断。只用一个windows 搞定。

同样考虑滑动窗口的四个问题：其中收缩窗口的条件和更新最后结果的位置和条件，是解决该题的关键。

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> window;
        int left = 0, right = 0, ans = 0;
        while(right < s.size()) {
            char c = s[right];
            right++;
            //右移窗口后的更新操作
            window[c]++;
            //收缩窗口的条件
            while(window[c] > 1) {
                char d = s[left];
                left++;
                //左移窗口后的更新操作
                window[d]--;
            }
            //更新结果条件应当在收缩窗口之后
            ans = max(ans, right - left);
        }
        return ans;
    }
};
```