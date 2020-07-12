const int maxn = 4010;
class Solution {
public:
    string longestPalindrome(string s) {
        string str = "$";
        for(int i=0;i<s.length();i++)
            str+='#',str+=s[i];
        str+="#";
        int p[maxn];
        memset(p,0,sizeof(p));
        int ans = 0, id=0,mx =0,pos;
        string sans;
        for(int i=1;i<str.length();i++){
            if(i<mx)
                p[i] = min(mx-i,p[2*id-1]);
            else
                p[i] = 1;
            while(str[i+p[i]] == str[i-p[i]])
                p[i]++;
            if(mx<i+p[i])
                id = i, mx = i+p[i];
            if(ans<p[i]){
                ans = max(p[i],ans);    
                pos = i;
            }
        }
        cout<<pos<<' '<<p[pos]<<endl;
        sans = str.substr(pos-p[pos]+1,p[pos]*2-1);//截取出那一段
        cout<<sans<<endl;
        sans.erase(remove(sans.begin(),sans.end(),'#'),sans.end());
        //sans.erase(remove(sans.begin(),sans.end(),'$'),sans.end());
        return sans;
    }
};