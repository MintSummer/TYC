#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10,inf=0x3f3f3f3f;
    int T,n,m,sword[N],reward[N],c[N];
    ll a[N],p[N];
    multiset<ll> s;
	
	ll mul(ll x,ll y,ll mod)
	{
		ll ans=0;
		for(;y;y>>=1,x=(x+x)%mod)
			if(y&1) ans=(ans+x)%mod;
		return ans;
	}

    ll solve_p1()
    {
        ll ans=0;
        for(int i=1;i<=n;i++)
            ans=max(ans,a[i]/c[i]+(a[i]%c[i]!=0));
        return ans;
    }

    ll exgcd(ll A,ll B,ll &x,ll &y)
    {
        if(!B) {x=1,y=0;return A;}
        ll g=exgcd(B,A%B,x,y);
        ll tmp=x;
        x=y;
        y=tmp-A/B*y;
        return g;
    }

    ll excrt()
    {
        ll ans=a[1],M=p[1];
        for(int i=2;i<=n;i++)
        {
            ll x,y,b=p[i],c=(a[i]-ans%p[i]+p[i])%p[i];
            ll g=exgcd(M,b,x,y);
            if(c%g) return -1;
            b/=g;
            x=mul(x,c/g,b);
            ans+=M*x;
            M*=b;
            ans=(ans%M+M)%M;
        }
        return ans;
    }

    ll solve()
    {
        ll x,y;
        for(int i=1;i<=n;i++)
        {
            ll g=exgcd(c[i],p[i],x,y);
            if(a[i]%g) return -1;
            p[i]=p[i]/g;
			x=(x%p[i]+p[i])%p[i];
            a[i]=mul(x,a[i]/g,p[i]);
        }
        return excrt();
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>T;
        while(T--)
        {
            s.clear();
            cin>>n>>m;
            int flag=1;
            for(int i=1;i<=n;i++) cin>>a[i];
            for(int i=1;i<=n;i++) 
                cin>>p[i],flag&=(p[i]==1);
            for(int i=1;i<=n;i++) cin>>reward[i];
            for(int i=1;i<=m;i++) 
                cin>>sword[i],s.insert(sword[i]);
			multiset<ll>::iterator it;
            for(int i=1;i<=n;i++)
            {
				it=(a[i]<(*s.begin())?s.begin():(--s.upper_bound(a[i])));
				c[i]=*it;
				s.erase(it);
                s.insert(reward[i]);
            }
            if(flag) cout<<solve_p1()<<"\n";
            else cout<<solve()<<"\n";
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
