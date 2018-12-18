#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    ll T,a0,a1,b0,b1;

    ll gcd(ll a,ll b)
    {
        return !b?a:gcd(b,a%b);
    }

    inline bool check(ll x)
    {
        return x%a1==0 && gcd(x/a1,a0/a1)==1 && gcd(b1/b0,b1/x)==1;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
		cin>>T;
		while(T--)
		{
			cin>>a0>>a1>>b0>>b1;
			ll limit=sqrt(b1),ans=0;
            for(int i=1;i<=limit;i++)
                if(!(b1%i))
                {
                    if(check(i)) ans++;
                    if(i*i!=b1) ans+=check(b1/i);
                }
			cout<<ans<<"\n";
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
