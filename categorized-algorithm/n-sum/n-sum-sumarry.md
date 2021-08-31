# Two-sum 系列

## Two sum

思路：固定一个数，寻找另一个数

寻找一个数：
- O(1) : 哈希表 插入时间为 O(n)
- O(logn) : 二分搜索 排序时间是O(nlogn)
- O(n): 双指针 排序时间是O(nlogn)

寻找小于一个值的一系列数：
- O(logn) : 二分搜索 排序时间是O(nlogn)
- O(n): 双指针 排序时间是O(nlogn)

思路：能用哈希尽可能用哈希，当是范围时候就只能用二分或者双指针了。
如果数据存在重复，则考虑是双指针。


## Two sum

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
            map[nums[i]] = i;
        }
        return {};
    }
};

```