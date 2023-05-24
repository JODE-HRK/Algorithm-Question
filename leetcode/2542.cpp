//
// Created by JODE on 2023-05-24.
//
//class Solution {
//
//
//private:
//    struct Treenode{
//        long long minn, sum;
//    };
//    vector<int> arr1, arr2;
//public:
//    void buildTree(int l,int r, int nodeId, Treenode *tree){
////        cout<<l<<" "<<r<<endl;
//        if(l == r){
//            tree[nodeId].sum = arr1[l - 1];
//            tree[nodeId].minn = arr2[l - 1];
//            return;
//        }
//        int mid = (l + r) >> 1;
//        buildTree(l, mid, nodeId << 1, tree);
//        buildTree(mid + 1, r, nodeId << 1 | 1, tree);
//        tree[nodeId].minn = min(tree[nodeId << 1].minn, tree[nodeId << 1 | 1].minn);
//        tree[nodeId].sum = tree[nodeId << 1].sum + tree[nodeId << 1 | 1].sum;
//    }
//
//    long long searchSum(int l, int r,int aiml, int aimr, int nodeId, Treenode *tree){
//        if (aimr < l || aiml > r)
//            return  0;
//        if(aiml <= l && r <= aimr){
//            return tree[nodeId].sum;
//        }
//        int mid = (l + r) >> 1;
//        long long sum = 0;
//        cout<<"SearchSum:  "<<l<<" "<<r<<" "<<aiml<<" "<<aimr<<" "<< nodeId << endl;
//        sum += searchSum(l, mid, aiml, aimr, nodeId << 1, tree);
//        sum += searchSum(mid + 1, r, aiml, aimr, nodeId << 1 | 1, tree);
//        return sum;
//    }
//
//    long long searchMin(int l, int r,int aiml, int aimr, int nodeId, Treenode *tree){
//        if (aimr < l || aiml > r)
//            return  10000000;
//        if(aiml <= l && aimr <= r){
//            return tree[nodeId].minn;
//        }
//        int mid = (l + r) >> 1;
//        long long minn = 0;
//        minn = min(searchSum(l, mid, aiml, aimr, nodeId << 1, tree) , searchSum(mid + 1, r, aiml, aimr, nodeId << 1 | 1, tree));
//        return minn;
//    }
//
//    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
//        int len = nums2.size();
//        Treenode tree[(len << 2) + 10];
//        arr1 = nums1, arr2 = nums2;
//        buildTree(1, len, 1, tree);
//        long long ans = 0;
//        for (int i = 0; i < len - k + 1; ++i) {
//            long long sum = searchSum(1, len, i + 1, i + k, 1, tree);
//            long long minn = searchMin(1, len, i + 1, i + k, 1, tree);
//            cout<<"FinAns:  " << i+1<<" "<<i+k+1<<" "<<sum<<" "<< minn<<endl;
//            ans = max(sum * minn, ans);
//        }
//        return ans;
//    }
//};
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {


        vector<pair<int,int>> v;

        for(int i=0;i<nums1.size();i++)
            v.push_back({nums2[i],nums1[i]});

        sort(v.rbegin(),v.rend());

        long long ans = 0;
        long long currSum = 0;

        priority_queue<int,vector<int>,greater<int>> pq;

        for(int i=0;i<k-1;i++){
            currSum += v[i].second;
            pq.push(v[i].second);
        }

        for(int i = k-1;i<nums1.size();i++){
            currSum += v[i].second;
            pq.push(v[i].second);
            ans = max(ans,currSum*v[i].first);

            currSum -= pq.top();
            pq.pop();
        }

        return ans;
    }
};