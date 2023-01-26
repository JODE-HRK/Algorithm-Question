//
// Created by JODE on 2023-01-26.
//

#include <vector>
#include <cstdio>
#include <queue>
using namespace std;
class Solution {
private:
    struct Edge{
        int to, price;
    };
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<Edge> edge[n];
        int dis[n];
        for (int i = 0; i < n; ++i) {
            dis[i] = 0x7fffffff;
        }
        for (auto e: flights){
            edge[e[0]].push_back(Edge{e[1], e[2]});
        }
        queue<pair<int, int>> Q;
        dis[src] = 0;
        int stops = 0;
        Q.push(make_pair(src, 0));
        while (stops <= k && !Q.empty()){
            int nowFloorSize = Q.size();
            while (nowFloorSize--){
                auto [node, distance] = Q.front();
                Q.pop();
                for (auto [nxtNode, cost] : edge[node]){
                    if (cost + distance >= dis[nxtNode])
                        continue;
                    dis[nxtNode] = cost + distance;
                    Q.push(make_pair(nxtNode, dis[nxtNode]));
                }
            }
            stops++;
        }
        if (dis[dst] == 0x7fffffff)
            return -1;
        return dis[dst];
    }
};