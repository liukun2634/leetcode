## 223. 矩形面积

### 题目

https://leetcode-cn.com/problems/rectangle-area/

### 思路：数学求面积


```C++
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int height = max(0, min(ay2, by2) - max(ay1, by1));
        int width = max(0, min(ax2, bx2) - max(ax1, bx1));
        return (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1) - height * width;
    }
};
```

**复杂度分析**

时间复杂度：O(1)
空间复杂度：O(1)