#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;

namespace TYC
{
    const int N=10000010,p=100000009;
    int T,n,m,tot,prime[N>>3],sum[N],f[N];
    bool vis[N];

    void init()
    {
		f[1]=1;
		for(int i=2;i<=N-10;i++)
		{
			if(!vis[i])
			{
				prime[++tot]=i;
				f[i]=((1-i)*i%p+p)%p;
			}
			for(int j=1;j<=tot&&i*prime[j]<=N-10;j++) 
			{
				vis[i*prime[j]]=1;
				if(i%prime[j]==0)
				{
					f[i*prime[j]]=f[i]*prime[j]%p;
					break;
				}
				f[i*prime[j]]=f[i]*f[prime[j]]%p;
			}
		}
		for(int i=1;i<=N-10;i++) sum[i]=sum[i-1]+f[i];
    }

    int tmp(int x)
    {
		return (x+1)*x/2%p;
    }

    int S(int x,int y)
    {
		return tmp(x)*tmp(y)%p;
    }

    void work()
    {
		init();
		scanf("%lld",&T);
		while(T--)
		{
			scanf("%lld%lld",&n,&m);
			if(n>m) swap(n,m);
			int ans=0;
			for(int i=1,tmp;i<=n;i=tmp+1)
			{
				tmp=min(n/(n/i),m/(m/i));
				ans=(ans+(sum[tmp]-sum[i-1]+p)*S(n/i,m/i)%p)%p;
			}
			printf("%lld\n",ans);
		}
    }
}

signed main()
{
    TYC::work();
    return 0;
}
