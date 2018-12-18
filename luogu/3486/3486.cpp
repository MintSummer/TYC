#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=610;
	int n,k,a[N][N],dp[N][60],sum[N][N],last[N][60];
	
	void work()
	{
		scanf("%d %d",&n,&k);
		for(int i=1;i<n;i++)
			for(int j=i+1;j<=n;j++)
			{
				scanf("%d",&a[i][j]);
				sum[i][j]=sum[i][j-1]+a[i][j];
			}
		for(int i=1;i<=n;i++)
		{
			int num=0;
			for(int j=1;j<=i;j++) 
				for(int k=i+1;k<=n;k++)
					num+=a[j][k];
			dp[i][1]=num;
			for(int j=2,lim=min(i,k);j<=lim;j++)
			{
				int tot=0;
				for(int k=i-1;k>=j-1;k--)
				{
					tot+=sum[k+1][n]-sum[k+1][i];
					if(dp[k][j-1]+tot>dp[i][j])
						dp[i][j]=dp[k][j-1]+tot,last[i][j]=k;
					else if(dp[k][j-1]+tot==dp[i][j])
						last[i][j]=k;
				}
			}
		}
		static int ans[N];
		int now=0;
		for(int i=1;i<=n;i++) 
			if(dp[i][k]>dp[now][k]) now=i;
		for(int i=k;i;i--)
			ans[i]=now,now=last[now][i];
		for(int i=1;i<=k;i++)
			printf("%d ",ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
} 
