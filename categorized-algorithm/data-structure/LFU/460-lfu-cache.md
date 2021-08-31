## 460. LFU 缓存

### 题目

https://leetcode-cn.com/problems/lfu-cache/

### 思路： 

需要额外构造一个freqToKeys 的表，利用LinkedHashSet 达到 O(1)的删除（从两端删除， 从中间删除）

```Java
class LFUCache {
    //key 到 val 的映射 K-V
    Map<Integer, Integer> keyToVal;
    //key 到 freq 的映射 K-F
    Map<Integer, Integer> keyToFreq;
    //freq 到 一些keys 的映射 F-K
    Map<Integer, LinkedHashSet<Integer>> freqToKeys;
    
    
    //记录最小freq
    int minFreq;
    //记录容量 
    int capacity;

    public LFUCache(int capacity) {
        keyToVal = new HashMap();
        keyToFreq = new HashMap();
        freqToKeys = new HashMap();
        this.capacity = capacity;
        this.minFreq = 0;
    }
    
    public int get(int key) {
        //1. 不存在
        if(!keyToVal.containsKey(key)) return -1;
        //2. 存在，先增加freq，再返回
        increaseFreq(key);
        return keyToVal.get(key); 
    }
    
    public void put(int key, int value) {
        //特殊处理
        if(this.capacity <= 0) {
            return;
        }

        //1. 存在，只更新
        if(keyToVal.containsKey(key)) {
            increaseFreq(key);
            keyToVal.put(key, value);
            return;
        }

        //2.不存在,
        //2.1 如果超过cap 则需要删除least used
        if(this.capacity <= keyToVal.size()) {
            removeMinFreq(key);
        }

        //2.2 放入key value，更新相应值
        keyToVal.put(key, value);
        keyToFreq.put(key, 1);
        freqToKeys.putIfAbsent(1, new LinkedHashSet<>());
        freqToKeys.get(1).add(key);
        this.minFreq = 1;
    }


    void increaseFreq(int key){
        int oldFreq = keyToFreq.get(key);
        int newFreq = oldFreq + 1;

        //删除之前的freq
        LinkedHashSet<Integer> keySet = freqToKeys.get(oldFreq);
        keySet.remove(key);
        if(keySet.isEmpty()){
            freqToKeys.remove(oldFreq);
            //可能需要更新minFreq
            if(oldFreq == this.minFreq) {
                this.minFreq++;
            }
        }

        // 更新 F-K
        freqToKeys.putIfAbsent(newFreq, new LinkedHashSet());
        freqToKeys.get(newFreq).add(key);
        // 更新 K-F
        keyToFreq.put(key, newFreq);
    }

    void removeMinFreq(int key){
        LinkedHashSet<Integer> keySet = freqToKeys.get(this.minFreq);
        int deletedKey = keySet.iterator().next();
        // 更新 F-K
        keySet.remove(deletedKey);
        if(keySet.isEmpty()){
            freqToKeys.remove(this.minFreq);
            //this.minFreq 不需要额外更新，因为会在后面置为1
        }
        // 更新 K-V
        keyToVal.remove(deletedKey);
        // 更新 K-F
        keyToFreq.remove(deletedKey);
    }
}
```

**复杂度分析**

时间复杂度：
空间复杂度：