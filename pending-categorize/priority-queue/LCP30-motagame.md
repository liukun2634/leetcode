## LCP 30. 魔塔游戏

### 题目

https://leetcode-cn.com/problems/p0NxJO/

### 思路1：贪心 + 优先队列 

用一个小顶堆存储前面负数值（堆顶绝对值最大），如果存在到达不了的情况就调整堆顶到最后。

注意数据范围，需要将和用`long long` 保存。

```C++
class Solution {
public:
    int magicTower(vector<int>& nums) {
        int n = nums.size();
        priority_queue<int, vector<int>, greater<int>> q;
        int res = 0;
        //调整到末尾的负数
        long long monster = 0;
        //当前血量
        long long blood = 1;
        for(int i = 0; i < n; i++) {
            blood += nums[i];
            if(nums[i] < 0) {
                q.push(nums[i]);
                 //需要调整，移动之前最小的负数到末尾
                if(blood <= 0){
                    res++;
                    //加的是正值
                    monster += abs(q.top());
                    blood += abs(q.top()); 
                    //因为已经压入负值，肯定不为空
                    q.pop(); 
                }
                //只需调整一次，因为之前堆顶的负数肯定比这次加入的要大或者相等
            }
        }
        return blood <= monster ?  -1 : res;
    }
};
```

**复杂度分析**

时间复杂度：O(n*logn) 插入优先队列的时间
空间复杂度：O(n)

**优化**

可以一开始就统计所有的正数和负数的差值，决定是否返回-1