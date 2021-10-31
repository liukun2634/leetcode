//singly-linked list
struct ListNode {
    //1. 值
    int val;
    //2. next指针
    ListNode* next;
    //3. 构造函数, 使用构造列表, 根据参数有三种
    ListNode(): val(0), next(nullptr) {}

    ListNode(int x): val(x), next(nullptr) {}

    ListNode(int x, ListNode* next): val(x), next(next) {}
};


//Tree Node

