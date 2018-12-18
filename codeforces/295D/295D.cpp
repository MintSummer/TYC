#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll p=1000000007;
	const int N=2010;
	int n,m;
	ll ans,dp[N][N],sum[N][N],sumk[N][N];
	
	inline void Mod(ll &x) {x=(x>=p?x-p:x);}
	
	void work()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			dp[1][i]=1;
			if(i!=1)
			{
				sum[1][i]=sum[1][i-1]+1;
				sumk[1][i]=sumk[1][i-1]+i;
			}
		}
		for(int i=2;i<=n;i++)
		{
			dp[i][1]=1;
			for(int j=2;j<=m;j++)
			{
				Mod(dp[i][j]=(sum[i-1][j]*(j+1)%p-sumk[i-1][j]+1+p));
				Mod(sum[i][j]=sum[i][j-1]+dp[i][j]);
				Mod(sumk[i][j]=sumk[i][j-1]+dp[i][j]*j%p);
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=2;j<=m;j++)
				Mod(ans+=(dp[i][j]-dp[i-1][j]+p)*dp[n-i+1][j]%p*(m-j+1)%p);
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
