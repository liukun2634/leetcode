## 552. 学生出勤记录 II

### 题目

https://leetcode-cn.com/problems/student-attendance-record-ii/

### 思路1：动态规划 1 

定义状态：
dp 表示 第 i 天 以 0: A, 1: L, 2: P 结尾的出勤奖励的个数 增加了下标3, 4 表示 只有LP 在出勤记录的分别以 L，P结尾的出勤奖励个数

- 增加3, 4 是为了计算以A结尾的出勤奖励个数
- 以L结尾的要看根据前两天的情况分类讨论求和
- 中间结果因为多于2个int相加可能超过int范围，所以使用long long 记录

```cpp
class Solution {
public: 
    const int MOD =1e9+7;
    int checkRecord(int n) {
        if(n == 1) return 3;
        //dp 表示 第 i 天 以 0: A, 1: L, 2: P 结尾的出勤奖励的个数
        //dp 表示 第 i 天 以 3: L, 4: P 结尾的 并且只由L和P组成记录的出勤奖励的个数 
        vector<vector<long long>> dp(n + 1, vector<long long>(5, 0));
       
        dp[1][0] = 1;
        dp[1][1] = 1;
        dp[1][2] = 1;
        dp[1][3] = 1;
        dp[1][4] = 1;
        dp[2][0] = 2;
        dp[2][1] = 3;
        dp[2][2] = 3;
        dp[2][3] = 2;
        dp[2][4] = 2;

        for(int i = 3; i <= n; i++){
            //以A结尾的是 第i - 1 天的只有LP 组成出勤记录个数
            dp[i][0] = dp[i-1][3] + dp[i-1][4]; 
            //以L结尾的要看 第i - 2 天的情况，分类讨论
            dp[i][1] = dp[i-2][0] * 2 + dp[i-2][2] * 2 + dp[i-2][3] + dp[i-2][4] + dp[i-2][1]; 
            //以P结尾就是 第i - 1天 的所有出勤奖励个数
            dp[i][2] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
            //以L结尾的只包含LP记录的要看 i - 2 天的情况
            dp[i][3] = dp[i-2][3] + dp[i-2][4] * 2;
            //以P结尾的只包含LP记录的是 第 i - 1 天 的所有只有LP的出勤奖励个数
            dp[i][4] = dp[i-1][3] + dp[i-1][4];

            //结果全部MOD
            dp[i][1] %= MOD;
            dp[i][2] %= MOD;
            dp[i][4] %= MOD;
            dp[i][3] %= MOD;
            dp[i][0] %= MOD;

        }
        int res = (dp[n][0] + dp[n][1] + dp[n][2]) % MOD;
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)


### 思路2：动态规划 2

应该完全可以按照题目需要定义状态, 这里有三个状态：
第几天，A的个数，L结尾的连续个数

1、定义 dp[i][j][k] 表示第i天，A的个数为j，连续k个L的获得出勤奖励个数 ( 0 <= i <= n, j = 0, 1, k = 0, 1, 2)

2、状态转移方程

//第i天 是A
dp[i][1][0] = dp[i-1][0][0] +  dp[i-1][0][1] + dp[i-1][0][2]
dp[i][1][1] = 0
dp[i][1][2] = 0
dp[i][0][k] = 0

//第i天 是L
dp[i][0][0] = 0
dp[i][j][1] = dp[i-1][j][0]
dp[i][j][2] = dp[i-1][j][1]  


//第i天 是P
dp[i][j][0] = dp[i-1][j][0] +  dp[i-1][j][1] + dp[i-1][j][2]
dp[i][j][1] = 0
dp[i][j][2] = 0

因为最终情况是三类情况求和，所以对他们求和再合并的状态方程：
//由A导致
dp[i][1][0] += dp[i-1][0][k]
//由L导致
dp[i][j][k] += dp[i-1][j][k-1]
//由P导致
dp[i][j][0] += dp[i - 1][j][k]

3、初始状态
dp[0][0][0] = 1; 其余默认为0

4、返回值
dp[n] (j 和 k 求和)

```cpp
class Solution {
public: 
    const int MOD =1e9+7;
    int checkRecord(int n) {
        //默认为0
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        dp[0][0][0] = 1;
        for(int i = 1; i <= n; i++){
            //A情况
            for(int k = 0; k < 3; k++){
                dp[i][1][0] = (dp[i][1][0] + dp[i-1][0][k]) % MOD;
            }
            
            //L情况
            for(int j = 0; j < 2; j++){
                for(int k = 1; k < 3; k++){
                dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k-1]) % MOD;
                }
            }

            //P情况
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 3; k++){
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][k]) % MOD;
                }
            }
        }
        
        int res = 0;
        for(int j = 0; j < 2; j++){
                for(int k = 0; k < 3; k++){
                    res = (res + dp[n][j][k]) % MOD;
                }
        }
        return res;
    }
};
```

#### 状态压缩

由于只i与前面i-1相关，可以压缩状态减小空间

- 中间传递需要新的temp 数组来保存结果
- 这里要改成一般数组，否则用move vector 会超时

```cpp
class Solution {
public: 
    const int MOD =1e9+7;
    //状态压缩
    int checkRecord(int n) {
        int dp[2][3];  
        memset(dp, 0, sizeof(dp)); //使用move 会超时
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            int temp[2][3]; 
            memset(temp, 0, sizeof(temp));
            //A情况
            for(int k = 0; k < 3; k++){
                temp[1][0] = (temp[1][0] + dp[0][k]) % MOD;
            }
            
            //L情况
            for(int j = 0; j < 2; j++){
                for(int k = 1; k < 3; k++){
                temp[j][k] = (temp[j][k] + dp[j][k-1]) % MOD;
                }
            }

            //P情况
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 3; k++){
                temp[j][0] = (temp[j][0] + dp[j][k]) % MOD;
                }
            }
            memcpy(dp, temp, sizeof(temp));
        }
        
        int res = 0;
        for(int j = 0; j < 2; j++){
                for(int k = 0; k < 3; k++){
                    res = (res + dp[j][k]) % MOD;
                }
        }
        return res;
    }
};

```


### 思路3：矩阵快速幂

O(logn)

