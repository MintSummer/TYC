#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	int n,r,sum[5010][5010];

	void work()
	{
		scanf("%d%d",&n,&r);
		int x,y,v;
		for(int i=1;i<=n;i++)
		{	
			scanf("%d%d%d",&x,&y,&v);
			sum[x+1][y+1]=v;
		}
		for(int i=1;i<=5000;i++)
			for(int j=1;j<=5000;j++)
				sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		int ans=0;
		for(int i=r;i<=5000;i++)
			for(int j=r;j<=5000;j++)
				ans=max(ans,sum[i][j]-sum[i-r][j]-sum[i][j-r]+sum[i-r][j-r]);
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
