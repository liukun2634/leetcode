## 19. 删除链表的倒数第 N 个结点

### 题目

https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/

### 思路： 快慢指针 + dummy 指针

倒数 考虑 快慢指针
删除节点 考虑 dummy 指针

```C++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        for(int i = 1; i <= n; i++){
            fast = fast -> next;
        }

        
        ListNode* dummy = new ListNode();
        dummy -> next = head;
        ListNode* pre = dummy;
        ListNode* cur = head;
        while(fast != nullptr){
            cur = cur -> next;
            pre = pre -> next;
            fast = fast -> next;
        }

        //删除操作
        ListNode* next = cur -> next;
        delete cur;
        pre -> next = next;
        return dummy -> next;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：