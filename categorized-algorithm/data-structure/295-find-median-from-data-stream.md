## 295. 数据流的中位数

### 题目

https://leetcode-cn.com/problems/find-median-from-data-stream/

### 思路： 大顶堆 + 小顶堆

大顶堆存小的K个数，这样最大的在堆顶。
小顶堆存大的K个数，这样最小的在堆顶。
这样中位数一定是这两个堆顶相关（保证大顶堆大于等于小顶堆，那么中位数要么是大顶堆的堆顶，要么是两者的和的一半）

那么如何保证两个堆数目相差至少为1，同时小的部分放在大顶堆，大的部分放在小顶堆呢？

通过一个技巧，比如大顶堆的数目少，在加入前先将要加入的数字放到小顶堆，然后将小顶堆的堆顶放到大顶堆，这样就保证了大顶堆一定都是小的，小顶堆一定都是大的。

```C++
class MedianFinder {
private:
    //大顶堆：存小的K个数
    priority_queue<int, vector<int>, less<int>> small;
    //小顶堆: 存大的K个数
    priority_queue<int, vector<int>, greater<int>> large;

public:
    /** initialize your data structure here. */
    MedianFinder() {

    }
    
    void addNum(int num) {
        //技巧：先插入另一个小的堆中，再把另一个的堆顶拿过来
        //从而保证大顶堆堆顶一定小于小顶堆堆顶
        if(small.size() <= large.size()) {
          large.push(num);
          small.push(large.top());
          large.pop();
         
        } else {
          small.push(num);
          large.push(small.top());
          small.pop();
        }
    }
    
    double findMedian() {
        //add里保证了small至少比large多1
        if(small.size() > large.size()) {
            return small.top();
        }
        //相等说明是偶数个
        return (small.top() + large.top()) / 2.0;
    }
};
```

**复杂度分析**

时间复杂度：O(logn)
空间复杂度：O(n)