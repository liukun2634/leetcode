## 剑指 Offer 10- I. 斐波那契数列

### 题目

https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/

### 思路1：动态规划

已经直接给出了转移方程, 由于只有两个状态，使用滚动数组压缩。
```
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
```

```C++
class Solution {
public:
    const int M = 1e9 + 7;
    int fib(int n) {
        int a = 0;
        int b = 1;
        for(int i = 0; i < n; i++){
            int c = (a + b) % M;
            a = b;
            b = c; 
        }
        return a;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)

### 思路2：矩阵快速幂

```C++

```
