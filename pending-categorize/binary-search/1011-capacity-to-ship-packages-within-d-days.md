### 1011. 在 D 天内送达包裹的能力

#### 题目

https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/

#### 思路： 二分搜索

从例题可以看出来包裹不能被拆分，所以先按照题目写出f(x);

判断区间大小：左侧一定是weights中的最大值，右侧是所有weights[i]的和（一天可以运完所有的）;

先可以按照模板写，然后优化if else判断分支。这里一定有一个最左端解，所以不需要最后判断是否越界。


```cpp
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = 0, right = 0;
        for(auto weight : weights) {
            left = max(left, weight);
            right += weight; //所有的货物加起来的运载量，一天运完
        }
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(f(weights, mid) > days) {
                left = mid + 1;
            } else { //向左侧找最小
                right = mid - 1;
            } 
        }
        //肯定能找到left，不需要额外判断
        return left;

    }

    //x 运载能力
    //f(x) 送达天数
    int f(vector<int>& weights, int x) {
        int days = 1;
        int cap = x;
        for(int i = 0; i < weights.size(); i++) {
            if (cap < weights[i]) {
                days++;
                cap = x;
            }
            cap = cap - weights[i];
        }
        return days;
    }
};

```