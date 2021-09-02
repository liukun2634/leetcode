### 138. 复制带随机指针的链表

#### 题目: 

https://leetcode-cn.com/problems/copy-list-with-random-pointer/

#### 思路1:  
使用 hashmap 存储老节点X和新节点x对应关系
第一遍遍历老链表，构造hashmap(X, x), (Y, y)，同时构造新链表
第二遍同时遍历老链表和新链表，根据老节点`X->random`指针所指向的节点Y，在hashmap中找到对应的新节点y，并更新此时的新节点的`x->random`指针

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* p1 = head;
        Node* p2 = nullptr, *head2 = nullptr;
        unordered_map<Node*, Node*> map;
        while(p1 != nullptr) {
            if (p2 == nullptr) {
               p2 = new Node(p1->val);
               head2 = p2;
            } else {
               p2 -> next = new Node(p1->val);
               p2 = p2 ->next;
            }
            map.emplace(p1, p2);
            p1 = p1 -> next;
        }

        p1 = head;
        p2 = head2;
        while(p1 != nullptr) {
            if(p1 -> random != nullptr) {
                p2->random = map.find(p1->random)->second;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return head2;
    }
};
```

#### 提升
 新链表完全通过map来获取, 第一遍遍历只构造hasmap，在第二次遍历时连接next和random
- [unorder_map的使用](https://en.cppreference.com/w/cpp/container/unordered_map) 

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* p = head;
        unordered_map<Node*, Node*> map;
        while(p != nullptr) {
            map.emplace(p, new Node(p->val));
            p = p -> next;
        }
        //将null也插入map, 从而处理p->next和p->random情况
        map.emplace(nullptr, nullptr);

        p = head;
        while(p != nullptr) {
            map.at(p)->next = map.at(p->next);
            map.at(p)->random = map.at(p->random);
            p = p -> next;
        }
        return map.at(head);
    }
};
```

#### 思路2 
技巧 
1. 先将所有新链表的节点插入老链表的后面：X1->Y1->X2->Y2->X3 ···
2. 然后通过老链表random指针，将新链表的节点random链接好 （因为新链表就是老链表的next指针）
3. 再将新链表与老链表断开