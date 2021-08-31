### 1337. 矩阵中战斗力最弱的 K 行

#### 题目

https://leetcode-cn.com/problems/the-k-weakest-rows-in-a-matrix/ 

#### 思路1：二分搜索 + 堆

技巧： 

- 当数组有序时，查找位置就要考虑到二分搜索
- 找Kth问题，一定要用堆来解决。

数组有序不局限于所有数，对于0, 1数组, 也可以考虑到是否相互有序，所以这里可以使用二分搜索。
对于堆，因为最后需要是从小到大排序，所以用K的大顶堆不行（因为返回会从大到小排序），只能用一个空间为N的小顶堆来解决。这里还涉及到C++中`priority_queue`的使用。



```cpp
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> q; //小顶堆
        int m = mat.size();
        int n = mat[0].size();

        for(int i = 0; i < m; i++) {
            //二分搜索
            int left = 0, right = n;
            while(left < right) {
                int mid = left + (right - left) / 2;
                if (mat[i][mid] == 1) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            q.push({left, i});
        }

        vector<int> res;
        while(!q.empty() && k != 0){
            res.push_back(q.top().second);
            q.pop();
            k--;
        }
        return res;
    }
};
```