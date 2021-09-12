## 678. 有效的括号字符串

### 题目

https://leetcode-cn.com/problems/valid-parenthesis-string/

### 思路1：模拟 

使用变量记录出现的个数， 第一遍遍历判断 ')' 是否合法，第二遍遍历判断 '(' 是否合法。 

注意star 记录需要清 0；

```C++
class Solution {
public:
    bool checkValidString(string s) {
        int left = 0, right = 0;
        int star = 0;
        int n = s.size();
        for(int i = 0; i < n; i++){
            char c = s[i];
            if(c == '(') {
                left++;
            } else if(c == '*'){
                star++;
            } else {
                if(left > 0) left--;
                else if(star > 0) star--;
                else return false; 
            }
        }
        //star 清0
        star = 0;
        for(int i = n - 1; i >= 0; i--){
            char c = s[i];
            if(c == ')') {
                right++;
            } else if(c == '*'){
                star++;
            } else {
                if(right > 0) right--;
                else if(star > 0) star--;
                else return false; 
            }
        }
        return true;
    }

};
```
**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)


**优化**： 一遍遍历, 贪心思路：
https://leetcode-cn.com/problems/valid-parenthesis-string/solution/you-xiao-de-gua-hao-zi-fu-chuan-by-leetc-osi3/

遍历过程中维护未匹配的左括号数量可能的最小值和最大值，根据遍历到的字符更新最小值和最大值：

如果遇到左括号，则将最小值和最大值分别加 1；
如果遇到右括号，则将最小值和最大值分别减 1；
如果遇到星号，则将最小值减 1，将最大值加 1。


### 思路2：栈

使用两个栈 left 和 star，栈记录的是index，一遍遍历判断 ')' 是否合法 （先pop left 再pop start）。

最后根据index 判断 '(' 是否合法

### 思路3：动态规划