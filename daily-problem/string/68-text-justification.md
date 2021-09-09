## 68. 文本左右对齐

### 题目

https://leetcode-cn.com/problems/text-justification/

### 思路： 模拟

分三种情况：
1. 一行只有一个字符，左对齐
2. 一行多个字符，两端对齐
3. 最后一行，左对齐

使用left 和 right 指针滑动

```C++
class Solution {
    // blank 返回长度为 n 的由空格组成的字符串
    string blank(int n) {
        return string(n, ' ');
    }

    // join 返回用 sep 拼接 [left, right) 范围内的 words 组成的字符串
    string join(vector<string> &words, int left, int right, string sep) {
        string s = words[left];
        for (int i = left + 1; i < right; ++i) {
            s += sep + words[i];
        }
        return s;
    }

public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> res;
        int left = 0, n = words.size();
        int sumLen = 0;
        for(int right = 0; right < n; right++){
            sumLen += words[right].size();
            if(sumLen + right - left > maxWidth){
                sumLen -= words[right].size();
                int numWords = right - left;
                int numSpaces = maxWidth - sumLen;
                // 情况1：只有一个单词：该单词左对齐，在行末填充剩余空格
                if (numWords == 1) {
                    res.emplace_back(words[left] + blank(numSpaces));
                } else {
                    // 情况2：当前行不只一个单词
                    int avgSpaces = numSpaces / (numWords - 1);
                    int extraSpaces = numSpaces % (numWords - 1);
                    string s1 = join(words, left, left + extraSpaces + 1, blank(avgSpaces + 1)); // 拼接额外加一个空格的单词
                    string s2 = join(words, left + extraSpaces + 1, right, blank(avgSpaces)); // 拼接其余单词
                    res.emplace_back(s1 + blank(avgSpaces) + s2);
                }
                left = right;
                sumLen = words[right].size();
            }
        }
        // 情况3： 最后一行
        if(left < n) {
            string s = join(words, left, n, " ");
            res.emplace_back(s + blank(maxWidth - s.size()));
        }
        return res;
    }
};

```

**复杂度分析**

时间复杂度：
空间复杂度：