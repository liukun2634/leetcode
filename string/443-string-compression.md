## 443. 压缩字符串

### 题目

https://leetcode-cn.com/problems/string-compression/

### 思路： 双指针

> 字符串的遍历、翻转、去重等均可以考虑双指针来解决。

这题使用快慢指针，fast 指针用于探寻不等于 slow 指向的字符，然后计算两个指针的间隔就是要压缩的大小。

最后，记得要再次判断fast是不是因为到达末尾而结束，将剩余的一段加到最后结果中。

```C++
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int slow = 0, fast = 0, count = 0, res = 0;
        while(fast < n) {
            //相同就计数, 移到fast指针
            if(chars[slow] == chars[fast]){
                fast++;
                count++;
            } else {   //遇到不相同，压缩前面的字符，并更新slow指针
                chars[res++] = chars[slow];
                setCount(chars, res, count);
                slow = fast;
                count = 0; 
            }
        }
        //处理因为fast到达n而结束的情况
        if(count > 0) {
            chars[res++] = chars[slow];
            setCount(chars, res, count);
        }
        return res;
    }
    void setCount(vector<char>& chars, int& res, int count){
        if(count == 0 || count == 1) return;
        string tmp = to_string(count);
        for(char c : tmp){
            chars[res++] = c;
        }
    }
};
```
#### 复杂度分析：

时间复杂度: $O(n)$ 遍历字符串的复杂度
空间复杂度：$O(1)$ 

前面在setCount时候使用了一个tmp string，也可以改用除法计算count的每位记录在原字符中，从而保证一定是O(1)空间。

```C++
void setCount(vector<char>& chars, int& res, int count){
    if(count == 0 || count == 1) return;
    int left = res, right = res;
    while(count > 0) {
        chars[right++] = '0' + count % 10;
        count = count / 10;
    }
    res = right;
    right = right - 1;
    while(left < right) {
        swap(chars[left++], chars[right--]);
    }
}
```