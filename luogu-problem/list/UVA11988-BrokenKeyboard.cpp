#include <cstdio>
#include <cstring>

const int maxn = 100000 + 5;
int last, cur, next[maxn];
char s[maxn];

int main(){
    while(scanf("%s", s + 1) == 1) {
        int n = strlen(s + 1);
        last = cur = 0;
        //增加s[0]是空字符 
        next[0] = 0;

        for(int i = 1; i <= n; i++){
            char ch = s[i];
            if(ch == '[') cur = 0;
            else if(ch == ']') cur = last;
            else{
                //cur 是光标位置， i 是字符位置
                next[i] = next[cur];
                next[cur] = i;
                //更新last位置
                if(cur == last) last = i;
                cur = i;
            }
        }

        for(int i = next[0]; i != 0; i = next[i]){
            printf("%c", s[i]);
        }
        printf("\n");
    }
    return 0;
}