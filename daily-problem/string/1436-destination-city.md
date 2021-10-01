## 1436. 旅行终点站

### 题目

https://leetcode-cn.com/problems/destination-city/

### 思路： 哈希表

```C++
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_map<string, int> map;
        for(auto& path : paths){
            map[path[0]]++;
            if(!map.count(path[1])){
                map[path[1]] = 0;
            }
        }
        for(auto& [key, value] : map){
            if(value == 0) return key;
        }
        return "";
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：