//
// Created by JODE on 2023-04-26.
//
class SmallestInfiniteSet {
private:
    priority_queue<int, vector<int>,greater<int> > Q;
    bool in[1001];
public:
    SmallestInfiniteSet() {
        for (int i = 1; i <= 1000 ; ++i) {
            Q.push(i);
            in[i] = true;
        }
    }

    int popSmallest() {
        int x = Q.top();
        Q.pop();
        in[x] = false;
        return x;
    }

    void addBack(int num) {
        if(in[num] == false){
            Q.push(num);
            in[num] = true;
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */