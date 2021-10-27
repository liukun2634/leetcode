## 224. 基本计算器

### 题目

https://leetcode-cn.com/problems/basic-calculator/

### 思路： 双栈

1. 左括号 记录到 ops 中
2. 遇到右括号就一直计算到左括号，最后pop 左括号
3. 遇到数字，就一直统计数字，记录到 nums
4. 遇到运算符，就把之前相等级别和更高级别运算符计算完成

细节判断，nums中push 一个 0

```C++
class Solution {
public:
    int calculate(string s) {
        stack<int> ops;
        stack<int> nums;
        
        //细节处理，开始为正负数 "-2 + 1"
        nums.push(0);

        int n = s.size();
        for(int i = 0; i < n; i++){
            char c = s[i];
            //处理空格
            if(c == ' ') continue; 

            if(c == '('){
                //1. 如果是 左括号 压入
                ops.push(c);
            } else if(c == ')'){
                //2. 如果是 右括号 则计算到左括号为止 
                while(!ops.empty() && ops.top() != '('){
                    calc(nums, ops);
                }
                //最后弹出'('
                ops.pop();
            } else if(c >= '0' && c <='9'){
                //3. 如果是数字要一直统计出来全部的值 压入
                int num = 0;
                int j = i;
                while(j < n && s[j] >= '0' && s[j] <= '9'){
                    num = num * 10 + (s[j] - '0');
                    j++;
                }
                nums.push(num);
                i = j - 1;
            } else {
                //细节处理 "1-(-2)" "1-(+2)"
                if(i > 1 && s[i - 1] == '('){
                    nums.push(0);
                }

                //4. 如果有更高或者相同的运算符，需要在这里计算之前中更高或者相同的运算符
                while(!ops.empty() && ops.top() != '('){
                    calc(nums, ops);
                }
                //压入运算符
                ops.push(c);
            }
        }
        //5. 最后计算剩余值
        while(!ops.empty()){
            calc(nums, ops);
        }
        return nums.top();
    }

    //每次计算一次
    void calc(stack<int>& nums, stack<int>& ops){
        //1. 判断 nums 情况
        if(nums.empty() || nums.size() < 2) return;
        //2. 判断 ops 情况
        if(ops.empty()) return;

        //3. 注意堆顶是b
        int b = nums.top();
        nums.pop();
        int a = nums.top();
        nums.pop();

        char op = ops.top();
        ops.pop();

        //4. 注意堆顶是b
        int ans = 0;
        if(op == '+') ans = a + b;
        else if(op == '-') ans = a - b;

        //5.计算结果压入
        nums.push(ans);
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)