### 题目


### 870. 优势洗牌

#### 题目
https://leetcode-cn.com/problems/advantage-shuffle/

#### 思路： 排序 + 双指针

田忌赛马：都排好序，打的过就直接上，打不过就找最小的去送

技巧： 排序 +　双指针

```cpp
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> match;
        int n = nums1.size();
        vector<pair<int, int>> sorted1(n);
        vector<pair<int, int>> sorted2(n);
        for(int i = 0; i < n; i++){
            sorted1[i] = {nums1[i], i};
            sorted2[i] = {nums2[i], i};
        }
        sort(sorted1.begin(), sorted1.end(), [](const auto& a, const auto& b){return a.first > b.first;});
        sort(sorted2.begin(), sorted2.end(), [](const auto& a, const auto& b){return a.first > b.first;});
        
        int left = 0, right = n - 1;
        int i = 0;
        while(left <= right) {
            //没有优势就拿弱马来送
            if(sorted1[left].first <= sorted2[i].first) {
                match[sorted2[i].second] = sorted1[right].second;
                right--;
            } else {
                match[sorted2[i].second] = sorted1[left].second;
                left++;
            } 
            i++;
        }

        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            res[i] = nums1[match[i]];
        }
        return res;
    }
};
```

**优化代码**

- 不需要num1 也保存下标，只需要nums2要对应下标
- 不需要用map存储match，实际上只用数组就可以实现map 功能，下标为B的下标，值为A对应的值
- 遍历是以sorted nums2，然后通过双指针调整nums1的位置

```cpp
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        //从大到小排序
        sort(nums1.begin(), nums1.end(), greater<int>());
        //需要记录B的下标
        vector<pair<int, int>> sorted2(n);
        for(int i = 0; i < n; i++){
            sorted2[i] = {nums2[i], i};
        }
        sort(sorted2.begin(), sorted2.end(), [](const auto& a, const auto& b){return a.first > b.first;});
        
        //记录对应B下标的A的值
        vector<int> res(n);
        //双指针记录num1 要比较的位置
        int left = 0, right = n - 1;
        for(int i = 0; i < n; i++){
            auto [cur, idx] = sorted2[i];
            //如果没有优势，就选最弱的来较量
            if(nums1[left] <= cur) {
                res[idx] = nums1[right];
                right--;
            } else {
                res[idx] = nums1[left];
                left++;
            } 
        }
        return res;
    }
};

```