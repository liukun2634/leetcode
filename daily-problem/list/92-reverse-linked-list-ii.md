## 92. 反转链表 II

### 题目

https://leetcode-cn.com/problems/reverse-linked-list-ii/

### 思路1： 迭代 + 头插法

因为前后都有节点，使用反转链表，需要记录前后节点。

这里还可以采用头插法：

pre 是头结点 （pre -> next 插入）
cur 是记录下一个需要反转的节点，插到最前面
next 是反转的节点，接到 pre的后面，并将下一个next 节点放到 cur->next后

额外还有dummy 指针，以防head没了。

```C++
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        //dummy 指针
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        
        ListNode* pre = dummy;
        //先移动left
        for(int i = 0; i < left - 1; i++){
            pre = pre -> next;
        }

        ListNode* cur = pre -> next;
        ListNode* next;
        //再反转right - left 次
        for(int i = left; i < right; i++){
            //头插法
            next = cur -> next;
            cur -> next = next -> next;
            next -> next = pre -> next;
            pre -> next = next;
        }

        return dummy->next;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：

### 思路2： 迭代 + 反转链表


### 思路3： 递归

```C++


```

