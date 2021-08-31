### 72. 编辑距离

#### 题目

https://leetcode-cn.com/problems/edit-distance/

#### 思路：动态规划

1、定义状态：**dp[i][j] 是s1[0, i-1] 转换成 s2[0, j-1]的编辑距离**

2、状态转移方程：

- 如果s1[i - 1] 与 s2[j - 1]相同， 那么 dp[i][j] = dp[i - 1][j - 1] 
- 如果s1[i - 1] 不同 s2[j - 1]，说明需要删除，插入，替换来得到， dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1:
    - 删除： dp[i][j] = dp[i][j -1] + 1
    - 插入： dp[i][j] = dp[i - 1][j] + 1
    - 替换： dp[i][j] = dp[i - 1][j - 1] + 1

3、初始状态：d[i][0] = i, d[0][j] = j

注意这里要单独赋值初始状态。

4、最终结果：res = dp[n][m]


```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        //1.定义状态：dp[i][j] 是s1[0, i-1] 转换成 s2[0, j-1]的编辑距离
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        //2. 初始状态：d[i][0] = i, d[0][j] = j
        for(int i = 1; i <= n; i++){
            dp[i][0] = i;
        }
        for(int j = 1; j <= m; j++){
            dp[0][j] = j;
        }

        //3. 状态转移方程
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++){
                if (word1[i - 1] == word2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1];
                } else{
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }

        //4. 最终结果
        return dp[n][m];
    }
};
```

**复杂度分析**

时间复杂度：O(nm)
空间复杂度：O(nm)