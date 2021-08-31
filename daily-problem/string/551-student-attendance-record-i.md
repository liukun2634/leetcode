### 551. 学生出勤记录 I

#### 题目

https://leetcode-cn.com/problems/student-attendance-record-i/

#### 思路： 模拟

```cpp
class Solution {
public:
    bool checkRecord(string s) {
        int countA = 0;
        int countL = 0;
        for(char c : s){
            if(c == 'L') {
                countL++;
                if(countL == 3) return false;
            } else {
                if(c == 'A') {
                    countA++;
                    if(countA == 2) return false;
                } 
                countL = 0;
            }
        }
        return true;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)