#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=5e4;
	int T,n,m,cnt,mu[N+10],prime[N+10],vis[N+10];
	ll f[N+10];
	
	void init()
	{
		mu[1]=1;
		for(int i=2;i<=N;i++)
		{
			if(!vis[i]) prime[++cnt]=i,mu[i]=-1;
			for(int j=1;j<=cnt&&i*prime[j]<=N;j++)
			{
				vis[i*prime[j]]=1;
				if(i%prime[j]==0)
				{
					mu[i*prime[j]]=0;
					break;
				}
				mu[i*prime[j]]=-mu[i];
			}
		}
		for(int i=1;i<=N;i++) mu[i]+=mu[i-1];
		for(int i=1;i<=N;i++)
			for(int l=1,r;l<=i;l=r+1)
			{
				r=i/(i/l);
				f[i]+=1LL*(r-l+1)*(i/l);
			}
	}
	
	void work()
	{
		init();
		scanf("%d",&T);
		while(T--)
		{
			scanf("%d%d",&n,&m);
			if(n>m) swap(n,m);
			ll ans=0;
			for(int l=1,r;l<=n;l=r+1)
			{
				r=min(n/(n/l),m/(m/l));
				ans+=1LL*(mu[r]-mu[l-1])*f[n/l]*f[m/l];
			}
			printf("%lld\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
