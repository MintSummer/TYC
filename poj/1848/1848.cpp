#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

namespace TYC
{
    const int N=110,inf=10010;
    int n,cnt,Head[N],dp[N][3];

    struct edge
    {
		int to,next;
    }E[N*2];

    void add(int u,int v)
    {
		++cnt;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		Head[u]=cnt;
    }

    void dfs(int u,int fa)
    {
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			dfs(v,u);
			dp[u][1]+=dp[v][0];
		}
		dp[u][0]=dp[u][2]=inf;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			dp[u][2]=min(dp[u][2],dp[u][1]-dp[v][0]+min(dp[v][1],dp[v][2]));
			dp[u][0]=min(dp[u][0],dp[u][1]-dp[v][0]+dp[v][2]+1);
			for(int j=Head[u];j;j=E[j].next)
			{
				int k=E[j].to;
				if(k==fa||v==k) continue;
				dp[u][0]=min(dp[u][0],dp[u][1]-dp[v][0]-dp[k][0]+min(dp[v][1],dp[v][2])+min(dp[k][1],dp[k][2])+1);
			}
		}
			
    }

    void work()
    {
		while(~scanf("%d",&n))
		{
		    cnt=0;
			memset(Head,0,sizeof(Head));
			int u,v;
			for(int i=1;i<n;i++)
			{
				scanf("%d%d",&u,&v);
				add(u,v),add(v,u);
			}
			dfs(1,0);
			printf("%d\n",dp[1][0]>=inf?-1:dp[1][0]);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
