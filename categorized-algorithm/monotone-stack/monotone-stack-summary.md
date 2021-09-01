# 单调栈

应用题目出现最近最小/最大的情况。

标准题目：给你一个数组 nums，请你返回一个等长的结果数组，结果数组中对应索引存储着下一个更大元素，如果没有更大的元素，就存-1。

### 单调栈逆序模板
倒序遍历整个数组，将值压入栈中。如果栈中存在比当前值小的，就把他们直接出栈（因为前面也只会看到当前值了，不会再往后了），直到栈中有一个更大的值，即当前下标的对应的后面最大值。

```cpp
vector<int> nextGreaterElement(vector<int>& nums) {
    //存放答案的数组，记得要初始化好
    vector<int> res(nums.size()); 
    //栈可以存放值，也可以存放下标，取决于答案需求是值还是下标
    stack<int> s;
    // 1. 倒序遍历数组，这样是正的出栈
    for (int i = nums.size() - 1; i >= 0; i--) {
        // 2. 根据是否比当前值大，判定是否需要出栈
        while (!s.empty() && s.top() <= nums[i]) {
            // 小的值一律出栈
            s.pop();
        }
        //3. 经过步骤2后，栈顶元素就是最近的最大元素
        res[i] = s.empty() ? -1 : s.top();
        //4. 将当前值放入栈中，继续向前遍历
        s.push(nums[i]);
    }
    return res;
}
```

使用单调栈时间复杂度O(n)， 空间复杂度 O(n).

关键的4步：
- 倒序遍历数组
- while (栈是否为空, 需要出栈) {s.pop()}
- 记录栈顶元素作为结果
- 将当前值放入栈中

#### 单调栈正序模板

正序的思路与逆序是相反的。正序遍历先要通过栈记录之前值的下标。当正序遍历到后面的时候，若存在当前值比栈顶值大时候，就需要出栈。这时候再更新之前的下标对应的后面最大元素为当前值。

而逆序遍历的更新再每次达到节点的时候，而不是后面再去更新之前的值。相比下，逆序更容易理解，不容易出问题。

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        //初始化为默认值
        vector<int> res(nums.size(), -1);
        //单调栈记录的是下标
        stack<int> s;
        //1. 正序遍历，逆序出栈（从后往前更新值）
        for (int i = 0; i < n; ++i) {
            //2. 需要出栈条件，当前位置值要比之前的值要大
            while (!s.empty() && nums[i] > nums[s.top()]) {
                //3. 更新之前节点对应的最近最大元素为当前下标
                res[s.top()] = nums[i];
                //4. 之前的节点出栈
                s.pop();
            }
            //5. 将当前下标入栈
            s.push(i);
        }
        return res;
    }
};
```


#### 提升

对于单调栈，可以通过使用一个静态数组，并且增加两个指针模拟栈来减少时间。