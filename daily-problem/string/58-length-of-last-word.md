## 58. 最后一个单词的长度

### 题目

https://leetcode-cn.com/problems/length-of-last-word/

### 思路1： 正序 + 双指针

双指针滑动，使用res 保存最后单词长度。

```C++
class Solution {
public:
    int lengthOfLastWord(string s) {
        int left = 0, right = 0;
        int res = 0;
        for(char c : s){
            right++;
            if(c == ' '){
                left = right;
            } else{
                res = right - left;
            }
        }
        return res;
    }
};
```

### 思路2： 反序遍历

```C++
class Solution {
public:
    int lengthOfLastWord(string s) {
        int index = s.size() - 1;
        while(s[index] == ' '){
            index--;
        }
        int res = 0;
        while(index >= 0 && s[index] != ' '){
            index--;
            res++;
        }
        return res;
    }
};
```