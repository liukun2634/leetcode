### 567. 字符串的排列

#### 题目

https://leetcode-cn.com/problems/permutation-in-string/

#### 思路1： 滑动窗口

套用滑动窗口模板。是 76 题的修改版。

这里在收缩窗口的条件是：当窗口长度大于等于（其实就是等于）s1字符串的长度的时候。这时候如果刚好valid 满足就可以直接返回，否则就是收缩left，到窗口大小小于s1字符串的长度。

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> need, window;
        for(char c : s1) {
            need[c]++;
        }

        int left = 0, right = 0, valid = 0;
        while(right < s2.size()){
            //c 是要加入的节点
            char c = s2[right];
            right++;
            //窗口更新之后操作         
            if(need.count(c)){
                window[c]++;
                if(need[c] == window[c]) valid++;  
            } 

            //满足缩小窗口的条件
            while(right - left >= s1.size()) {
                //存在排列，窗口刚好在s1长度时候，满足所有need
                if(valid == need.size()) 
                    return true;
                
                //d 是要删除的节点
                char d = s2[left];
                left++;
                //窗口更新之后操作  
                if(need.count(d)) {
                    if(need[d] == window[d]) valid--;
                    window[d]--;
                }
            }
        }
        return false;
    }
};
```


#### 思路2：双指针

参考：

https://leetcode-cn.com/problems/permutation-in-string/solution/zi-fu-chuan-de-pai-lie-by-leetcode-solut-7k7u/ 