## 141. 环形链表

### 题目

https://leetcode-cn.com/problems/linked-list-cycle/

### 思路1：快慢指针 

fast 和 slow 指针

```C++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == nullptr) return false;
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast != nullptr && fast -> next != nullptr){
            fast = fast -> next -> next;
            slow = slow -> next;
            if(fast == slow) return true;
        } 
        
        return false;
    }
};
```

**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(1)


### 思路2：哈希表

该思路，比较方便直接返回，确定就是 O(N) 的复杂度

```C++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* p = head;
        unordered_set<ListNode*> set;
        while(p != nullptr){
            if(set.count(p)) return true;
            set.insert(p);
            p = p -> next;
        }     
        return false;
    }
};
```


**复杂度分析**

时间复杂度：O(N)
空间复杂度：O(N)