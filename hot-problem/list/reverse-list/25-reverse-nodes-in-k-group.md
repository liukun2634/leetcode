## 25. K 个一组翻转链表

### 题目

https://leetcode-cn.com/problems/reverse-nodes-in-k-group/

### 思路1：迭代 +　头插法

快慢指针，计算ｋ个节点。

然后对ｋ　个节点范围内进行头插法。

注意　slow 和 fast 指针的更新。

同时需要dummy 指针。

```C++
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        //1. dummy node
        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;
        //2. 快慢指针
        ListNode* slow = dummy;
        ListNode* fast = dummy -> next;

        int count = 1;
        while(fast != nullptr){   
            fast = fast -> next;
            count++;
            if(count == k) {
                ListNode* pre = slow;
                ListNode* cur = pre -> next;
                ListNode* next;
                //3. 迭代 + 头插法反转k个节点 （移动k - 1 次）
                for(int i = 1; i < k; i++){
                    next = cur -> next;
                    cur -> next = next -> next;
                    next -> next = pre -> next;
                    pre -> next = next;
                }
                count = 0;
                slow = cur;
                //注意fast 也需要更新
                fast = cur -> next;
            }
        }   
        return dummy->next;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：