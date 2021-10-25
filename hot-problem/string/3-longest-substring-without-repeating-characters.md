## 3. 无重复字符的最长子串

### 题目

https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/

### 思路： 滑动窗口


```C++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0;
        int n = s.size();
        unordered_set<char> set;
        int res = 0;
        while(right < n){
            char c = s[right];
            right++;

            while(set.count(c)){
                char d = s[left];
                set.erase(d);
                left++;
            }

            set.insert(c);
            res = max(res, right - left);
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)