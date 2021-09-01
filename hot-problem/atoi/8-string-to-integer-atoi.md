## 8. 字符串转换整数 (atoi)

### 题目

https://leetcode-cn.com/problems/string-to-integer-atoi/

### 思路1： 遍历模拟

核心是 string 转换为 10 进制:
```C++
res = res * 10 + (s[start] - '0');
```
此外根据题意增加限制条件（注意指针的挪动）：
1. 丢弃前面空格
2. 检查正负号
3. 读入数字，直到没有数字为止
4. 截取数字 (使用 long long 存储数据/ 使用与INT_MIN和MAX使用除法判断是否大于)


```C++
class Solution {
public:
    int myAtoi(string s) {
        int start = 0, end = s.size();
        //1.丢弃前面空格
        while(start < end && s[start] == ' '){
            start++;
        } 
        //2. 检查正负号
        int flag = false;
        if(start < end && s[start] == '-') {
            flag = true;
            start++;
        } else if(start < end && s[start] == '+') {
            start++;
        }
        long long res = 0;
        //3. 读入数字，直到没有数字为止
        while(start < end && s[start] >= '0' && s[start] <= '9'){
            res = res * 10 + (s[start] - '0');
            //4. 截取数字
            if(res + INT_MIN > 0 && flag) return INT_MIN; 
            if(res - INT_MAX > 0 && !flag) return INT_MAX; 
            start++;
        }
        return flag ? -res : res;
    }
};
```

另一种写法：

- **可以将符号作为变量乘进res**
- 使用int 来存储，不过增加了额外判断。

```C++
class Solution {
public:
    int myAtoi(string s) {
        int start = 0, end = s.size();
        //1.丢弃空格
        while(start < end && s[start] == ' '){
            start++;
        } 
        //2. 检查正负号
        int sign = 1;
        if(start < end && s[start] == '-') {
            sign = -1;
            start++;
        } else if(start < end && s[start] == '+') {
            start++;
        }
        int res = 0;
        //3. 读入数字，直到没有数字为止
        while(start < end && s[start] >= '0' && s[start] <= '9'){
            //4. 截取数字 要在乘之前先判断
            if(res < INT_MIN / 10 || (res == INT_MIN / 10 && s[start] - '0' > - (INT_MIN % 10))) return INT_MIN; 
            if(res > INT_MAX / 10 || (res == INT_MAX / 10 && s[start] - '0' > INT_MAX % 10)) return INT_MAX; 

            res = res * 10 + sign * (s[start] - '0'); //这里把符合乘到结果中
            start++;
        }
        return res;
    }
};
```


**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)


**测试**

正数：正常， 溢出
负数：正常， 溢出
其他字符

### 思路2： 自动机

https://leetcode-cn.com/problems/string-to-integer-atoi/solution/zi-fu-chuan-zhuan-huan-zheng-shu-atoi-by-leetcode-/

表格表示的含义： 当前状态（左列），遇到第一列的情况后，会跳转到什么状态 。

|           | '空格' | '+ / - ' | '数字'    | '其他字符' |
| --------- | ------ | -------- | --------- | ---------- |
| start     | start  | signed   | in_number | end        |
| signed    | start  | end      | in_number | end        |
| in_number | end    | end      | in_number | end        |
| end       | end    | end      | end       | end        |

状态可以用const 来保存

```c++
class Automation {
private:
    string state = "start";
    unordered_map<string, vector<string>> table = 
    {
        {"start",     {"start", "signed", "numbering", "end"}},
        {"signed",    {"end", "end", "numbering", "end"}},
        {"numbering", {"end", "end", "numbering", "end"}},
        {"end",       {"end", "end", "end", "end"}}
    };  //string 可以用const 来保存

    int getIndex(char c){
        if(c == ' ') return 0;
        if(c == '+' || c == '-') return 1;
        if(c >= '0' && c <= '9') return 2;
        return 3;
    }

public:
    int res = 0;
    int sign = 1;

    void update(char c){
        //依据转移矩阵计算当前状态
        state = table[state][getIndex(c)];
        //根据当前状态
        if(state == "signed") {
            if(c == '-') sign = -1;
        } else if(state == "numbering") {
            //截取判断
            if(res < INT_MIN / 10 || (res == INT_MIN / 10 && c - '0' > - (INT_MIN % 10))) {
                res = INT_MIN; 
                state = "end";
                return;
            }
            if(res > INT_MAX / 10 || (res == INT_MAX / 10 && c - '0' > INT_MAX % 10)) {
                res = INT_MAX; 
                state = "end";
                return;
            }
            res = res * 10 + sign * (c - '0');
        }      
    }
};


class Solution {
public:
    int myAtoi(string s) {
        Automation automation;
        for(char c : s){
            automation.update(c);
        }
        return automation.res;
    }
};
```