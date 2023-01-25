//
// Created by JODE on 2023-01-25.
//
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
class Solution {
public:

    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        int dis1[n], dis2[n];
        bool vis1[n], vis2[n];
        for (int i = 0; i < n; ++i) {
            dis1[i] = dis2[i] = 10000000;
            vis1[i] = vis2[i] = false;
        }
        queue<int> Q;
        Q.push(node1);
        dis1[node1] = 0;
        while (!Q.empty()){
            int node = Q.front();
            Q.pop();
            vis1[node] = true;
            if (edges[node]!=-1 && !vis1[edges[node]]){
                Q.push(edges[node]);
                dis1[edges[node]] = dis1[node] + 1;
            }
        }
        Q.push(node2);
        dis2[node2] = 0;
        while (!Q.empty()){
            int node = Q.front();
            Q.pop();
            vis2[node] = true;
            if (edges[node]!=-1 && !vis2[edges[node]]) {
                Q.push(edges[node]);
                dis2[edges[node]] = dis2[node] + 1;
            }
        }
        int minMax = 0x7fffffff, ans = -1;
        for (int i = 0; i < n; ++i) {
//            printf("%d %d\n", dis1[i], dis2[i]);
            if (dis1[i] == 10000000 || dis2[i] == 10000000)
                continue;
            if (minMax > max(dis1[i],dis2[i])){
                minMax = max(dis1[i],dis2[i]);
                ans = i;
            }
        }
        return ans;
    }
};