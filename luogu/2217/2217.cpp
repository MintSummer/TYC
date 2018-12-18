#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

namespace TYC
{
	const int N=12;
	int n,m,k,G[N][N],sum[N][N];
	double ave,dp[N][N][N][N][N];

	double dfs(int a,int b,int c,int d,int cut)
	{
		if(dp[a][b][c][d][cut]!=-1) return dp[a][b][c][d][cut];
		if(!cut)
		{
			double res=sum[b][d]-sum[a-1][d]-sum[b][c-1]+sum[a-1][c-1];
			res=(res-ave)*(res-ave);
			return dp[a][b][c][d][cut]=res;
		}
		double res=1e12;
		for(int i=a+1;i<=b;i++)
			for(int j=0;j<cut;j++)
				res=min(res,dfs(a,i-1,c,d,j)+dfs(i,b,c,d,cut-j-1));//横着切j+1刀
		for(int i=c+1;i<=d;i++)
			for(int j=0;j<cut;j++)
				res=min(res,dfs(a,b,c,i-1,j)+dfs(a,b,i,d,cut-j-1));//竖着切
		return dp[a][b][c][d][cut]=res;
	}

	void work()
	{
		scanf("%d%d%d",&n,&m,&k);
		for(int a=1;a<=10;a++)
			for(int b=1;b<=10;b++)
				for(int c=1;c<=10;c++)
					for(int d=1;d<=10;d++)
						for(int f=0;f<=10;f++)
							dp[a][b][c][d][f]=-1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&G[i][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				sum[i][j]=sum[i-1][j]+sum[i][j-1]+G[i][j]-sum[i-1][j-1];
		ave=(double)sum[n][m]/k;
		dfs(1,n,1,m,k-1);
		printf("%.2lf\n",sqrt(dp[1][n][1][m][k-1]/k));
	}
}

int main()
{
	TYC::work();
	return 0;
}
