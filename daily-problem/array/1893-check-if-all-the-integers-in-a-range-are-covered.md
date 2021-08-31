### 1893. 检查是否区域内所有整数都被覆盖

题目：https://leetcode-cn.com/problems/check-if-all-the-integers-in-a-range-are-covered/

#### 思路1： 排序遍历

首先先保证`ranges`数组的按照`start`的大小从小到大排序 (遇到区间数组考虑先排序)。

然后遍历数组，如果`left`在区间内，那么就可以将`end + 1`作为新的`left`。返回结果判断 `left`是否已经超过了`right`即可。

**要点：**
1. 小技巧：遇到区间数组考虑先排序
2. c++ sort 和 lamda 函数应用

```cpp
class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right)
    {
        sort(ranges.begin(), ranges.end(), [](vector<int> r1, vector<int> r2) -> bool { return r1[0] < r2[0]; });
        for (vector<int> range : ranges) {
            if (range[0] <= left && range[1] >= left) {
                left = range[1] + 1;
            }
        }
        return left > right;
    }
};
```
时间复杂度：O(nlogn)

#### 思路2：差分数组
来源：https://leetcode-cn.com/problems/check-if-all-the-integers-in-a-range-are-covered/solution/yi-ti-san-jie-bao-li-you-hua-chai-fen-by-w7xv/

使用差分数组`diff`表示该点是否被覆盖的变化量。
1. 对于每个`start`点，将`diff[start]++`, 表示从start开始有新的覆盖
2. 对于每个`end`点，将`diff[end+1]--`,表示end+1点并没有被覆盖到

这里并没有看出这个差分数组的作用，但一旦对该数组进行前缀和运算sum[i] , 就清楚了。
1. 如果sum[i] 为0， 就表示该位置没有被覆盖过
2. 如果sum[i] 大于0，表示该位置被覆盖过了sum[i]次
3. sum[i] 不会小于0的，因为最终的diff[end+1]-- 保证了前面diff[start]++在这个没有覆盖的位置将会被清除到0。

理解：这个差分数组就是为了标记覆盖情况，最后是通过前缀和将覆盖的结果表现出来。

**要点：**
1. 技巧：区间函数覆盖问题考虑构造差分前缀和
2. c++ 数组初始化

```
class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right)
    {
        const int MAX_NUM = 51;
        //diff要比数据范围多1
        int diff[MAX_NUM + 2] = { 0 };

        //根据start和end构造差分数组diff
        for (vector<int> range : ranges) {
            diff[range[0]]++;
            diff[range[1] + 1]--;
        }

        //计算前缀和
        int sum[MAX_NUM + 1] = { 0 };
        for (int i = 1; i < MAX_NUM + 1; i++) {
            sum[i] = sum[i - 1] + diff[i];
        }

        //判断是否覆盖
        for (int i = left; i <= right; i++) {
            if (sum[i] == 0)
                return false;
        }
        return true;
    }
};
```
n表示ranges数组长度，m表示数据取值范围
时间复杂度：O(n)
空间复杂度: O(m) 

#### 思路3：暴力遍历

看题目要求的1 <= starti <= endi <= 50， 初始化一个51的bool数组，将所有ranges包含的数均置为true。然后遍历left 到right 中的所有值，判断是否均为true。

时间复杂度 O(m*n) 这里 m = 51

要点：
1. 审题目的数据区域，考虑算法复杂度

优化：
1. 在遍历ranges的时候标记时，其考虑区域min(L,start) min(R, end)直接的数据
2. 采用bitmap 保存 bool 数组，最后用位运算来判断是否都覆盖