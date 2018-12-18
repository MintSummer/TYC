#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=50000;
	typedef long long ll;
	ll n,ans;
	int cnt,prime[N+10],vis[N+10];

	inline void init()
	{
		for(int i=2;i<=N;i++)
		{
			if(!vis[i]) prime[++cnt]=i;
			for(int j=1;j<=cnt&&(ll)i*prime[j]<=N;j++)
			{
				vis[i*prime[j]]=1;
				if(i%prime[j]==0) break;
			}
		}
	}

	bool is_prime(ll x)
	{
		if(x<=N) return !vis[x];
		for(int i=1;i<=cnt&&prime[i]<=x;i++)
			if(!(x%prime[i])) return false;
		return true;
	}

	void dfs(int last,ll rest,ll x)
	{
		if(rest==1) 
			{ans=min(ans,x);return;}
		if(rest>floor(sqrt(n))&&is_prime(rest+1)) 
			{ans=min(ans,x*(rest+1));return;}
		for(int i=last+1;i<=cnt&&prime[i]<=rest;i++)
			if(!(rest%(prime[i]-1))) 
			{
				ll tmp=rest/(prime[i]-1),val=x*(ll)prime[i];
				dfs(i,tmp,val);
				while(tmp%prime[i]==0) 
				{
					tmp/=prime[i];
					val*=(ll)prime[i];
					dfs(i,tmp,val);
				}
			}
	}

	void work()
	{
		init();
		scanf("%lld",&n);
		ans=2147483648LL;
		dfs(0,n,1);
		if(ans>2147483647LL) printf("-1\n");
		else printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
