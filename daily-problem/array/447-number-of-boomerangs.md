## 447. 回旋镖的数量

### 题目

https://leetcode-cn.com/problems/number-of-boomerangs/

### 思路： 哈希表

首先，根据数据量，分析时间复杂度最多能到 O(n^2)

考虑两层遍历，通过哈希表记录之前的距离，然后在遍历中判断之前是否有相同距离的节点。

```C++
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        unordered_map<int, int> map;
        int n = points.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            map.clear();
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                int dist = distance(points[i], points[j]);
                if(map.count(dist)){
                    //该节点和之前节点可以满足
                    res += map[dist];
                }
                map[dist]++;
            }
        }
        //不考虑顺序，数据最后*2
        return res * 2;
    }

    int distance(vector<int>& point1, vector<int>& point2){
        int x = abs(point1[0]) - abs(point2[0]);
        int y = abs(point1[1]) - abs(point2[1]);
        return x * x + y * y;
    }
};
```

另一种是在最后遍历map，统计结果：

```C++
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        unordered_map<int, int> map;
        int n = points.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            map.clear();
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                int dist = distance(points[i], points[j]);
                map[dist]++;
            }
            //在遍历一遍后，统计结果计入最后结果中
            for(auto &[dist, cnt] : map){
                res += cnt * (cnt - 1);
            }
        }
        return res;
    }

    int distance(vector<int>& point1, vector<int>& point2){
        int x = point1[0] - point2[0];
        int y = point1[1] - point2[1];
        return x * x + y * y;
    }
};
```


**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n)