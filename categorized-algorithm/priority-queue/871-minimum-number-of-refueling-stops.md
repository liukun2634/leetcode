## 871. 最低加油次数

### 题目

https://leetcode-cn.com/problems/minimum-number-of-refueling-stops/

### 思路1 ： 贪心 + 优先队列
 
贪心策略：**能不加油就不加油，如果一定要加油的话（即到达不了下一个加油站），就在之前的加油站找一个加油最多的地方加油，** 从而能够保证最后加油的次数最少。

实现逻辑：利用优先队列保存之前所有加油站的油量信息。采用大顶堆，保证堆顶就是之前能够加到最多油的地方。一旦遇到不能够到达下一个加油站，就不断从堆顶抛出最大油量加入（记录加油次数），直到可以到达下一个加油站。如果还是达到不了，就可以直接返回 -1。

额外技巧：可以把 target 视为油量为 0 的加油站，作为最后的到达点。

### 代码

```C++ []
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        //默认是大顶堆
        priority_queue<int> q;
        //target 也作为加油站加入
        stations.push_back({target, 0});
        //start 记录前一个出发点位置， res 记录加油次数
        int start = 0, res = 0;
        for(auto station : stations) {
            startFuel -= station[0] - start;
            //判断是否需要加油
            while(startFuel < 0 && !q.empty()) {
                startFuel += q.top();
                q.pop();
                res++;
            }
            //即使前面所有加油站都加油也到达不了
            if(startFuel < 0) return -1;
            //达到加油站，加入优先队列，为后面做准备
            q.push(station[1]);
            start = station[0];
        }
        return res;
    }
};
```

### 时间复杂度

时间复杂度：O(n*logn) 插入优先队列的时间
空间复杂度：O(n)


### 思路2： 动态规划