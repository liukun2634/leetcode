### 875. 爱吃香蕉的珂珂

#### 题目

https://leetcode-cn.com/problems/koko-eating-bananas/

#### 思路：二分搜索

注意这里的f(x) 是单调递减的，在left和right 更新时需要注意。

这里的判断分支最后可以优化合并，为了清晰可以先都写出来。

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        //确定区间，使用左闭右闭
        int left = 1, right= 1e9;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            //搜索左侧
            if(f(piles, mid) > h) {
                 left = mid + 1;
            } else if (f(piles, mid) < h) {
                 right = mid - 1;
            } else if (f(piles, mid) == h) {
                right = mid - 1;
            }
        }
        return left;
    }

    //x 速度 (根/小时)
    //f(x) 花费时间 (小时)
    int f(vector<int>& piles, int x) {
        int hours = 0;
        for(int i = 0; i < piles.size(); i++) {
            hours += piles[i] / x;
            //如果剩下少于x根，那么在这一个小时内只吃剩下的，不会再吃更多
            if (piles[i] % x > 0) {
                hours++;
            }
        }
        return hours;
    }
};

```