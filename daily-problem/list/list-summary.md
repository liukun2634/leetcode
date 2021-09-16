# 链表总结

https://mp.weixin.qq.com/s/dVqXEMKZ6_tuB7J-leLmtg



## 链表节点

```C++
struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

## 技巧总结

- 快慢指针
- dummy指针（虚拟头结点） -> 处理head 可能有挪动的情况
- 双指针 
- 利用额外空间保存链表节点 （栈实现反转，数组，哈希表快速得到位置）
- 递归 
- 迭代 （三指针递进，头插法）

### 快慢指针

- 倒数第k个节点（快指针走k步）
- 删除倒数第k个节点 （同时也需要dummy指针）
- 单链表的中点（快指针走两步，慢指针走一步）
- 判断链表是否包含环（快指针走两步，慢指针走一步，直到相遇）

### 双指针

- 两个链表是否相交 （走完一条走另一条）

### dummy指针

作用： 防止head出现空指针的情况，可以无需额外判断 


定义 dummy 指针。

```C++
ListNode* dummy = new ListNode(-1);
dummy -> next = head;

return dummy -> next;
```

有删除/合并的地方就考虑用dummy 指针

- 合并两个链表
- 合并K个链表（优先队列）
- 删除倒数第k个节点
  
### 反转链表

思路：
- 递归
- 迭代 
  - 三指针递进反转
  - 头插法（三指针，不过位置不同） 
- 栈反转

1. 反转整个链表 （递归，迭代）
2. 反转前N个 （记录后驱节点，反转后连接后驱节点）
3. 反转一部分 （利用2，递归， 迭代头插法）
4. 反转k组 （迭代头插法）


