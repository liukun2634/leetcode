## 41. 缺失的第一个正数

### 题目

(https://leetcode-cn.com/problems/first-missing-positive/)

### 思路1：原数组哈希 （放到合适位置） 

把 i 位置的数 放到合适位置，直到当前位置合适了 或者 当前为负数。

注意避免 `[1, 1]` 数据的问题： nums[nums[i] - 1] != nums[i] 避免循环超时，同时也可以用于结束while 循环（表示当前位置合适）

```C++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        //1 - > 0 2 -> 1
        for(int i = 0; i < n; i++){
            //nums[nums[i] - 1] != nums[i] 避免循环超时
            while(nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]){
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for(int i = 0; i < n; i++){
            if(nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)

### 思路2：原数组哈希 （打标记） 

遍历三次
1、 将负数先转换为 n + 1的正数
2、 num = abs(nums[i]),  把 nums[num - 1]的位置 标记为负数
3、 再次遍历，如果 i 位置为正数，那么就返回 i + 1 否则返回 n + 1


```C++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(nums[i] <= 0) {
                nums[i] = n + 1;
            }
        }

        for(int i = 0; i < n; i++){
            //标记技巧，变为负值，这样能够继续修改 nums[nums[i] - 1]
            int num = abs(nums[i]);
            if(num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }

        for(int i = 0; i < n; i++){
            if(nums[i] > 0){
                return i + 1;
            }
        }
        return n + 1;
    }
};
```


**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)