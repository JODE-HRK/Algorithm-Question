#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
int n,base;
void calc(int z,int base){
    if(!z)  return;
    int tmp=z%base;
    if(tmp<0)   tmp-=base,z+=base;
    calc(z/base,base);
    if(tmp<10)  printf("%d",tmp);
    else
        printf("%c",tmp-10+'A');
}
int main(){
    scanf("%d %d",&n,&base);
    printf("%d=",n);
    calc(n,base);
    printf("(base%d)",base);
return 0;
}
/*
30000=11011010101110000(base-2)
30000=00111010100110000


*/
