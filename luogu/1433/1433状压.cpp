#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
//设dp[i][s]表示从i点出发遍历集合为s的点的路程最小值（i也包括在s里），枚举s里的其他点进行转移。

namespace TYC
{
    int n;
    double x[20],y[20],dp[20][1<<16];

    double dis(int i,int j)
    {
		return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    }

    void work()
    {
		scanf("%d",&n);
		for(int i=1;i<=n;i++) 
			scanf("%lf%lf",&x[i],&y[i]);
		int all=(1<<n)-1;
		memset(dp,127,sizeof(dp));
		for(int s=1;s<=all;s++)
			for(int i=1;i<=n;i++)
			{
				if((s&(1<<(i-1)))==0) continue;
				if(s==(1<<(i-1))) {dp[i][s]=0;continue;}
				for(int j=1;j<=n;j++)
				{
					if( i==j || (s&(1<<(j-1)))==0 ) continue;
					dp[i][s]=min(dp[i][s],dp[j][s-(1<<(i-1))]+dis(i,j));
				}
			}
		double ans=1e9;
		for(int i=1;i<=n;i++)
			ans=min(ans,dp[i][all]+dis(0,i));
		printf("%.2lf",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
