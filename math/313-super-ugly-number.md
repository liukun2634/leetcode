### 313. 超级丑数

#### 题目

https://leetcode-cn.com/problems/super-ugly-number/

#### 思路1：最小堆

用一个小顶堆存储数据，每次pop 堆顶，与所有primes相乘，结果再存到堆中。

要点：

- C++ 的 heap 默认是大顶堆，要改成小顶堆
- 增加一个unordered_set 记录是否访问过
- 注意越界的情况(堆也得用long类型存储)



```cpp
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<long, vector<long>, greater<long>> heap;
        unordered_set<long> saved;
        heap.push(1);
        saved.insert(1);
        int res = 0;
        while(n > 0) {
            res = heap.top();
            heap.pop();
            for(int i = 0; i < primes.size(); i++) {
                long num = (long) res * primes[i];
                if(saved.find(num) == saved.end()) {
                    heap.push(num);
                    saved.insert(num);
                }
            }
            n--;
        }
        return res;
    }
};
```

#### 思路2：多路归并

https://leetcode-cn.com/problems/super-ugly-number/solution/gong-shui-san-xie-yi-ti-shuang-jie-you-x-jyow/ 

我们需要每次取 m 个指针中值最小的一个，然后让指针后移（即将当前序列的下一个值放入堆中），不断重复这个过程，直到我们找到第 n 个丑数。

依然使用小顶堆存储，不过每次存储的信息增加为
- val ：为当前列表指针指向具体值；
- i ：代表这是由 primes[i] 构造出来的有序序列；
- idx：代表丑数下标，存在关系 val = ans[idx] * primes[i]。

把primes 数组的各个路primes[i]，都取一个最小的放到堆里比较，然后pop 出来是哪一个i，就是最小的n个，然后放入的是同一个i 的后面一个 ans[idx+1]∗primes[i], i , idx+1。

返回结果是ans[n - 1];
