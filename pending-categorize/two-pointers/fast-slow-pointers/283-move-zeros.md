### 283. 移动零

#### 题目

https://leetcode-cn.com/problems/move-zeroes/

#### 思路：快慢指针

27题的简化版，考虑到remove的元素就是0就可以了。

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        //空数组判断
        if (nums.size() == 0) return;

        int slow = 0, fast = 0;
        while(fast < nums.size()){
            //更新slow指针
            if (nums[fast] != 0) {
                nums[slow] = nums[fast];
                //维护 nums[0, slow - 1] 不包含val
                slow++;
            }
            fast++;
        }

        //将后面数组置为0
        while(slow < nums.size()){
            nums[slow] = 0;
            slow++;
        }
    }
};

```