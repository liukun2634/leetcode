### 1137. 第 N 个泰波那契数

#### 题目

https://leetcode-cn.com/problems/n-th-tribonacci-number/

#### 思路1： 动态规划

状态转移就是题目的公式 `T(n+3) = T(n) + T(n+1) + T(n+2)`
再利用三个变量将一维数组缩小到O(1)的空间复杂度.

技巧：
  - 动态规划（滚动数组）

```cpp
class Solution {
public:
    int tribonacci(int n) {
        if(n == 0 || n == 1) return n;
        if(n == 2) return 1;
        int a = 0, b = 1, c = 1;
        for(int i = 2; i < n; i++ ) {
            int d = a + b + c;
            a = b;
            b = c;
            c = d;
        }
        return c;
    }
};
```

#### 思路2： 矩阵快速幂