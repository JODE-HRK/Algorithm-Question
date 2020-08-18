/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-14 21:40:08
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-15 22:42:46
 */
class Solution
{
public:
    /**
     * 牛牛经过的房间数。
     * @param n int整型
     * @param x int整型
     * @param Edge Point类vector
     * @return int整型
     */
    enum
    {
        SIZE = 100010
    };
    int depth[SIZE];
    int max_depth[SIZE];
    int father[SIZE];
    //bool flag[SIZE];
    //int pre[SIZE];
    vector<int> g[SIZE];

    void dfs(int u, int parent)
    {

        depth[u] = depth[father[u] = parent] + 1;
        max_depth[u] = depth[u];

        vector<int> const &vec = g[u];
        for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (*it != parent)
            {
                dfs(*it, u);
                max_depth[u] = max(max_depth[u], max_depth[*it]);
            }
        }
    }

    int solve(int n, int x, vector<Point> &Edge)
    {
        if (1 == x)
            return 0;
        int INF = 1000000000;
        for (int i = 1; i <= n; ++i)
            g[i].clear();
        //fill(flag,flag+n+1,false);
        //fill(depth,depth+n+1,INF);

        for (vector<Point>::const_iterator it = Edge.begin(); it != Edge.end(); ++it)
        {
            g[it->x].push_back(it->y);
            g[it->y].push_back(it->x);
        }

        depth[0] = -1;
        dfs(1, 0);

        int ans = 0;
        int u = x;
        do
        {
            int t1 = depth[u];
            int tx = depth[x] - depth[u];
            if (tx < t1)
            {
                ans = max(ans, max_depth[u]);
            }
            else
            {
                break;
            }
        } while (u = father[u]);
        return ans + 1;
        /*
        queue<int> q;
        q.push(1);
        flag[1] = true;
        d[1] = 0;
        while(!q.empty()){
            int h = q.front();
            q.pop();

            vector<int>const& vec = g[h];
            for(vector<int>::const_iterator it=vec.begin();it!=vec.end();++it){
                if(d[*it]==INF){
                    d[*it] = d[h] + 1;
                    q.push(*it);
                    pre[*it] = h;
                }
            }
        }//*/
    }
};