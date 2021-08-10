### 快慢指针

#### 数组的应用模板

应用场景：
- 有序数组去重 （如果无序可以排序变为有序）
- 无序数组去某一个元素 

```cpp
int fastslowpointer(vector<int>& nums){
    //空数组判断
    if (nums.size() == 0)
        return 0;

    int slow = 0, fast = 0;
    //1. fast 要在 nums 范围内
    while (fast < nums.size()) {
        //2. 当fast满足条件，需要更新slow指针
        if (nums[fast] is valid) {
            //3. 更新 nums 和 slow 指针
            ...
        }
        //4. fast 增加 
        fast++;
    }
    //5. 返回取决于维护数组范围是[0, slow -1] 还是[0, slow]
    return slow / slow + 1;
}
```

注意几点：

1. 其中while 循环也可以修改成：

```cpp
  for(int fast = 0; fast < nums.size(); fast++) {
      ...
  }
```

但使用while循环结构更为清晰。

2. 在返回时，要注意的是维护的数组范围。



