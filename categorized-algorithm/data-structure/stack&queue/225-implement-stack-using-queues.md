## 225. 用队列实现栈

### 题目

https://leetcode-cn.com/problems/implement-stack-using-queues/

### 思路：一个队列实现栈 

当需要pop/top 时候，把前面的数都放到队尾，这样使得最前面的数是最后插入的那个数就可以了。

注意：top在看完栈顶的数后，还需要放到队尾，从而保证插入的顺序是正确的。

```C++
class MyStack {
    Deque<Integer> queue = new ArrayDeque();
    public MyStack() {
    }
    
    public void push(int x) {
        queue.addLast(x);
    }
    
    public int pop() {
        int size = queue.size();
        while(size > 1){
            size--;
            queue.addLast(queue.pollFirst());
        }
        return queue.pollFirst();
    }
    
    public int top() {
        int size = queue.size();
        while(size > 1){
            size--;
            queue.addLast(queue.pollFirst());
        }
        //注意：看完top 后，需要把数据再放到结尾
        int top = queue.peekFirst();
        queue.addLast(queue.pollFirst());
        return top;
    }
    
    public boolean empty() {
        return queue.isEmpty();
    }
}

```

**复杂度分析**

时间复杂度：pop() 和 top() 是O(n)
空间复杂度：O(n)