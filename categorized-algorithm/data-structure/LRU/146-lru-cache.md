## 146. LRU 缓存机制

### 题目

https://leetcode-cn.com/problems/lru-cache/

### 思路： HashMap + 双向链表

需要一个hashmap，从而保证O(1)的get 和 put

需要一个双向链表这样可以保证能够O(1)的remove first 和 同时remove 最近使用的x到链表头部

Java LinkedHashMap

```Java 
class LRUCache {
    LinkedHashMap<Integer, Integer> cache = new LinkedHashMap();
    int cap;

    public LRUCache(int capacity) {
        this.cap = capacity;
    }
    
    public int get(int key) {
        //1.如果不存在
        if(!cache.containsKey(key)){
            return -1;
        }
         //2. 如果存在，就变为最近使用，再返回
        makeRecentlyUsed(key);
        return cache.get(key);
    }
    
    public void put(int key, int value) {
        //1. 如果不存在
        if(!cache.containsKey(key)){
            //1.1 达到cap需要删除最少使用的元素
            if(cache.size() >= cap) {
                int oldestKey = cache.keySet().iterator().next();
                cache.remove(oldestKey);
            } 
            //1.2 再放到末尾
            cache.put(key, value);
            return;
        } 

        //2. 如果存在，先更新为最新的值，再变为最近使用
        cache.put(key, value); 
        makeRecentlyUsed(key);
    }

    private void makeRecentlyUsed(int key){
        int value = cache.get(key);
        cache.remove(key);
        cache.put(key, value);
    }
}

```

**复杂度分析**

时间复杂度：O(1)
空间复杂度：O(capacity)