#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p=1e9+7;
    int n,k;

    ll inv(ll x)
    {
		ll ans=1,tim=p-2;
		for(;tim;tim>>=1,x=x*x%p)
			if(tim&1) ans=ans*x%p;
		return ans;
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n>>k;
		ll ans=inv(n);
		for(int i=1;i<=n-2;i++)
			if(i<k||(k&&i==n-2)) 
				ans=(1-ans)*inv(n-i-1)%p;
		cout<<(ans+p)%p<<endl;
    }
}

int main()
{
    TYC::work();
    return 0;
}
