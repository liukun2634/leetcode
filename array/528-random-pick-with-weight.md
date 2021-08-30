## 528. 按权重随机选择

### 题目

https://leetcode-cn.com/problems/random-pick-with-weight/

### 思路：前缀和 + 二分搜索 

利用前缀和保存每个数可以对应的区域，然后对随机生成的数进行二分搜索（左侧）。

```C++
class Solution {
public:
    //存储前缀和
    vector<int> sums;
    Solution(vector<int>& w) {
        int n = w.size();
        sums.resize(n);
        sums[0] = w[0];
        for(int i = 1; i < n; i++){
            sums[i] = w[i] + sums[i - 1];
        }
    }
    
    int pickIndex() {
        int n = sums.size();
        int max = sums[n - 1];
        int target = rand() % max + 1;
        int left = 0, right = n - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(sums[mid] >= target) {
                right = mid - 1; 
            } else {
                left = mid + 1;
               
            }
        }
        //肯定能找到left，所以不需要额外判断
        return left;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：