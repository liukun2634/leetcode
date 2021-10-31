## 215. 数组中的第K个最大元素

### 题目

https://leetcode-cn.com/problems/kth-largest-element-in-an-array/

### 思路： 选择算法

```C++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        partition(nums, 0, nums.size()-1, k);
        return nums[k - 1];
    }

    void partition(vector<int>& nums, int left, int right, int k){
        //1. 返回条件
        if(left >= right) return;

        //2. 随机选择
        int random = left + rand() % (right - left);
        swap(nums[left], nums[right]);

        //3. 初始化 pivot，i 和 j
        int pivot = nums[left];
        int i = left, j = right;

        //4. 循环
        while(i < j){
            //先从右边找一个, 右边没找到说明不用交换了
            while(nums[j] <= pivot && i < j){
                j--;
            } 
            //左边必须从i开始, 左边找一个小的值，才去交换 
            //(如果只有一个大的了, 那么 i == j， 最后与left交换)
            while(nums[i] >= pivot && i < j){
                i++;
            }
            swap(nums[i], nums[j]);
        }
        
        //最后交换left 到合适 i 位置
        //如果没有找到，i == left
        swap(nums[i], nums[left]);

        //5. 递归
        if(i < k - 1) partition(nums, i + 1, right, k);
        if(i > k - 1) partition(nums, left, i - 1, k);
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：