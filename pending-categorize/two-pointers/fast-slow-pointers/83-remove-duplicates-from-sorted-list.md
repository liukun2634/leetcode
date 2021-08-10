### 83. 删除排序链表中的重复元素

#### 题目

https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/

#### 思路： 快慢指针

首先题目提到了该链表是一个有序链表，可以考虑使用快慢指针。

类似题目26，不过链表的操作数组稍有不同，注意在于链表的处理主要是next指针，判断循环是通过指针是否为空。两者快慢指针的框架是相同的。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        //空指针判断
        if(head == nullptr) return head;

        ListNode *slow = head, *fast = head;
        //循环条件是fast处于有效指针范围内
        while(fast != nullptr) {
            //更新slow指针条件
            while(fast->val != slow->val) {
                slow -> next = fast;
                slow = slow -> next;
            }
            //更新fast指针
            fast = fast->next;
        }
        //最后要处理掉slow后面的数
        slow -> next = nullptr;
        return head;
    }
};
```


