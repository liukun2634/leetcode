## 881. 救生艇

### 题目

https://leetcode-cn.com/problems/boats-to-save-people/

### 思路： 贪心 + 双指针

通过对数组排序，看最大的是否能够挑选最小的加入，否则就最大的一个人乘船。

双指针来移动标识没有乘船的人。

```C++
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end(), greater<int>());
        int left = 0, right = people.size() - 1;
        int res = 0;
        while(left <= right){
            if(people[left] + people[right] <= limit && left != right){
                left++;
                right--;
            } else{
                left++;
            }
            res++;
        }
        return res;
    }
};
```
**复杂度分析**

时间复杂度：O(nlogn)
空间复杂度：O(logn)

简化代码：
```C++
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end(), greater<int>());
        int left = 0, right = people.size() - 1;
        while(left <= right){
            if(people[left] + people[right] <= limit){
                right--;
            }
            left++;
        }
        return left;
    }
};
```