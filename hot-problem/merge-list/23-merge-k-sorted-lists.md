## 23. 合并K个升序链表

### 题目

https://leetcode-cn.com/problems/merge-k-sorted-lists/

### 思路1： 优先队列

```C++
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode();
        ListNode* iterator = dummy;
        priority_queue<pair<int, ListNode*>, vector<pair<int,ListNode*>>, greater<pair<int,ListNode*>>> queue;
        int n = lists.size();
        for(int i = 0; i < n; i++){
            if(lists[i] != nullptr){
                queue.push({lists[i]->val, lists[i]});
            }
        } 

        while(!queue.empty()){
            ListNode* cur = queue.top().second;
            queue.pop();
        
            ListNode* next = cur->next;
            cur->next = nullptr; 
            iterator->next = cur;
            //移动iterator
            iterator = iterator -> next; 
            //push next
            if(next != nullptr) {
                queue.push({next->val, next});
            }
        }
        return dummy -> next;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：