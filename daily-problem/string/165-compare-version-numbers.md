## 165. 比较版本号

### 题目

https://leetcode-cn.com/problems/compare-version-numbers/

### 思路： 双指针 

考虑while 循环，两次判断边界，这里先使用尾递归做。（其实还是判断了两次边界）

```C++
class Solution {
public:
    int compareVersion(string version1, string version2) {
        return compareVersion(version1, 0, version2, 0);
    }

    int compareVersion(string& version1, int start1, string& version2, int start2) {
        if(start1 >= version1.size() && start2 >= version2.size()) return 0;

        int number1 = getNumber(version1, start1);
        int number2 = getNumber(version2, start2);
        if(number1 != number2) return number1 > number2? 1: -1; 
        return compareVersion(version1, start1 + 1, version2, start2 + 1);
    }

    int getNumber(string& version, int& start){
        int number = 0;
        int n = version.size();
        while(start < n && version[start] == '0' && version[start] != '.'){
            start++;
        }
        while(start < n && version[start] != '.'){
            number *= 10;
            number += version[start] - '0';
            start++;
        }
        return number;
    }
};
```

优化：
version 前面是0 start也无需跳转，
string 转换 10 进制时的变化公式

```C++
number = number * 10 +  (version[start] - '0');
```

**复杂度分析**

时间复杂度：O(n+m)
空间复杂度：O(1)