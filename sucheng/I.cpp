#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;



int main(){
    int n1,n2,n12;
    cin>>n1>>n2>>n12;

    int ans=(n1+1)*(n2+1)/(n12+1)-1;
    cout<<ans<<endl;
    return 0;
}