#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
char str[maxn],po;
int t1,sum1,t2,sum2,len,st=0;
bool c=0;
void calc(int &t,int &sum){
    t=0,sum=0;
    int tmp=0;
    c=0;
    for(int i=st;i<len;i++){
        char k=str[i],kn=str[i+1];
       // printf("i=%d k=%c kn=%c\n",i,k,kn);
        if(k=='='){
            st=i+1;
            break;
        }
        if(k>='a' && k<='z'){
                t++;
                continue;
        }
        if(k == '-'){
            c=1;
            if(kn>='a' && kn<='z'){
                po=kn;
                t--;
                i++;
            }
            tmp=0;
            continue;
        }
        if(k == '+'){
            c=0;
            if(kn>='a' && kn<='z'){
                po=kn;
                t++;
                i++;
            }
            tmp=0;
            continue;
        }
        tmp=tmp*10+k-'0';
        if(kn>='a' && kn<='z'){
            po=kn;
            tmp= c==0 ? tmp : -tmp;
            t+=tmp;
            tmp=0;
            i++;
        }
        else if(kn == '+' || kn == '-'){
            tmp= c==0 ? tmp : -tmp;
            sum+=tmp;
            tmp=0;
        }
    }
    tmp= c==0 ? tmp : -tmp;
    sum+=tmp;
}
int main(){
    cin>>str;
    len=strlen(str);
    calc(t1,sum1);
    calc(t2,sum2);
    // cout<<t1<<' '<<sum1<<endl;
    // cout<<t2<<' '<<sum2<<endl;
    printf("%c=%.3lf",po,(double)(sum1-sum2)/(double)(t2-t1));
return 0;
}