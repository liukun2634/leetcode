## 470. 用 Rand7() 实现 Rand10()

### 题目

https://leetcode-cn.com/problems/implement-rand10-using-rand7/

### 思路1： k 进制诸位生成 + 拒绝采样

保证等概率，先扩大组合，通过k进制模式，保证组合的每一位是同概率的。

然后使用while循环拒绝掉一些多余的数据。

```C++
// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        while(true){
            int r = (rand7() - 1) * 7 + (rand7() - 1);
            if(1 <= r && r <= 10) return r;
        }
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：