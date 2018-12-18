#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

namespace TYC
{
	const double eps=1e-6;
	const int N=110,M=10010;
	int n,m,cnt,Head[N],bin[N],deg[N];
	double ans,f[N][N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int to,next,w;
	}E[M<<1];
	
	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}
	
	void Gauss()
	{
		for(int i=1;i<=n;i++)
		{
			int pos=i;
			for(int j=i+1;j<=n;j++)
				if(fabs(f[j][i])-fabs(f[pos][i])>eps) pos=j;
			if(pos!=i)
				for(int j=1;j<=n+1;j++) swap(f[i][j],f[pos][j]);
			for(int j=1;j<=n;j++)
				if(i!=j)
				{
					double tmp=f[j][i]/f[i][i];
					for(int k=1;k<=n+1;k++)
						f[j][k]-=tmp*f[i][k];
				}
		}
		for(int i=1;i<=n;i++)
			f[i][n+1]/=f[i][i];
	}
	
	void solve(int pos)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n+1;j++)
				f[i][j]=0.0;
		f[n][n]=-1.0;
		for(int u=1;u<n;u++)
		{
			f[u][u]=-deg[u];
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&bin[pos]) f[u][v]--,f[u][n+1]--;
				else f[u][v]++;
			}
		}
		Gauss();
		ans+=(double)bin[pos]*f[1][n+1];
	}
	
	void work()
	{
		n=read(),m=read();
		int mx=0;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			mx=max(mx,w);
			add(u,v,w),deg[u]++;
			if(u!=v) add(v,u,w),deg[v]++;
		}
		bin[1]=1;
		for(int i=2;i<=32;i++) bin[i]=bin[i-1]<<1;
		for(int i=1;bin[i]<=mx&&i<=32;i++) solve(i);
		printf("%.3f",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
