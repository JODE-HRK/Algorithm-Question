//
// Created by JODE on 2023-03-22.

#include "vector"
#include "queue"
using namespace std;
class Solution {
private:
    struct Edge{
        int to, distance, edgeId;
    };
    vector<Edge> edge[100001];
public:
    int minScore(int n, vector<vector<int>>& roads) {
        int count = 0;
        for(auto e: roads){
            ++count;
            edge[e[0]].push_back(Edge{e[1],e[2], count});
            edge[e[1]].push_back(Edge{e[0],e[2], count});
        }
        int t[n + 1];
        queue<int> Q;
        fill(t,t+n+1, 100007);
        Q.push(1);
        while (!Q.empty()){
            int nowNode = Q.front();
            Q.pop();
            for(auto e: edge[nowNode]){
                if (t[e.to] > e.distance || t[e.to] > t[nowNode]){
                    t[e.to] = min(t[nowNode], e.distance);
                    Q.push(e.to);
                }
            }
        }
        return t[n];
    }
};