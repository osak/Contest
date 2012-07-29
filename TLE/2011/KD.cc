#include <iostream>
#include <map>
#include <vector>
using namespace std;
map<vector<int>,int> m;
int k;
int r(vector<int>&v,vector<int>&w,vector<int>&x,int i){
    if(i==k)return m[x];
    int s=0;
    for(int j=v[i];j<=w[i];++j){x[i]=j;s+=r(v,w,x,i+1);}
    return s;
}
int main(){
    int t,n,q;
    cin>>t;
    while(t--){
        m.clear();
        cin>>k>>n>>q;
        vector<int>v(k),w(k),x(k);
        while(q--){
            int f,p,i;
            cin>>f;
            if(f){
                for(i=0;i<k;++i)cin>>v[i];
                for(i=0;i<k;++i)cin>>w[i];
                cout<<r(v,w,x,0)<<endl;
            }
            else{
                for(i=0;i<k;++i)cin>>v[i];
                cin>>p;
                m[v]+=p;
            }
        }
    }
    return 0;
}
