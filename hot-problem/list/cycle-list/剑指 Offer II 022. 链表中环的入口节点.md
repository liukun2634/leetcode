## 剑指 Offer II 022. 链表中环的入口节点

### 题目

https://leetcode-cn.com/problems/c32eOV/

### 思路1： 快慢指针

关键是根据公式计算 x 是到环入口的距离， y 是入口到第一次相遇的距离，l 是环的长度
根据第一次相遇点有 2 * slow 的距离  = fast 的距离
2 * (x + y) = x + nl + y

可得 x = (l - y) + (n - 1)l

所以将slow 移到起点，fast 保持在相遇点出发，然后分别一步一步走，最终会在环的入口相遇

```C++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast != nullptr && fast -> next != nullptr){
            fast = fast -> next -> next;
            slow = slow -> next;
            
            //存在环
            if(fast == slow) {
                //将slow 移到起点，fast 保持在相遇点出发，然后分别一步一步走，直到相遇
                //x  = l - y + (n - 1) * l
                slow = head;
                while(slow != fast){
                    slow = slow -> next;
                    fast = fast -> next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：