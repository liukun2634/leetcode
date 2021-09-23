## 326.3的幂

### 题目

https://leetcode-cn.com/problems/power-of-three/

### 思路1： 除3模拟

```C++
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n <= 0) return false;
        while(n > 1){
            if(n % 3 > 0) return false;
            n = n / 3;
        }
        return true;
    }
};
```


### 思路2： 判断是否为最大 3 的幂的约数

根据数据范围，最大的3的幂为3^19=1162261467, 判断 n 是否为 该数的因子。

```C++
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};
```