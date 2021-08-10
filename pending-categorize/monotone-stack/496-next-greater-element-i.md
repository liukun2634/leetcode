### 496. 下一个更大元素 I

#### 题目

https://leetcode-cn.com/problems/next-greater-element-i/

#### 思路：单调栈

对于求最近的最大/最小的例题，就考虑使用 **单调栈** 来寻找数组中每个值对应的下一个最大值。

因为题目希望得到是`nums2`中的子数组`nums1`对应的下一个最大值，所以可以先通过 **哈希表** 来存储所有`nums2` 中的映射结果，最后根据哈希表把结果更新到`nums1`上。

**单调栈** 根据数组遍历方向这里分为 **正序遍历** 和 **逆序遍历** 两种解法。

#### 单调栈(正序遍历)

**代码逻辑：**

- 正序遍历 `nums2`, 将当前元素与栈顶元素比较：
  - 如果当前元素 >= 栈顶元素，更新 `map` 的栈顶元素下标的映射结果，弹出栈顶元素
  - 如果当前元素 < 栈顶元素，入栈
- 遍历`nums1`, 根据`map` 结果，修改为映射后下一个最大值，并返回`nums1`

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        //记录的是下标
        stack<int> s;
        //记录每个值对应的下一个最大值
        unordered_map<int, int> map;
        //正序遍历
        for(int i = 0; i < nums2.size(); i++){
            while(!s.empty() && nums2[s.top()] <= nums2[i]){
                //更新map
                map[nums2[s.top()]] = nums2[i];
                s.pop();
            }
            //map初始化
            map[nums2[i]] = -1;
            s.push(i);
        }
        //处理返回
        for(int i = 0; i < nums1.size(); i++) {
            nums1[i] = map[nums1[i]];
        }
        return nums1;
    }
};
```

#### 单调栈(逆序遍历)

**代码逻辑：**

- 倒序遍历 `nums2`, 将当前元素与栈顶元素比较：
  - 如果当前元素 >= 栈顶元素，弹出栈顶元素，直到栈顶
  - 如果当前元素 < 栈顶元素，更新 `map` 当前值的映射结果，入栈
- 遍历`nums1`, 根据`map` 结果，修改为映射后下一个最大值，并返回`nums1`

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        //记录的是数组的值
        stack<int> s;
        //记录每个值对应的下一个最大值
        unordered_map<int, int> map;
        //倒序遍历
        for(int i = nums2.size() - 1; i >= 0; i--){
            while(!s.empty() && s.top() <= nums2[i]){
                s.pop();
            }
            //更新map
            map[nums2[i]] = s.empty() ? -1 : s.top();
            s.push(nums2[i]);
        }
        //处理返回
        for(int i = 0; i < nums1.size(); i++) {
            nums1[i] = map[nums1[i]];
        }
        return nums1;
    }
};
```

#### 复杂度分析

假设 `nums1`的长度为 $M$, `nums2`的长度为 $N$
时间复杂度：$O(N + M)$  
空间复杂度：$O(N)$
