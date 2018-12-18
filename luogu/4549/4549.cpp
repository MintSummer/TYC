#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    #define Abs(x) x<0?-x:x
    int n;ll t,ans;
    
    ll gcd(ll a,ll b)
    {
        return !b?a:gcd(b,a%b);
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
		cin>>n;
        cin>>ans;ans=Abs(ans);
        for(int i=2;i<=n;i++)
        {
            cin>>t;t=Abs(t);
            ans=gcd(ans,t);
        }
        cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
