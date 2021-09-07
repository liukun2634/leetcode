## 1221. 分割平衡字符串

### 题目

https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/

### 思路： 贪心

https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-wumnk/

一个合法的 LR 子串满足 L 字符和 R 字符数量相等，常规检查一个字符串是否为合格的 LR 子串可以使用 O(n)的遍历方式，可以使用记录前缀信息的数据结构，而对于成对结构的元素统计，更好的方式是转换为数学判定，使用 1 来代指 L 得分，使用 -1 来代指 R 得分。

采用map 计数：

```C++
class Solution {
public:
    int balancedStringSplit(string s) {
        int n = s.size();
        unordered_map<char, int> count ={
            {'L', 0}, {'R', 0}
        };
        int res = 0;
        for(int i = 0; i < n; i++){
            count[s[i]]++;
            if(count['L'] == count['R']){
                res++;
                count['L'] = 0;
                count['R'] = 0;
            }
        }
        return res;
    }
};
```

优化就采用一个数字记录++ 和 --

```C++
class Solution {
public:
    int balancedStringSplit(string s) {
        int n = s.size();
        int count =0, res = 0;
        for(int i = 0; i < n; i++){
            s[i] == 'L' ? count++ : count--;
            if(count == 0) res++;
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)