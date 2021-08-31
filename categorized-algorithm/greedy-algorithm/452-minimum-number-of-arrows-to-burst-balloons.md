### 452. 用最少数量的箭引爆气球

#### 题目

https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons/

#### 思路： 贪心

思路等同于 题435， 区间贪心法，对 `end`从小到大排序，去掉所有重叠区间后就是最后结果。

```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        sort(points.begin(), points.end(), [](const auto& a, const auto& b){
            return a[1] < b[1];
        });

        int res = 1;
        int end = points[0][1];
        for(int i = 1; i < n; i++){
            if(points[i][0] > end){
                end = points[i][1];
                res++;
            } 
        }
        return res;
;
    }
};
```

**复杂度分析**

时间复杂度：O(nlogn)
空间复杂度：O(logn) 排序栈空间