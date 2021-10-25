# 字符串总结

## 技巧总结

- 哈希表
- 双指针 （比较两个字符串）
- 滑动窗口 （子串， 一般加上哈希表记录窗口内数据） 
- 字典树
- 动态规划 (求回文子串/子序列，动态规划 dp[i][j] 从i开始 到j结尾)
- 翻转 （回文字符串性质）


## 求回文子串

动态规划 ：dp[i][j] 以 i 开始 j 结尾的字符串 是否为回文子串
　　　　　　记得 i 最好从 i + 1 向 0 减少 


其他方法：中心扩展， 回文子序列问题使用翻转求最大公共子序列

## 求最长无重复子串

子串考虑滑动窗口来统计个数，借助unodered_set 来维护一个窗口内的数据

## 字符串排序模板

先对长度进行判断，或者 长度相同再判断大小。

```C++
  sort(dictionary.begin(), dictionary.end(), [](string s1, string s2) {
      return s1.size() > s2.size() || (s1.size() == s2.size() && s1 < s2);
  });
```


```Java
Collections.sort(list, (a,b)->{
    if (a.length() != b.length()) return b.length() - a.length();
    return a.compareTo(b);
});

//方法2：
dictionary.sort((a,b)-> a.length() != b.length() ? b.length() - a.length() : a.compareTo(b));
```



