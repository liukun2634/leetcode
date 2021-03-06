### 动态规划


#### 相关概念

- 动态规划问题的一般形式就是求最值
- 求解动态规划的核心问题是穷举
    -  首先，动态规划的穷举有点特别，因为这类问题存在「重叠子问题」，如果暴力穷举的话效率会极其低下，所以需要「备忘录」或者「DP table」来优化穷举过程，避免不必要的计算。
    - 而且，动态规划问题一定会具备「最优子结构」，才能通过子问题的最值得到原问题的最值。 
    - 另外，虽然动态规划的核心思想就是穷举求最值，但是问题可以千变万化，穷举所有可行解其实并不是一件容易的事，只有列出正确的「状态转移方程」，才能正确地穷举。

**重叠子问题**、**最优子结构**、**状态转移方程**就是动态规划三要素。


#### 动态规划框架

1、定义状态
2、初始状态
3、状态转移方程
4、处理最终结果

```cpp
//1. 定义状态
vector<vector<int>..> dp(n)
//2. 初始状态
dp[0][0][...] = ...
//穷举所有状态
for 状态1 in 状态1的所有取值：
    for 状态2 in 状态2的所有取值：
        for ...
            //3. 状态转移方程
            dp[状态1][状态2][...] = 求最值(选择1，选择2...)

//4. 处理最终结果
for() {
    res = dp[]
}
return res;
```


#### 思路

1. 暴力递归
2. 带备忘录的递归解法
3. dp 数组的迭代解法
4. **滚动数组优化**

