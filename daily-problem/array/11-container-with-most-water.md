## 11. 盛最多水的容器

### 题目

https://leetcode-cn.com/problems/container-with-most-water/

### 思路：双指针

两个指针分别从两边向中间遍历，如果相比另一个高度更小，就相向移到。期间不断计算面积，保留最大值。

```C++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int res = 0;
        while(left < right){
            int w = right - left;
            int h = min(height[left], height[right]);
            res = max(res, w * h);
            if(height[left] > height[right]) {
                right--;
            } else{
                left++;
            }
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)