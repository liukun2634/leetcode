# 字符串总结

## 技巧总结

- 哈希表
- 双指针 （比较两个字符串）
- 滑动窗口
- 字典树


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



