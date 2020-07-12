#include <bits/stdc++.h>
using namespace std;
struct OP
{
    int num, id;
};
vector<OP> V[2];
vector<int> S[101];
int n, id = 0;
void ct()
{
    int p = 1;
    while (p)
    {
        V[!id].clear();
        for (int i = 0; i < V[id].size(); i++)
        {
            int now = V[id][i].id;
            if (i + 1 < V[id].size()){
                int nxt = V[id][i].id;
                
            }
        }
    }
}
int main()
{
    
    return 0;
}