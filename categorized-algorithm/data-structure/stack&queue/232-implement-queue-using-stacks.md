## 232. 用栈实现队列

### 题目

https://leetcode-cn.com/problems/implement-queue-using-stacks/

### 思路： 用两个栈实现队列

定义两个栈，in 和 out。（in的顶是最后进入， out的顶是最先进入）

在插入时，将out先全部倒回到in栈，再插入数据。

在抛出和求队头时，将in先全部倒到out栈中，再返回out的堆顶。

```Java
class MyQueue {
    Deque<Integer> in = new ArrayDeque();
    Deque<Integer> out = new ArrayDeque();

    public MyQueue() {

    }
    public void push(int x) {
        while (!out.isEmpty()) {
            in.addLast(out.pollLast());
        }
        in.addLast(x);
    }
    
    public int pop() {
        while(!in.isEmpty()) {
            out.addLast(in.pollLast());
        }
        return out.pollLast();
    }
    
    public int peek() {
        while(!in.isEmpty()) {
            out.addLast(in.pollLast());
        }
        return out.peekLast();
    }
    
    public boolean empty() {
        return in.isEmpty() && out.isEmpty();
    }
}
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)

### 复杂度优化

不需要每次都倒腾来倒腾去，只需要保证： **输入的元素总是跟在前面的输入元素的后面，而输出元素总是最早输入的那个元素即可。**

所以，倒腾只发生在pop/peek 且 out栈为空的情况下：

```Java
class MyQueue {
    Deque<Integer> in = new ArrayDeque();
    Deque<Integer> out = new ArrayDeque();
    public MyQueue() {

    }
    
    public void push(int x) {
        in.addLast(x);
    }
    
    public int pop() {
        checkAndmoveInToOut();
        return out.pollLast();
    }
    
    public int peek() {
        checkAndmoveInToOut();
        return out.peekLast();
    }

    private void checkAndmoveInToOut(){
        //先判断out 是不是空，再把值放入
        if(out.isEmpty()){
            while(!in.isEmpty()){
                out.addLast(in.pollLast());
            }
        }
    }
    
    public boolean empty() {
        return in.isEmpty() && out.isEmpty();
    }
}
```

**复杂度分析**

时间复杂度：pop() 和 peek() 操作都是均摊 O(1)
空间复杂度：O(n)


