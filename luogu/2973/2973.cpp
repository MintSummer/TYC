#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

namespace TYC
{
	const double eps=1e-8;
	const int N=310;
	int n,m,p,q,cnt,Head[N],deg[N];
	double f[N][N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int to,next;
	}E[N*N];
	
	inline void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}
	
	void Gauss()
	{
		for(int i=1;i<=n;i++)
		{
			int pos=i;
			for(int j=i+1;j<=n;j++)
				if(fabs(f[j][i])-fabs(f[pos][i])>eps) pos=i;
			if(pos!=i)
				for(int j=1;j<=n+1;j++) swap(f[i][j],f[pos][j]);
			for(int j=1;j<=n;j++) if(i!=j)
			{
				double tmp=f[j][i]/f[i][i];
				for(int k=1;k<=n+1;k++)
					f[j][k]-=f[i][k]*tmp;
			}
		}
		for(int i=1;i<=n;i++) f[i][n+1]/=f[i][i];
	}
	
	void work()
	{
		n=read(),m=read(),p=read(),q=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
			deg[u]++,deg[v]++;
		}
		f[1][n+1]=-1;
		double tmp=1-(double)p/q;
		for(int u=1;u<=n;u++)
		{
			f[u][u]=-1;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				f[u][v]=tmp*1.0/deg[v];
			}
		}
		Gauss();
		for(int i=1;i<=n;i++)
		{
			double ans=f[i][n+1]*(double)p/q;
			if(fabs(ans)<eps) printf("0.000000000\n");
			else printf("%.9f\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
