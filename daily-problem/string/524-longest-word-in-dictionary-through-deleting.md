## 524. 通过删除字母匹配到字典里最长单词

### 题目

https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/

### 思路：排序 + 双指针 

先按照题目对字典要求按照长度从大到小排序。

判断一个字符串删掉几个字符是否可以得到另一个，可以用双指针，一个字符一个字符的比较。

```C++
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        int n = s.size();
        sort(dictionary.begin(), dictionary.end(), [](string s1, string s2) {
            return s1.size() > s2.size() || (s1.size() == s2.size() && s1 < s2);
        });
        for(string word : dictionary){
            int j = 0, m = word.size();
            for(int i = 0; i < n; i++){
                if(s[i] == word[j]){
                    j++;
                    if(j == m) return word;
                }
            } 
        }
        return "";
    }
};
```

**复杂度分析**

时间复杂度：O(mlogm + m * n) 排序 + 判断
空间复杂度：O(logm) 排序空间