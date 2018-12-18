#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=201,R=200,MaxBag=401;
    //用R防止背包空间减到负数,MaxBag控制背包空间不至于太多,最多只能拿n个地图
    int n,l,k,a[MAXN];
    double p[MAXN],dp[MAXN][MAXN][MaxBag];
    //dp[now][win][bag]表示到第now场后已经赢了win场和背包的空间

    void work()
    {
		scanf("%d%d%d",&n,&l,&k);
		for(int i=1;i<=n;i++) 
			scanf("%lf",&p[i]),p[i]/=100;
		for(int i=1;i<=n;i++) 
		{
			scanf("%d",&a[i]);
			a[i]=min(a[i],MaxBag);
		}
		dp[1][1][min(R+k+a[1],MaxBag)]=p[1];
		dp[1][0][min(R+k,MaxBag)]=1.0-p[1];
		for(int now=2;now<=n;now++)
			for(int win=0;win<now;win++)
				for(int bag=1;bag<=MaxBag;bag++)
				{
					dp[now][win+1][min(bag+a[now],MaxBag)]+=dp[now-1][win][bag]*p[now];
					dp[now][win][bag]+=dp[now-1][win][bag]*(1-p[now]);
				}
		double ans=0;
		for(int i=l;i<=n;i++) 
			for(int j=R;j<=MaxBag;j++)
				ans+=dp[n][i][j];
		printf("%.6lf",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
