#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int MAXN=1e7+10,N=1e7;
	int T,cnt,tot,query[1010],ans[N],mu[MAXN],prime[N/10+10],f[N],a[1010],p[N];
	bool vis[MAXN];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void init()
	{
		mu[1]=1;
		for(int i=2;i<=N;i++)
		{
			if(!vis[i]) p[i]=prime[++cnt]=i,mu[i]=-1;
			for(int j=1;j<=cnt&&i*prime[j]<=N;j++)
			{
				int k=i*prime[j];
				vis[k]=1;
				p[k]=prime[j];
				if(i%prime[j]==0) {mu[k]=0;break;}
				else mu[k]=-mu[i];
			}
		}
	}

	int getans(int now,int pai,int val)
	{
		if(now>tot)
		{
			f[pai]+=val;
			return f[pai]*mu[pai];
		}
		return getans(now+1,pai*a[now],val)+getans(now+1,pai,val);
	}

	void work()
	{
		init();
		T=read();
		int mx=0;
		for(int i=1;i<=T;i++) 
			query[i]=read(),mx=max(mx,query[i]);
		for(int i=1;i<=mx;i++)
		{
			ans[i]+=ans[i-1];
			if(!mu[i]) continue;
			tot=0;
			int x=i;
			while(x>1) a[++tot]=p[x],x/=p[x];
			ans[i]+=mu[i]*getans(1,1,mu[i]);
		}
		for(int i=1;i<=T;i++)
			printf("%d\n",ans[query[i]]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
