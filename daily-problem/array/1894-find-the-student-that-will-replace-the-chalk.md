## 1894. 找到需要补充粉笔的学生编号

### 题目

https://leetcode-cn.com/problems/find-the-student-that-will-replace-the-chalk/

### 思路1： 模拟

注意sum 数据可能溢出int，这里是利用比k 大的特性，更一般做法就是用long long 保存。

```C++
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int sum = 0, n = chalk.size();
        for(int i = 0; i < n; i++){
            sum += chalk[i];
            //防止溢出
            if(sum > k) return i;
        }
        k = k % sum;
        for(int i = 0; i < n; i++){
            k = k - chalk[i];
            if(k < 0) return i;   
        }
        return 0;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)

### 思路2： 前缀和 + 二分

因为构建前缀和是O(n)，所以使用二分并没有比模拟提升时间复杂度，空间复杂度反而增加到了O(n).




右侧二分搜索：

因为肯定存在，所以对于left不需要额外的边界判断,
left最终是right + 1，所以是大于等于k的下标。

```C++
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int n = chalk.size();
        vector<long long> sum(n);
        sum[0] = chalk[0];
        for(int i = 1; i < n; i++){
            sum[i] = sum[i - 1] + chalk[i];
        }
        k = k % sum[n - 1];
        int left = 0, right = n - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(sum[mid] >= k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } 
        //如果相等要加1个
        return sum[left] == k ? left + 1 : left;
    }
};
```

右侧二分搜索 (用的左闭右开区间)

```C++
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int n = chalk.size();
        vector<long long> sum(n);
        sum[0] = chalk[0];
        for(int i = 1; i < n; i++){
            sum[i] = sum[i - 1] + chalk[i];
        }
        k = k % sum[n - 1];
        int left = 0, right = n;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(sum[mid] > k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        } 
        return sum[right] == k? right + 1 : right;
    }
};

```
