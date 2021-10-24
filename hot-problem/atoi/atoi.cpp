#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

int myAtoi(string s);

int main() {
    string s;
    getline(cin , s);
    cout<<"Input:" << s <<endl<< "Output:"<<myAtoi(s);
}

//case1: "123"
//case2: "   +123"
//case3: "   -223321   "
//case4: ""

int myAtoi(string s){
    long long res = 0;
    int start = 0, end = s.size();
    //1. handle branket
    while(start < end && s[start] == ' '){
        start++;
    }

    //2. + / -
    bool flag = false; //default is +
    if(start < end && (s[start] == '-' || s[start] == '+')){
        flag = (s[start] == '-');
        start++;
    }

    //3. calculate real value
    while(start < end && '0' <= s[start] && '9' >= s[start]){
        res = res * 10 + (s[start] - '0');
        if(!flag && res > INT_MAX) return INT_MAX;
        if(flag && res < INT_MIN) return INT_MIN;
        start++;
    }
    
    //4. return value check
    return flag? -res : res;
}
