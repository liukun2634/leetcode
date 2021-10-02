## 405. 数字转换为十六进制数

### 题目

https://leetcode-cn.com/problems/convert-a-number-to-hexadecimal/

### 思路： 进制转换

负数的处理是加上 0x100000000 (2 ^ 32), 转换成long 来计算

```C++
class Solution {
public:
    string toHex(int N) {
        string res;
        long num = N;
        if(num == 0) return "0";
        if(num < 0) num = num + 0x100000000;
        while(num > 0){
            int temp = num % 16;
            if(temp >= 10){
                temp = temp - 10;
                res += (temp + 'a');
            } else{
                res += (temp + '0');
            }
            num = num / 16;
        }
        reverse(res.begin(), res.end());
        return res;
    }

};
```

**复杂度分析**

时间复杂度：
空间复杂度：