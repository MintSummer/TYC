#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1010;
    int n,num;
    map<ll,int> tim;
    map<ll,int>::iterator it;

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>num;
        ll val,ans=0;
        for(int i=1;i<=n;i++) 
        {
            cin>>val;
            for(ll j=1,lim=sqrt(val);j<=lim;j++)
                if(!(val%j)) 
                {
                    tim[j]++;
                    if(j*j!=val) tim[val/j]++;
                }
        }
        for(it=tim.begin();it!=tim.end();it++)
            if(it->second>=num) ans=max(ans,it->first);
        cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}