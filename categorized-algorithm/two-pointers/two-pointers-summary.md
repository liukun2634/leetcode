### 双指针

参考：
https://labuladong.gitbook.io/algo/mu-lu-ye-1/mu-lu-ye-3/shuang-zhi-zhen-ji-qiao

#### 快慢指针

多用于链表中，循环的判断 `while (fast != null && fast.next != null)`

1、 判断是否有环 (可以用于指针，也可以用于表示图的数组)

2、 返回环的起始位置
   
   fast 和 slow 相遇后，将slow 移到 head位置，然后两个同时走一步，直到再次相遇就是环的起始位置。

   证明： 设 fast 与 slow 相遇时，slow 走了k步，那么fast 一定走了 2k步。多出的k步就是fast在环中转的步数。 再设相遇点为与环起始位置距离为m，可以得到环起始位置距离一定为 k - m 。 巧合的是，从相遇点出发，再走k - m 步同样也会再次到达相遇点。所以，可以通过把slow 放回起点，之后两个指针只走一步，再次相遇就是起始位置。

3、 返回链表中点

TODO: 876 题就是找链表中点

4、返回链表倒数第n个元素

TODO: 19 题「删除链表的倒数第 n 个元素」

5、有序数组/链表去重复数字

26 题 - 有序数组 （如果是无序数组，可以使用排序变为有序）
83 题 - 有序链表

6、 移除数组中的某个元素
27 题 
283 题 移除 0


#### 左右指针

多用于数组，最常用的滑动窗口。只要数组有序，就应该想到双指针技巧。

1、 二分查找

2、 两数之和

TODO: 第 167 题「两数之和 II」

3、 反转数组

TODO: 第 344 题是类似的需求

4、 滑动窗口算法
