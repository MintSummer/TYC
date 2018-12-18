#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=50000;
    int cnt,tot,prime[N],vis[N];
    ll n,ans[N<<1];

    inline void init()
    {
        for(int i=2;i<=44800;i++)
        {
            if(!vis[i]) prime[++cnt]=i;
            for(int j=1;j<=cnt&&i*prime[j]<=44800;j++)
            {
                vis[i*prime[j]]=1;
                if(i%prime[j]==0) break;
            }
        }
    }

	bool is_prime(ll x)
	{
		if(x<=44800) return !vis[x];
		for(int i=1;prime[i]*prime[i]<=x;i++)
			if(x%prime[i]==0) return false;
		return true;
	}

    void dfs(int now,ll res,ll pai)
    {
        if(res==1) {ans[++tot]=pai;return;}
		if(res-1>=prime[now]&&is_prime(res-1))
			ans[++tot]=pai*(res-1);
        for(int i=now;prime[i]*prime[i]<=res;i++)
        {
            ll sum=1+prime[i],tmp=prime[i];
            for(;sum<=res;tmp*=1LL*prime[i],sum+=tmp)
                if(res%sum==0) dfs(i+1,res/sum,pai*tmp);
        }
    }

    void work()
    {
        init();
        while(~scanf("%lld",&n))
        {
            tot=0;
            dfs(1,n,1LL);
            sort(ans+1,ans+1+tot);
            printf("%d\n",tot);
            for(int i=1;i<tot;i++) printf("%lld ",ans[i]);
			if(tot) printf("%lld\n",ans[tot]);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
