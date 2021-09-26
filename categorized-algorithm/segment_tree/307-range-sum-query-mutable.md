## 307. 区域和检索 - 数组可修改

### 题目

https://leetcode-cn.com/problems/range-sum-query-mutable/

### 思路1：树状数组（Binary index tree)

关键点 
1. lowbit
2. 树状数组 从1开始到n，所以从原数组到线状数组需要转换 i + 1
3. query 函数，会返回 0 - idx 下标的区间和
4. add 函数用于构造 和 更新 （更新增量）

```C++
class NumArray {
private:
    int n; //原数组长度，树状数组长度为 n+1
    vector<int> arr; //树状数组
    vector<int> nums;//原数组

    /**** helper functions ***/
    int lowbit(int x){
        return x & -x;
    }

    //返回 0 - x 下标的区间和
    int query(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= lowbit(i)){
            res += arr[i];
        }
        return res;
    }

    //给idx 增加 value
    void add(int idx, int value){
        for(int i = idx; i <= n; i += lowbit(i)){
            arr[i] += value;
        } 
    }

public:
    NumArray(vector<int>& nums_) {
        n = nums_.size();
        arr.resize(n + 1); 
        nums.resize(n);
        for(int i = 0; i < n; i++){
            nums[i] = nums_[i];
            //注意树状数组下标要从1开始，两数组下标转换要注意
            add(i + 1, nums[i]);
        }
    }
    
    void update(int index, int val) {
        add(index + 1, val - nums[index]);
        nums[index] = val;
    }
    
    int sumRange(int left, int right) {
        return query(right + 1) - query(left);
    }
};
```

**复杂度分析**

时间复杂度：更新 和 查询均为 O(logn)， 构造是 O(nlogn)
空间复杂度：O(n)

### 思路2：线段树

要点：
先构造/更新 叶子， 再到根节点

节点 i  的兄弟节点下标是 i^1


```C++
class NumArray {
private:
    int n; //数组长度，下标从1开始
    vector<int> arr; //线段树

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        arr.resize(2 * n, 0);
        //1.叶子构建
        for(int i = 0; i < n; i++){
            arr[i + n] = nums[i];
        }
        //2. 根节点构建, 从下往上计算
        for(int i = n - 1; i > 0; i--){
            arr[i] = arr[i << 1] + arr[ (i << 1) | 1];
        }
    }
    
    void update(int index, int val) {
        //1.更新叶子节点
        arr[index + n] = val;
        //2.更新根节点, 从叶子节点向上
        for(int i = index + n; i > 1; i >>= 1) {
            arr[i >> 1] = arr[i] + arr[i ^ 1];
        }
    }
    

    int sumRange(int left, int right) {
        int res = 0;
        left = left + n;
        right = right + n;
        //注意这里是左闭右闭区间
        while(left <= right){
            //如果left 是右孩子，left加入res，并移除该节点，left++
            if(left & 1) res += arr[left++];
            //如果right 是左孩子，同样right加入res，并移除该节点，right--
            if(! (right & 1)) res += arr[right--];
            left >>= 1;
            right >>= 1;
        }
        return res;
    }
};

```