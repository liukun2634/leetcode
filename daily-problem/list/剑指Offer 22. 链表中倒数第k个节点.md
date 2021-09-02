## 剑指 Offer 22. 链表中倒数第k个节点

### 题目

https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/

### 思路1： 快慢指针

```C++
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *slow = head, *fast = head;
        for(int i = 0; i < k - 1; i++){
            fast = fast -> next;
        }
        while(fast->next != nullptr){
            fast = fast -> next;
            slow = slow -> next;
        }
        return slow;
    }
};
```

fast 走到 nullptr， 会增加点时间，但是code 相对好看些。

```C++
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *slow = head, *fast = head;
        for(int i = 0; i < k ; i++){
            fast = fast -> next;
        }
        while(fast != nullptr){
            fast = fast -> next;
            slow = slow -> next;
        }
        return slow;

    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)


### 思路2： 差值法

遍历一遍，拿到完整的长度，然后len - k 就是倒数第k 个节点


### 思路3： 栈

所有翻转，倒数，都可以考虑使用栈来保存，最后抛出。
