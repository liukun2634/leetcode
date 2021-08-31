### 710. 黑名单中的随机数

#### 题目

https://leetcode-cn.com/problems/random-pick-with-blacklist/

#### 思路：黑名单映射

首先，紧凑的随机分布，就考虑用动态数组实现。这里因为取值范围为[0, n)且连续，所以可以直接用一个int记录white数组的size就可以代表数组。

那么怎么维护white数组呢？
考虑将[0, n) 分为两个部分，whitelist和blacklist，对于索引小于whitelist的范围，如果存在有black，就通过一个unordered_map把它映射对于大于whitelist中的一个节点。 这样在随机选择时，只计算小于whitelist size 的值，然后可以通过映射方式，将一个black 对应到一个white。

大于whitelist的black 也不用做任何考虑。



```cpp
class Solution {
private:
    int whitesize;
    //记录在white size 范围内的black 节点应该映射的下标
    unordered_map<int, int> mapping;
public:
    Solution(int n, vector<int>& blacklist) {
        whitesize = n - blacklist.size();
        //先做预处理标记, 把所有black先标记，为寻找white做准备
        for(int black : blacklist) {
            mapping[black] = 1; 
        }

        //注意区间大小为[0, n)
        int last = n - 1;
        //为存在于white size 内的black节点，映射到大于white size的white节点
        for(int black : blacklist) {
            //如果black在右边就不用管
            if(black >= whitesize) {
                continue;
            }
            //从最右边找第一个white节点去映射
            while(mapping.count(last)) {
                last--;
            }
            mapping[black] = last; 
            last--;
        }
    }
    
    int pick() {
        int index = rand() % whitesize;
        //如果索引到的是black节点，需要返回的是映射下标
        if(mapping.count(index)){
            return mapping[index];
        }
        //否则说明是一个white 节点，直接返回
        return index;
    }
};

```