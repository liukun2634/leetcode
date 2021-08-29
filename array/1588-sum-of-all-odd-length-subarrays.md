## 1588. 所有奇数长度子数组的和

### 题目

https://leetcode-cn.com/problems/sum-of-all-odd-length-subarrays/

### 思路：前缀和

因为要求的是连续子数组的和，可以考虑使用前缀和。

增加一个前缀和的辅助数组 `sums[i]` 表示数组中前 i 个数的和，于是有 **数组中第 i 个数 到 第 j 个数的 和为 `sum[j] - sums[i]`**。

可以通过遍历间隔 `t` 为 n 之内的所有奇数，将所有的间隔和计入到最后的返回值中。

```cpp
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        vector<int> sums(n + 1);
        //初始化前缀和数组
        sums[0] = 0;
        for(int i = 1; i <= n; i++){
            sums[i] = arr[i - 1] + sums[i - 1];
        }

        int res = 0;
        //遍历奇数间隔，通过前缀和数组求和
        for(int t = 1; t <= n; t = t + 2){
            for(int j = i; j <= n; j++){
                 res += sums[j] - sums[j - t];
            }
        }
        return res;
    }
};
```

### 复杂度分析

时间复杂度：$O(N^2)$ 
空间复杂度：$O(N)$