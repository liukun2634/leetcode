### 二分搜索


参考：
https://labuladong.gitbook.io/algo/mu-lu-ye-1/mu-lu-ye-3/er-fen-cha-zhao-xiang-jie


#### 难点
1. while 判断中什么时候用 <=, 什么时候用 <

取决于搜索区间是[0, length - 1] 还是 [0, length] 即 [0, lenght), 即right是否代表有效的值。

当然，如果对于 [0, length - 1] 非要用< 也没有关系，最后的时候进行一个补丁判断是否找到target 就可以。


2. 什么时候用left = mid, right = mid， 什么时候 用left = mid + 1， right = mid - 1。

取决于搜索区间是左闭右闭，还是左闭右开。如果mid 已经搜索过，应该从搜索区间中去除。
如果是右闭的话，就需要 mid + 1 和 mid -1 ;
如果是右开的话，left = mid + 1, right = mid。
这样保证搜索区间的统一性。

3. 最后要判断是否出界


**理解：**

- 搜索区间 决定 while 判断， 决定mid 更新。
- 左侧右侧值决定mid == target 的判断后的逻辑
- 是否存在找不到target情况，决定是否增加补丁判断
- 记住，最终left和right值是一样的

#### 双闭区间

```cpp
int left_bound(vector<int> nums, int target)
{
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            //nums[mid] <= target
            //锁定左边边界，因为返回是left，最终left是+1比right大
            right = mid - 1;
        }
    }
    //处理越界情况 和 没找到的情况
    if (left >= nums.size() || nums[left] != target)
        return -1;
    return left;
}

int right_bound(vector<int> nums, int target)
{
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }

        //处理越界 和 找不到情况
        if (right < 0 || nums[right] != target)
            return -1;
        return right;
    }
}

```

#### 二分搜索的泛化


你要从题目中抽象出一个自变量 x，一个关于 x 的函数 f(x)，以及一个目标值 target。
同时，x, f(x), target 还要满足以下条件：
1、f(x) 必须是在 x 上的单调函数（单调增单调减都可以）。
2、题目是让你计算满足约束条件 f(x) == target 时的 x 的值。

```cpp
// 函数 f 是关于自变量 x 的单调函数
int f(int x) {
    // ...
}

// 主函数，在 f(x) == target 的约束下求 x 的最值
int solution(int[] nums, int target) {
    if (nums.length == 0) return -1;
    // 问自己：自变量 x 的最小值是多少？
    int left = ...;
    // 问自己：自变量 x 的最大值是多少？
    int right = ...;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (f(mid) == target) {
            // 问自己：题目是求左边界还是右边界？
            // ...
        } else if (f(mid) < target) {
            // 问自己：怎么让 f(x) 大一点？
            // ...
        } else if (f(mid) > target) {
            // 问自己：怎么让 f(x) 小一点？
            // ...
        }
    }
    return left;
}
```

1、确定 x, f(x), target 分别是什么，并写出函数 f 的代码。
2、找到 x 的取值范围作为二分搜索的搜索区间，初始化 left 和 right 变量。
3、画出f(x)图型，具体分析target 判断方向
4、根据题目的要求，确定应该使用搜索左侧还是搜索右侧的二分搜索算法，写出解法代码。


#### 二分搜索优化效率
