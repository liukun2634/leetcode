## 1. 两数之和

### 题目

https://leetcode-cn.com/problems/two-sum/

### 思路1： 哈希表

哈希表存储在遍历下标 i 之前的值和下标的键值对， 用于返回值。

遍历数组，根据当前值x， 寻找哈希表是否存在target - x 的key：
- 如果存在，直接返回结果
- 如果不存在，当前值加入哈希表，继续寻找

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        //存储<值,下标>
        unordered_map<int, int> map;
        for(int i = 0; i < n; i++) {
            //只要存在一个就可以返回
            if(map.count(target - nums[i])) return {map[target - nums[i]], i};
            //当前值计入哈希表
            map[nums[i]] = i;
        }
        return {};
    }
};
```

**复杂度分析**

时间复杂度：O(N) 
空间复杂度：O(N)



**注意： 因为要返回的是下标，所以并不能采用排序后二分/双指针的做法。不然又需要额外的哈希表，不如当前方法。**