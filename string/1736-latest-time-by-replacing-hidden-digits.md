### 1736. 替换隐藏数字得到的最晚时间

#### 题目
https://leetcode-cn.com/problems/latest-time-by-replacing-hidden-digits/

#### 思路1：贪心
就if-else 判断就可以了, 可以改为三元判断运算符

```cpp
class Solution {
public:
    string maximumTime(string time)
    {
        if (time[0] == '?') {
            if (time[1] == '?' || time[1] < '4') {
                time[0] = '2';
            } else {
                time[0] = '1';
            }
        }

        if (time[1] == '?') {
            if (time[0] < '2') {
                time[1] = '9';
            } else {
                time[1] = '3';
            }
        }

        if (time[3] == '?') {
            time[3] = '5';
        }

        if (time[4] == '?') {
            time[4] = '9';
        }

        return time;
    }
};

```

### 思路2： 状态机

抽象成状态机来考虑