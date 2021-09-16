## 206. 反转链表

### 题目

https://leetcode-cn.com/problems/reverse-linked-list/

### 思路1： 递归 

构造一个反转函数返回的是反转后的头指针 （last），递归的后序遍历。

```C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //1.  返回条件
        if(head == nullptr || head->next == nullptr) return head;
        //2. 递归，保存last指针
        ListNode* last = reverseList(head->next);
        //3. 后序遍历处理当前节点
        head->next->next = head;
        head->next = nullptr;
        return last;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n) 栈空间


### 思路2： 迭代 + 三指针遍历

三个指针（pre，cur，next）不断递进，

1. pre 是递进的最开始节点，最后也用于返回
2. cur 是需要指向 pre 的节点
3. next 是用于中间保存，更新后面pre 和cur

```C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while(cur != nullptr) {
            //1. 临时保存 next 节点
            ListNode* next = cur -> next;
            //2. cur 下一个节点反转到pre 节点 （这里是反转关键点）
            cur -> next = pre;
            //3. cur 作为 pre 节点
            pre = cur;
            //4. next 节点作为cur
            cur = next;
        }
        //5. 返回的是pre 节点
        return pre;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)


### 思路3： 迭代 + 头插法

头插法需要dummy 指针来帮助

1. 这里的pre 和前面 pre 不同，这里pre 是不动的，代表反转节点前一个节点（如果不是中间反转，就是dummy节点）。

2. 这里的cur 一直是反转的最开始节点，所以插入最后变为尾节点。

3. cur->next 就是要往前插到 pre->next 位置的节点。 （头插入法）

```C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;

        //头插法（pre，cur 和 next）
        ListNode* pre =  dummy;
        ListNode* cur = pre -> next;
        ListNode* next;
        while(cur != nullptr && cur-> next != nullptr) {
            //cur 的下一个往前插 （ 移动 k - 1 个）
            next = cur -> next;
            //cur next 指向下一个要插到前面的节点
            cur -> next = next -> next;
            // 将next 节点插入 pre 和 pre-> next 中间
            next -> next = pre -> next;
            pre -> next = next;
        }
        return dummy -> next; 
    }
};

```


### 思路4： 利用栈反转