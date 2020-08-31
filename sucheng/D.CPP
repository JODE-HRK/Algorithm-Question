#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

char s[40];
int main(){
    int n;
    cin>>n;
    while(n--){
        cin>>s;
        int e=strlen(s);
        if(s[e-1]=='a'){
            cout<<s<<'s'<<endl;
            continue;
        }
        if(s[e-1]=='i'){
            cout<<s<<"os"<<endl;
            continue;
        }
        if(s[e-1]=='y'){
           for(int i=0;i<e-1;++i)cout<<s[i];
           cout<<"ios"<<endl; 
           continue;
        }
        if(s[e-1]=='l'){
            cout<<s<<"es"<<endl;
            continue;
        }
        if(s[e-1]=='n'){
            for(int i=0;i<e-1;++i)cout<<s[i];
            cout<<"anes"<<endl;
            continue;
        }
        if(s[e-1]=='e'&&s[e-2]=='n'){
            for(int i=0;i<e-2;++i)cout<<s[i];
            cout<<"anes"<<endl;
            continue;
        }
        if(s[e-1]=='o'){
            cout<<s<<"s"<<endl;
            continue;
        }
        if(s[e-1]=='r'){
            cout<<s<<"es"<<endl;
            continue;
        }
        if(s[e-1]=='t'){
            cout<<s<<"as"<<endl;
            continue;
        }
        if(s[e-1]=='u'){
            cout<<s<<"s"<<endl;
            continue;
        }
        if(s[e-1]=='v'){
            cout<<s<<"es"<<endl;
            continue;
        }
        if(s[e-1]=='w'){
            cout<<s<<"as"<<endl;
            continue;
        }
        cout<<s<<"us"<<endl;
    }
    return 0;
}