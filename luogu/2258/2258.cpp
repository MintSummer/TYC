#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
	const int inf=0x3f3f3f3f;
	int n,m,r,c,num,ans=inf;
	int dp[20][20],list[20],val[20][20],sum[20];
	
	inline int count(int x)
	{
		num=0;
		int now=m;
		while(x)
		{
			if(x&1) list[++num]=now;
			now--,x>>=1;
		}
		return num;
	}
	
	inline int Abs(int x){return x<0?-x:x;}
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		cin>>n>>m>>r>>c;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>val[i][j];
		for(int situ=0;situ<(1<<m);situ++)
			if(count(situ)==c)
			{
				memset(dp,inf,sizeof(dp));
				for(int i=1;i<=n;i++)
				{
					int res=0;
					for(int j=2;j<=num;j++)
						res+=Abs(val[i][list[j]]-val[i][list[j-1]]);
					dp[i][1]=res;

					memset(sum,0,sizeof(int[n+1]));
					for(int k=1;k<i;k++)
						for(int j=1;j<=num;j++)
							sum[k]+=Abs(val[i][list[j]]-val[k][list[j]]);

					for(int j=1;j<i;j++)
						for(int k=2,lim=min(j+1,r);k<=lim;k++)
							dp[i][k]=min(dp[i][k],dp[j][k-1]+sum[j]+res);
					ans=min(ans,dp[i][r]);
				}
			}
		cout<<ans<<"\n";
	}
}

int main()
{
	TYC::work();
	return 0;
}
