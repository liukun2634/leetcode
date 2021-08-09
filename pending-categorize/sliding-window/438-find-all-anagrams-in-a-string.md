### 438. 找到字符串中所有字母异位词

#### 题目

https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/

#### 思路： 滑动窗口

等同于题目567, 继续加强滑动窗口

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> need, window;
        for(char c : p) {
            need[c]++;
        }

        int left = 0, right = 0, valid = 0;
        vector<int> ans;
        while(right < s.size()) {
            char c = s[right];
            right++;
            //右移窗口后的操作
            if(need.count(c)) {
                window[c]++;
                if(window[c] == need[c]) 
                    valid++;
            }

            //收缩窗口的条件
            while(right - left >= p.size()) {
                //返回结果更新
                if(valid == need.size()){
                    ans.push_back(left);
                }

                char d = s[left];
                left++;
                //左移窗口后的操作
                if(need.count(d)){
                    if(window[d] == need[d])
                        valid--;
                    window[d]--;
                }
            }
        }
        return ans;
    }
};
```