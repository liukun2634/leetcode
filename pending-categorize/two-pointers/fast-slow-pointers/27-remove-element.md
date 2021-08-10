### 27. 移除元素

#### 题目

https://leetcode-cn.com/problems/remove-element/

#### 思路：快慢指针 

类似26题，slow指针移到是当fast指针指向的值不为val。

这里和有序数组去重的解法有一个重要不同，我们这里是先给 nums[slow] 赋值然后再给 slow++，这样可以保证 nums[0，slow-1] 是不包含值为 val 的元素的，最后的结果数组长度就是 slow。

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //空数组判断
        if (nums.size() == 0) return 0;

        int slow = 0, fast = 0;
        while(fast < nums.size()) {
            //更新slow的条件
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                //维护 nums[0, slow - 1] 不包含val
                slow++;
            }
            fast++;
        }
        //返回的slow是数组长度
        return slow;
    }
};
```