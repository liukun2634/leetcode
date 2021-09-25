## 50. Pow(x, n)

### 题目

https://leetcode-cn.com/problems/powx-n/

### 思路：快速幂 

快速幂的关键是看 n 转换为 2 进制，将位置上为1 的值，计入结果。

```C++
class Solution {
public:
    double myPow(double x, int n) {
        long long N = n; //避免 -MAX_INT 越界
        return N >= 0 ? quickPow(x, N) : 1.0 / quickPow(x, -N);
    }

    double quickPow(double x, long long n){
        double res = 1.0;
        while(n > 0) {
            if(n & 1){  //如果n在该位置为1，计入res
                res = res * x;
            }
            n >>= 1;
            x = x * x; //x翻倍
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：