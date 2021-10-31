#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;


void calc(stack<int>& nums, stack<char>& ops){
    if(nums.empty() || nums.size() < 2) return;
    if(ops.empty()) return;
    
    int b = nums.top();
    nums.pop();
    int a = nums.top();
    nums.pop();

    char op = ops.top();
    ops.pop();

    int ans = 0;
    if(op == '+') ans = a + b;
    else if(op == '-') ans = a - b;
    else if(op == '*') ans = a * b;
    else if(op == '/') ans = a / b;
    
    // cout<<a<<" "<<op<<" "<<b<<endl;
    nums.push(ans);
}

int calculate(string s){
    unordered_map<char, int> order ={
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };
    stack<char> ops; 
    stack<int> nums;

    //细节处理 "-2+ 1"
    nums.push(0);


    //1.去掉s 中所有空格
    string str;
    int n = s.size();
    for(int i = 0; i < n; i++){
        if(s[i] != ' '){
            str.push_back(s[i]);
        }
    }
    s = str;
    n = s.size();
    
    for(int i = 0; i < n; i++){
        char c = s[i];
        if(c == '('){
            ops.push(c);
        } else if(c == ')'){
            while(!ops.empty() && ops.top() != '('){
                //计算一直到左括号的
                calc(nums, ops);
            }
            ops.pop();
        } else if(c <= '9' && c >='0'){
            //一直计数到不是数字，或者结束
            int j = i;
            int num = 0;
            while(j < n && (s[j] <= '9' && s[j] >='0')){
                num = num * 10 + (s[j] - '0');
                j++;
            }
            //压入 nums 栈
            nums.push(num);
            //更新新的i
            i = j - 1;
        } else {
            //细节处理
            //为防止 () 内出现的首个字符为运算符，将所有的空格去掉，并将 (- 替换为 (0-
            if(i > 0 && (s[i - 1] == '(' || s[i - 1] == '-'  || s[i - 1] == '+')){
                nums.push(0);
            }

            //把前面比当前操作符优先级高的运算都计算完成
            while(!ops.empty() && ops.top() != '(' ){
                char pre = ops.top();
                if (order[pre] >= order[c]){
                    calc(nums, ops);
                } else {
                    break;
                }
            }
            //当前运算符入栈
            ops.push(c);
        }
    }

    //把剩余运算也完成了
    while (!ops.empty()) {
        calc(nums, ops);
    }
    return nums.top();
}

int main(){
    string s;
    getline(cin, s);

    cout<<"result: "<<calculate(s);
    
    return 0;
}
