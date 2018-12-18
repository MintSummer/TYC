#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=35,p=2017;
	int n,m,k;
	
	struct Matrix 
	{
		int G[N][N];
		Matrix(){memset(G,0,sizeof(G));}
		Matrix operator * (const Matrix &t) const
		{
			Matrix ans;
			for(int i=0;i<=n;i++)
				for(int k=0;k<=n;k++)
					for(int j=0;j<=n;j++)
						ans.G[i][j]=(ans.G[i][j]+G[i][k]*t.G[k][j])%p;
			return ans;
		}
	}M;
	
	Matrix qpow(Matrix &m,int tim)
	{
		Matrix ans;
		for(int i=1;i<=n;i++) ans.G[i][i]=1;
		for(;tim;tim>>=1,m=m*m)
			if(tim&1) ans=ans*m;
		return ans;
	}
	
	void work()
	{
		scanf("%d%d",&n,&m);
		int u,v;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			M.G[u][v]++,M.G[v][u]++;
		}
		for(int i=0;i<=n;i++) M.G[i][i]++;
		for(int i=1;i<=n;i++) M.G[i][0]++;
		scanf("%d",&k);
		Matrix res=qpow(M,k);
		int ans=0;
		for(int i=0;i<=n;i++) ans=(ans+res.G[1][i])%p;
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
} 
