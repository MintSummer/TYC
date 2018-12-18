#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    int n,m;
    ll G[110][110],cnt[110][110],mn[110][110];
    double p[110];
    void work()
    {
		scanf("%d%d",&n,&m);
		int u,v;
		ll w;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=1e12;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%lld",&u,&v,&w);
			G[u][v]=G[v][u]=w;
			cnt[u][v]=cnt[v][u]=1;
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(G[i][j]>G[i][k]+G[k][j])
					{
						G[i][j]=G[i][k]+G[k][j];
						cnt[i][j]=cnt[i][k]*cnt[k][j];
					}
					else if(G[i][j]==G[i][k]+G[k][j])
						cnt[i][j]+=cnt[i][k]*cnt[k][j];
		for(int v=1;v<=n;v++)
			for(int s=1;s<=n;s++)
				for(int t=1;t<=n;t++)
					if(s!=v&&t!=v&&s!=t)
						if(G[s][t]==G[s][v]+G[v][t])
							p[v]+=(double)(cnt[s][v]*cnt[v][t])/cnt[s][t];
		for(int i=1;i<=n;i++) printf("%.3lf\n",p[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
