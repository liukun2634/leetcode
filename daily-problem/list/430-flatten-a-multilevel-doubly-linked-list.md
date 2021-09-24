## 430. 扁平化多级双向链表

### 题目

https://leetcode-cn.com/problems/flatten-a-multilevel-doubly-linked-list/

### 思路1： 递归

增加一个辅助函数，返回flatten的last 节点，从而处理cur ， last 和 next 节点。

```C++
class Solution {
public:
    Node* flatten(Node* head) {
        flattenAndReturnLast(head);
        return head;
    }

    //递归返回flatten 后 last 节点
    Node* flattenAndReturnLast(Node* head){
        Node* cur = head;
        Node* last = nullptr; //有child 和 没child 需要分别处理last 值
        while(cur != nullptr){
            Node* next = cur -> next;
            if(cur -> child != nullptr){
                Node* child = cur->child;
                last = flattenAndReturnLast(child);
                child -> prev = cur;
                cur -> next = child;
                if(next != nullptr){
                    last -> next = next;
                    next -> prev = last;
                }
                cur -> child = nullptr;
            } else{
                last = cur;
            }
            cur = next;
        }
        return last;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)

### 思路2： 迭代