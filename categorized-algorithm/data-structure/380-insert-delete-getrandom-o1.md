### 380. O(1) 时间插入、删除和获取随机元素

#### 题目

https://leetcode-cn.com/problems/insert-delete-getrandom-o1/

#### 思路： 动态数组 + 哈希表

关键点：

- 动态数组 + 哈希表 实现
- 数组插入，只用在末尾插入就能够达到O(1)的复杂度（不考虑扩容的那一次）。
- 数组删除可以**通过哈希表记录value->index 映射，实现在O(1) 的时间内找到要删除元素，然后将数据移动到末尾进行O(1)的删除**，之后再同时更新哈希表。

C++ vector 和 unordered_map 的灵活使用:
- vector 的 `push_back()`, `back()` 和 `pop_back()`
- unordered_map 的 `count` 和 `map[index]`

```cpp
class RandomizedSet {
private: 
    //存储元素
    vector<int> nums;
    //记录每个元素对于nums 中的索引
    unordered_map<int, int> valToIndex;
public:

    bool insert(int val) {
        //val 存在就直接返回
        if (valToIndex.count(val)){
            return false;
        }
        //插在 nums 的尾部，并记录val 对应的索引值
        nums.push_back(val);
        valToIndex[val] = nums.size();
        return true;
    }
    
    bool remove(int val) {
        //val 不存在就直接返回
        if (!valToIndex.count(val)){
            return false;
        }
        //获取删除节点的索引
        int index = valToIndex[val];
        //与末尾节点交换，其实可以直接覆盖，反正也要被删除
        swap(nums[index], nums.back());
        //更新末尾元素新的index
        valToIndex[nums[index]] = index;
        //删除末尾元素
        nums.pop_back();
        valToIndex.erase(val);
        return true;
    }
    
    int getRandom() {
        //随机获取一个元素
        int index = rand() % nums.size();
        return nums[index];
    }
};

```