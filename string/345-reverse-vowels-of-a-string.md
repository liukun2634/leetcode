## 345. 反转字符串中的元音字母

### 题目

https://leetcode-cn.com/problems/reverse-vowels-of-a-string/

### 思路：双指针 

**翻转问题考虑双指针，分别找到对应的元音字母前后交换。** 

注意指针不能越界，所以在找寻时候也需要判断边界，这里使用左闭右闭区间。

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right = s.size() - 1;
        unordered_set<char> vowels = {'a', 'e', 'i', 'o','u' , 'A', 'E', 'I', 'O', 'U' };
        while(left <= right){
            while(vowels.count(s[left]) == 0  && left <= right){
                left++;
            }
            while(vowels.count(s[right]) == 0 && left <= right){
                right--;
            }
            //确保找到了元音后才交换
            if (left <= right) {
                swap(s[left], s[right]);
                //交换完要更新指针
                left++;
                right--;
            }
        }
        return s;
    }  
};
```

**优化**

- left 和 right 不需要相等时再交换一次
- 由于元音是固定不变的，可以用以static 存储全局，减少内存

```cpp
//固定不变，采用静态全局变量, 减少内存
static const unordered_set<char> vowels = {'a', 'e', 'i', 'o','u' , 'A', 'E', 'I', 'O', 'U' };
class Solution {
public: 
    string reverseVowels(string s) {
        int n = s.size();
        int left = 0, right = n - 1;
        while(left < right){
            while(vowels.count(s[left]) == 0  && left < n){
                left++;
            }
            while(vowels.count(s[right]) == 0 && right > 0){
                right--;
            }
            if(left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
    
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)