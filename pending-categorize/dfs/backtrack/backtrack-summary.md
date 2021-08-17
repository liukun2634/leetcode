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

### 类型1： 排列 组合 子列问题

使用used数组进行标记

### 类型2： 小岛问题

使用visited数组进行标记

### 技巧1： 状态压缩

用DFS 遍历，需要观察数据个数，如果数组长度有限，可以考虑使用int 代替 visited 数组


### 技巧2： 记忆化

增加cache数组



### 技巧3： 转换成动态规划