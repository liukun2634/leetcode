### 回溯算法 （DFS 算法）

#### 模板

回溯问题一定要画好决策树啊！

```cpp
result = []
void backtrack(路径, 所有选择, 已做选择列表):
    if 满足结束条件:
        result.add(路径)
        return

    for 选择 : 所有选择:
        if(选择 not in 已做选择列表) {
            加入选择列表
            backtrack(路径, 选择列表)
            撤销选择
        }
```

参考：
https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liweiw/



**时间复杂度计算:**  根据决策树每个节点的分支树决定

假设是个k 叉树， 那么遍历树的时间复杂度就是 O (k^ n)， n为树高（一般是结果数组的长度）

当然 如果剪枝存在，第一层k 叉，第二层 k - 1 叉，... 那么 结果是 k! (全排列)，当然最后返回结果时操作还需要额外相乘，比方全排列最后要把结果压入，就需要 n * k!

### 类型1： 排列 组合 子集问题

46. 全排列（中等）
47. 全排列 II（中等）
39. 组合总和（中等）
40. 组合总和 II（中等）
77. 组合（中等）
78. 子集（中等）
90. 子集 II（中等）
60. 第 k 个排列（中等）
93. 复原 IP 地址（中等）


全排列问题使用used数组进行标记

对于组合和子集问题，使用 i + 1 作为下一个开始，所以不需要used 来重复标记

对于组合和子集问题，也可以使用mask 来标记下标，将 n！问题转换 2^n

对于组合和子集问题，还可以套用递归遍历模板，遍历得到所有子序列（树遍历）
https://leetcode-cn.com/problems/subsets/solution/zi-ji-by-leetcode-solution/ 

dfs遍历求子序列模板
```cpp
vector<int> t;
void dfs(int cur, int n) {
    if (cur == n) {
        // 记录答案
        // ...
        return;
    }
    // 考虑选择当前位置
    t.push_back(cur);
    dfs(cur + 1, n, k);
    t.pop_back();
    // 考虑不选择当前位置
    dfs(cur + 1, n, k);
}
```

**排序预处理**
- 如果有重复数字，先排序，然后通过相邻数字是否相同决定要不要挪位置
- 如果是对数组求和，达到某个target，也可以先排序做预处理，然后便于剪枝


如果最后的结果是所有的数字，那么需要visited，同时回溯里面是循环，判断是不是visited。

如果最后结果是部分数字，那么可以用start表明当前数字，然后判断选择该数字和不选择该数字。

### 类型2： 小岛问题

使用visited数组进行标记

### 技巧1： 状态压缩

用DFS 遍历，需要观察数据个数，如果数组长度有限，可以考虑使用int 代替 visited 数组


### 技巧2： 记忆化

增加cache数组



### 技巧3： 转换成动态规划