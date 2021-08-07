### 457. 环形数组是否存在循环

#### 题目

https://leetcode-cn.com/problems/circular-array-loop/



#### 思路1: 模拟 O(N^2) 

遍历数组中的每个节点，不断找寻next节点，判断是否满足循环条件，如果是非循环节点则可以直接跳过循环。时间复杂度 O(n^2)，空间复杂度 O(1)。

```cpp
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++) {
                int pre = i;
                //限定找寻循环次数最多为n
                int m = n; 
                while(m > 0 && nums[pre] != 0) {  
                    int next = ((pre + nums[pre]) % n + n) % n;
                    //处理不是循环节点的情况
                    if(next == pre) break;
                    if((nums[pre] > 0 && nums[next] < 0) || (nums[pre] < 0 && nums[next] > 0)) break;
                    //发现节点下标相等，存在循环，直接返回true
                    if(next == i) return true;
                    pre = next;
                    m--;
                }
        }
        return false;
    }
};
```

#### 思路2： 模拟 + 标记路径 O(N)
https://leetcode-cn.com/problems/circular-array-loop/solution/gong-shui-san-xie-yi-ti-shuang-jie-mo-ni-ag05/ 

这里可以通过将非循环节点visit数组记录，这样后序判断时候，可以直接跳过该节点，时间复杂度可以从 O(n^2) 降到 O(n)，但空间复杂度为O(n)。

再考虑用原数组去做标记，这样可以将空间复杂度降为O（1）。这里对于模拟情况，增加一个很大的OFFSET去做标记， 通过OFFSET + i 标记从i点出发的所有节点。如果循环打破后，最后的节点的值为OFFSET + i， 那么就可以证明路径中存在环。

标记的思路来源于图遍历过程，可以将非安全节点清空 [802. 找到最终的安全状态](graph/802-find-eventual-safe-states.md)。可以转换问题为图上寻环。

技巧：
  - 标记走过的路径，visit 数组 或 用原数组 （OFFSET + i） 
  - 判断是否都大于0或者都小于0， 用两数的乘积判断是否大于或者小于0

```cpp
class Solution {
    const int OFFSET = 10010;
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++) {
                int cur = i, tag = OFFSET + i;
                //排除非循环节点
                while(nums[cur] < OFFSET) {  
                    int next =  ((cur + nums[cur]) % n + n) % n;
                    //退出条件1: 自我循环
                    if(next == cur) break;
                    //发现next已经访问过，存在循环，直接返回true
                    if(nums[next] == tag) return true;
                    //退出条件2：非全正或全负
                    if(nums[cur] * nums[next] < 0) break; 
                    nums[cur] = tag;
                    cur = next;
                }          
        }
        return false;
    }
};
```

#### 思路3： 快慢指针 + 标记非循环节点 O(N)

https://leetcode-cn.com/problems/circular-array-loop/solution/huan-xing-shu-zu-shi-fou-cun-zai-xun-hua-0ay2/ 

对于模拟+使用原数组标记的情况，不能用0去标记。因为，比方测试数据为[1, 1, 2]，对于下标0来说, 用模拟方法，0->1->2->1，所以0是属于非循环节点，但我们不能用0去标记模拟过程中的路径上的节点，因为1, 2是后面需要模拟的节点。

但对于快慢指针可以将遍历过的非循环节点标记为0，这是因为如果前面没有环，但后面有环，对于快慢指针仍然可以判断出来是满足循环的，所以在对下标0使用快慢指针，就能够判断出存在循环，而使用模拟就不行了。

区别就是快慢指针标记的是非循环节点，而模拟只能标记走过的路径，但走过的路径即可以判断是否有环，又可以再下次循环去除掉非循环节点。

技巧：
  - 双指针
  - 清除非循环节点，用0标记

```cpp
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        auto next = [&](int cur) {
            return ((cur + nums[cur]) % n + n) % n; // 保证返回值在 [0,n) 中
        };

        for (int i = 0; i < n; i++) {
            if (!nums[i]) {
                continue;
            }
            int slow = i, fast = next(i);
            // 判断非零且方向相同
            while (nums[slow] * nums[fast] > 0 && nums[slow] * nums[next(fast)] > 0) {
                if (slow == fast) {
                    if (slow != next(slow)) {
                        return true;
                    } else {
                        break;
                    }
                }
                slow = next(slow);
                fast = next(next(fast));
            }
            int add = i;
            while (nums[add] * nums[next(add)] > 0) {
                int tmp = add;
                add = next(add);
                nums[tmp] = 0;
            }
        }
        return false;
    }
};
```