#include <bits/stdc++.h>
#define ull unsigned long long 
using namespace std;
const int maxn=1e2+7;
int m,n,p,word[maxn],error;
string day[10];
string str,per[21],sentence[101],sayper[101];
int fake[maxn],act=0,ans=0;
void init(){
    day[1]="Today is Monday.";
    day[2]="Today is Tuesday.";
    day[3]="Today is Wednesday.";
    day[4]="Today is Thursday.";
    day[5]="Today is Friday.";
    day[6]="Today is Saturday.";
    day[7]="Today is Sunday.";
}
int judge(int pe,int val){
    if(fake[pe] && fake[pe]!=val)
        error=1;
    return val;
}
int main(){
    freopen(".in","r",stdin);
    init();
    scanf("%d %d %d",&m,&n,&p);
    for(int i=1;i<=m;i++)
        cin>>per[i];//输入人名
    for(int i=1;i<=p;i++){
        cin>>sayper[i];//输入说话的人
        sayper[i].erase(sayper[i].end()-1);//删除冒号
        for(int j=1;j<=m;j++)
        if(per[j]==sayper[i])
            word[i]=j;
        getline(cin,sentence[i]);//输入说话的句子
        sentence[i].erase(sentence[i].begin());//删除空格
        sentence[i].erase(sentence[i].end()-1);//这个地方莫名其妙。。不删洛谷能过，删了，洛谷过不了，本地能过。。。
    }
    for(int i=1;i<=7;i++)//枚举当前天
        for(int j=1;j<=m;j++){//枚举哪个人时罪犯
            error=0;//计数器，计算有多少人说假话
            fill(fake,fake+1+m,0);
            for(int k=1;k<=p;k++){//开始按句判断
                int nowper=word[k];
                if(sentence[k]=="I am guilty.")
                    fake[nowper]=judge(nowper,nowper==j ? 1 : -1);
                if(sentence[k]=="I am not guilty.")
                    fake[nowper]=judge(nowper,nowper!=j ? 1 : -1);  
                for(int o=1;o<=7;o++)
                    if(day[o]==sentence[k])
                        fake[nowper]=judge(nowper,o==i ? 1: -1);
                for(int po=1;po<=m;po++){
                    if(sentence[k]==per[po]+" is guilty.")
                        fake[nowper]=judge(nowper,po==j ? 1: -1);
                    if(sentence[k]==per[po]+" is not guilty.")
                        fake[nowper]=judge(nowper,po!=j ? 1: -1);   
                }
            }
            int cnt=0,nosure=0;
            for(int k=1;k<=m;k++){
                if(fake[k]==-1) cnt++;
                if(!fake[k])    nosure++;
            }

            if(!error && cnt<=n && cnt+nosure>=n){
                if(ans && ans!=j){
                    cout<<"Cannot Determine";
                    return 0;
                }
                ans=j;
            }
        }
        if(!ans)    cout<<"Impossible";
        else cout<<per[ans];
return 0;
}