### 739. 每日温度

#### 题目

https://leetcode-cn.com/problems/daily-temperatures/

#### 思路： 单调栈

参考单调栈的模板，根据题目的要求，这里只有两点需要做改动：

- 栈中记录的是下标，而不是数组的值
- 返回的值记录是栈顶值和当前下标的差值，

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        //存储的是下标, 因为返回结果是下标差值
        stack<int> s;
        //返回结果初始化，因为是逆序遍历
        vector<int> res(n, 0);
        for(int i = n - 1; i >= 0; i--) {
            //将后面温度低的都出栈
            while(!s.empty() && temperatures[s.top()] <= temperatures[i]){
                s.pop();
            }
            //直到找到一个更大温度值，结果为差值
            res[i] = s.empty()? 0 : s.top() - i;
            //压入当前下标 （注意不是温度值）
            s.push(i);
        }
        return res;
    }
};
```