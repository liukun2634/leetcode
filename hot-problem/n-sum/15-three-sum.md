## 15. 三数之和

### 题目

https://leetcode-cn.com/problems/3sum/

### 思路1：哈希表 

固定一个数， 转换成 two-sums。

排序用于处理不重复的情况，但用哈希表其实在记录重复结果时判断要稍微多点。

这里因为不再要求是下标，如果是结果去重，更好的考虑是用双指针思路。


```C++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        //边界处理
        int n = nums.size();
        if(n < 3) return res;

        //排序用于处理不重复的情况
        sort(nums.begin(), nums.end());
        unordered_set<int> set;
        for(int i = 0; i < n; i++){
            if(i != 0 && nums[i] == nums[i - 1]) continue;
            //转换成two-sum
            int target = 0 - nums[i];
            set.clear(); 
            for(int j = i + 1; j < n; j++){
                if(j > i + 2 && nums[j] == nums[j - 2]) continue;
                //放入结果
                if(set.count(target - nums[j])) {
                    res.push_back({target - nums[j], nums[j], nums[i]});
                    //去重， 解决nums[j] == nums[j - 1]同时相加满足target的情况
                    set.erase(target - nums[j]);
                } else{
                    //更新set
                    set.insert(nums[j]);
                }
            }
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n)


### 思路2：双指针

因为不是返回下标可以用双指针解决。


