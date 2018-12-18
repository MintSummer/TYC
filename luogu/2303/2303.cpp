#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;

    inline ll phi(ll x)
    {
        ll ans=x;
        for(ll i=2,limit=sqrt(x);i<=limit&&x>1;i++)
            if(!(x%i))
            {
                ans=ans/i*(i-1);
                while(!(x%i)) x/=i;
            }
        if(x!=1) ans=ans/x*(x-1); 
        return ans;
    }

    void work()
    {
        ll n,ans=0;
        scanf("%lld",&n);
        for(ll i=1,limit=sqrt(n);i<=limit;i++)
            if(!(n%i))
            {
                ans+=phi(i)*(n/i);
                if(i*i!=n) ans+=phi(n/i)*i;
            }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}