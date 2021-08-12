### 354. 俄罗斯套娃信封问题

#### 题目

https://leetcode-cn.com/problems/russian-doll-envelopes/

#### 思路：动态规划

**技巧：** 这里是二维数组分别表示信封宽度和高度，可以通过预处理，**将信封按照宽度的升序排列，对于宽度相同情况，按照高度的降序排列**。这样得到信封顺序，只需要按照高度求最长递增序列(Longest Increasing Subsequence) 就可以了。

通过排序将二维降为一维数组，然后使用动态规划

```cpp
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        //按信封宽度从小到大排序，相等情况下高度从大到小排序
        sort(envelopes.begin(), envelopes.end(), 
                [](vector<int> a, vector<int> b) -> bool {
                    return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
            });

        //转换为对高度求最大上升子序列(LIS)问题
        int n = envelopes.size();
        vector<int> dp(n, 1);
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(envelopes[i][1] > envelopes[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
           
        }
        int res = dp[0];
        for(int i = 1; i < n; i++) {
            res = max(res, dp[i]);
        }
        return res;   
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n)


**优化**

当然对于LIS 问题，可以使用二分搜索的解法，将时间复杂度降为O(nlogn)，具体可以参考 300题。