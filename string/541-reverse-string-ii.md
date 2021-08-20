## 541. 反转字符串 II

### 题目

https://leetcode-cn.com/problems/reverse-string-ii/

### 思路： 双指针

翻转依然考虑双指针，这里就是找2k，翻转前k位。

翻转模板：
```cpp
void reverse(vector<int>& nums, int left, int right) {
    while(left < right) {
        swap(nums[left++], nums[right--]);
    }
}
```

简单题写简单更考验功底。

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        int idx = 0;
        while(idx < n) {
            int left = idx, right = idx + k - 1 >= n ? n - 1 : idx + k - 1;
            while(left < right) {
                swap(s[left++], s[right--]);
            }
            idx = idx + 2*k; //idx + 2 * k - 1 + 1
        }
        return s;
    }
};
```

简化：

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for(int left = 0; left < n; left = left + 2 * k){
            int right = min(n - 1, left + k - 1);
            reverse(s, left, right);
        }
        return s;
    }

    void reverse(string& s, int left, int right) {
        while(left < right) {
            swap(s[left++], s[right--]);
        }
    }
};
```


**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)