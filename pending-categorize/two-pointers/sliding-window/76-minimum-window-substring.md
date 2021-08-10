### 76. 最小覆盖子串

#### 题目

https://leetcode-cn.com/problems/minimum-window-substring/

#### 思路：滑动窗口

该题是最为标准的滑动窗口题，参照滑动窗口模板。

注意点：

- [left，right) 是左闭右开区间，在字符串计算时注意长度是right - left
- 删除节点的顺序要跟加入节点的顺序刚好相反，这样判断就没有问题
- 滑动窗口可以在中间增加debug left 和 right

- valid 判断是当window 的个数满足了need 要求，注意增加的条件是
    1. 字符c是need 存在map中 need.count(c) （其实可以把window[c]++ 放入该判断，减少map操作。）
    2. 字符c刚好满足要求 window[c] == need[c]


C++ map 的使用：
- 它的一个方法 count(key) 相当于 Java 的 containsKey(key) 可以判断键 key 是否存在。

- 可以使用方括号访问键对应的值 map[key]。需要注意的是，如果该 key 不存在，C++ 会自动创建这个 key，并把 map[key] 赋值为 0。map[key]++ 相当于 Java 的 map.put(key, map.getOrDefault(key, 0) + 1)


```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        int valid = 0;
        for(char c : t) {
            need[c]++;
        }
        
        int left = 0, right = 0;
        string res = "";
        while (right < s.size()){
            //c 是要移入窗口的字符
            char c = s[right];
            //右侧移动窗口
            right++;
            //进行窗口内数据的一次更新
            window[c]++;
            if(need.count(c) && window[c] == need[c]) {
                valid++;
            }
            
            // Debug
            // printf("window: [%d, %d)\n", left, right);

            //判断左侧窗口是否要收缩， 即所有字符包括个数都满足需要
            while(valid == need.size()) {
                //更新最小覆盖子串，注意right是右开
                if(res == "" || res.size() > right - left) { 
                    res = s.substr(left, right - left);
                }
                //d是要删除的字符
                char d = s[left];
                //左侧移动窗口
                left++;
                //进行窗口内数据的一次更新
                if (need.count(d) && window[d] == need[d]) {
                    valid--;
                }
                window[d]--; //删除的顺序要与添加的相反
            }
        }
        return res;
    }
};

```