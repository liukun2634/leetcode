### 26. 删除有序数组中的重复项

#### 题目

https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/

#### 思路：快慢指针

fast指针是探路指针，slow指针维护是一个不会有重复指针的数组。使用一个while循环保证fast在范围内，然后分别判断slow 和 fast 更新的条件。

注意：
- nums数组空的判断
- 循环条件是 while(fast < nums.size());
- 判断条件是nums[fast] != nums[slow], 同样使用于两者下标为0的情况
- 返回应为数组长度


```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //空数组判断
        if(nums.size() == 0) return 0;

        int slow = 0, fast = 0;
        while(fast < nums.size()) {
            //更新slow指针
            if(nums[fast] != nums[slow]) {
                slow++;
                // 维护 nums[0, slow] 无重复
                nums[slow] = nums[fast];
            }
            fast++;
        }
        //返回数组长度为索引 + 1
        return slow + 1;
    }
};
```