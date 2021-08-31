### 503. 下一个更大元素 II

#### 题目

https://leetcode-cn.com/problems/next-greater-element-ii/

#### 思路：单调栈

参考单调栈模板，对于**环形的数组，解题技巧是增加一倍数组。**

简单的方案就是先把数组压入栈中，再按照单调栈进行判断。

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        //单调栈
        stack<int> s;
        //因为逆序，需要初始化答案数组
        vector<int> res(n, -1);
        //预压入数组，因为环状
        for(int i = n - 1; i >=0; i--) {
            s.push(nums[i]);
        }
        //倒序遍历，正序出栈
        for(int i = n - 1; i >= 0; i--) {
            //判断是否需要出栈，直到栈中存在比当前值更大的元素
            while(!s.empty() && s.top() <= nums[i]){
                s.pop();
            }
            //将栈顶作为结果记录
            res[i] = s.empty()? -1 : s.top();
            //将当前值入栈
            s.push(nums[i]);
        }
        return res;
    }
};
```

当然，可以利用 `index = i % n` 的方法扩大数组。即使用一次循环遍历 2*n -1 到 0， 然后将`i % n`映射为数组中的值。

**优化**
```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> s;
        vector<int> res(n, -1);
        for(int i = 2 * n - 1; i >= 0; i--) {
            while(!s.empty() && s.top() <= nums[i % n]){
                s.pop();
            }
            res[i % n] = s.empty()? -1 : s.top();
            s.push(nums[i % n]);
        }
        return res;
    }
};
```
