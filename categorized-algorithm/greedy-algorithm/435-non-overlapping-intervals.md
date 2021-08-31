### 435. 无重叠区间

#### 题目

https://leetcode-cn.com/problems/non-overlapping-intervals/

#### 思路1：贪心

该题是调度区间的经典题。

假设 `intervals[i]` 的区间表示为 `[start_i, end_i]`，整体的思路就是：

- 在所有可以选择区间中，选择一个结束时间最小的区间 k 作为首区间 [start_k, end_k]。
- 对于所有其他的区间 i，一定满足 end_i > end_k:
   - 如果有 start_i < end_k, 则一定说明区间i 与 k 重叠，可以将重叠区间 i 记录下来并去除。
   - 如果有 start_i > end_k, 那么说明这两个区间不重叠。
- 继续搜寻结束时间第二小的区间，同样去除所有重复的区间，以此类推，最后剩下的区间就是留下的非重叠的区间，即移除了最少的重叠区间。

我们可以一开始对`intervals`按照结束时间从小到大排序，这样对`intervals`只需要遍历一遍就能够得到最小重叠区间个数。

注意: 写sort 函数一定要用引用参数，否则会超时

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n == 0) return 0;

        //按照end升序排列
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            return a[1] < b[1];
        });
        //记录重叠区间个数
        int count = 0; 
        int end = intervals[0][1];
        for(int i = 1; i < n; i++){
            //无重叠区间，可以更新end
            if(intervals[i][0] >= end){
                end = intervals[i][1];
            } else {
                count++;
            }
        }
        return count;
    }
};
```


**优化**

由于重叠区间较多，可以通过记录非重叠区间个数，来优化时间。

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n == 0) return 0;

        //按照end升序排列
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            return a[1] < b[1];
        });
        //记录非重叠区间个数
        int count = 1; 
        int end = intervals[0][1];
        for(int i = 1; i < n; i++){
            //更新end
            if(intervals[i][0] >= end){
                count++;
                end = intervals[i][1];
            }
        }
        return n - count;
    }
};
```

**复杂度分析**

时间复杂度：O(nlogn) 排序算法
空间复杂度：O(logn) 快速排序的栈空间

#### 思路2: 另一种贪心

我们可以一开始对`intervals`按照**开始时间从小到大排序**， 记录最小的开始区间的`end`

- 如果有 start_i < end, 则一定说明区间 i 会重叠，这里的处理有区别：需要把 min(end_i, end) 作为新的 end 继续去比较， 并增加重叠区间个数。
- 如果有 start_i >= end, 那么说明这两个区间不重叠，end 更新为 end_i。 

```cpp
class Solution {
public:
    //贪心方法 2
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n == 0) return 0;

        //按照start升序排列
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            return a[0] < b[0];
        });

        //记录重叠区间个数
        int count = 0; 
        int end = intervals[0][1];
        for(int i = 1; i < n; i++){
            //当重叠时，更新的end为两者最小值
            if(intervals[i][0] < end){
                end = min(intervals[i][1], end);
                count++;
            } else {
                //如果没有重叠则更新end
                end = intervals[i][1];
            }
        }
        return count;
    }
};
```

仔细思考会发现，该方法其实就是思路1的逆序，先排的是`start`，但是需要不断的更新找到最小的end。


#### 思路3：动态规划

参考：
https://leetcode-cn.com/problems/non-overlapping-intervals/solution/wu-zhong-die-qu-jian-by-leetcode-solutio-cpsb/


所有的 n 个区间按照左端点（或者右端点）从小到大进行排序， 使用动态规划的方法求出区间数量的最大值。

1. 定义状态： dp[i] 表示**以区间 i 为结尾区间，可以选出的不重叠区间数量的最大值**

2. 状态转移方程： 如果 end[j] < start[i], 那么 dp[i] = max(dp[j]) + 1 (j < i)

3. 初始状态： dp[i] = 1 

4. 返回结果： max(dp[i])

**复杂度分析**

时间复杂度：O(n^2) 
空间复杂度：O(n) 

动态规划思路的本质是求一个最长上升子序列。可以参考 300 题 优化到 O(nlogn)。


