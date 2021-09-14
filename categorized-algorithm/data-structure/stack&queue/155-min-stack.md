## 155. 最小栈

### 题目

https://leetcode-cn.com/problems/min-stack/

### 思路1：辅助栈记录最小值

增加一个help stack 记录当前位置的最小值。

```Java
class MinStack {
    Deque<Integer> data;
    Deque<Integer> helper;

    /** initialize your data structure here. */
    public MinStack() {
        data = new ArrayDeque();
        helper = new ArrayDeque();
    }
    
    public void push(int val) {
        data.addLast(val);
        if(helper.isEmpty() || helper.peekLast() > val) {
            helper.addLast(val);
        } else {
            helper.addLast(helper.peekLast());
        }
    }
    
    public void pop() {
        data.pollLast();
        helper.pollLast();
    }
    
    public int top() {
        return data.peekLast();
    }
    
    public int getMin() {
        return helper.peekLast();
    }
}
```

**复杂度分析**

时间复杂度：O(1)
空间复杂度：O(n)

### 思路2：原栈压入的是与最小值的差值

例如：  3  2  4  5  1
栈为：  0 -1  2  3 -1
最小值：3  2  2  2  1

负值用于min被pop 出，后需要更新的差值
正值是当前值与min的差值，用于计算当前值

- push 时候 如果比min 小，就更新min。
- pop 时候，如果是负值，说明当前pop的值是最小值，要更新min 为 min - top
- top 时候，如果是负值，可以直接返回min，否则返回的是min + top

注意：因为差值可能会超出int，所以要用long保存

```Java
class MinStack {
    Deque<Long> stack;
    long min;

    public MinStack() {
       stack = new ArrayDeque();
    }
    
    public void push(int val) {
        if(stack.isEmpty()){
            min = val;
        } 
        stack.addLast(val - min);
        min = Math.min(val, min);
    }
    
    public void pop() {
        long top = stack.pollLast();
        if(top < 0) {
            min -= top;
        }
    }
    
    public int top() {
        long top = stack.peekLast();
        return top < 0 ? (int)min : (int)(min + top);
    }
    
    public int getMin() {
        return (int)min;
    }
}
```
