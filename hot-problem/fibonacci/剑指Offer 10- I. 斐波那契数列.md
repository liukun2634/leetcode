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

https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/solution/gong-shui-san-xie-yi-ti-si-jie-dong-tai-9zip0/


```C++
class Solution {
public:
    int MOD = 1e9 + 7;

    int fib(int n) {
        if(n < 2) return n;
        vector<vector<long long>> ans = {{1},{0}};
        vector<vector<long long>> mat = {{1, 1},{1, 0}};
        pow(ans, mat, n - 1);
        return ans[0][0];
    }

    //快速幂
    void pow(vector<vector<long long>>& ans, vector<vector<long long>>& mat, int n){ 
        while(n > 0){
            if(n & 1){
                ans = multiply(ans, mat);
            }
            n = n >> 1;
            mat = multiply(mat, mat);
        }
    }

    //矩阵乘法
    vector<vector<long long>> multiply(vector<vector<long long>>& a, vector<vector<long long>>& b){
        int  n = a.size(), r = a[0].size(), m = b[0].size(); 
        vector<vector<long long>> c(n, vector<long long>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                for(int k = 0; k < r; k++){
                    c[i][j] += a[i][k] * b[k][j];
                    c[i][j] %= MOD;
                }
            }
        }
        return c;
    }
};
```
