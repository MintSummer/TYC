#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;

namespace TYC
{
    const int N=3010,inf=0x3f3f3f3f;
    int n,m,cnt,Head[N],dp[N][N],leaf[N];

    struct edge
    {
		int to,next,w;
    }E[N*2];

    void init()
    {
    	cnt=0;
		memset(Head,0,sizeof(Head));
		memset(leaf,0,sizeof(leaf));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) 
				dp[i][j]=-inf;
    }

    void add(int u,int v,int w)
    {
    	++cnt;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void dfs(int u,int f)
    {
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u);
			leaf[u]+=leaf[v];
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			for(int h=leaf[u];h>=1;h--)
				for(int g=1;g<=leaf[v];g++)
					if(h>=g) dp[u][h]=max(dp[u][h],dp[u][h-g]+dp[v][g]-E[i].w);//树上背包
					else break; 
		}
    }

    void work()
    {
		while(~scanf("%d%d",&n,&m))
		{
			init();
			int tmp,v,w;
			for(int u=1;u<=n-m;u++)
			{
				scanf("%d",&tmp);
				while(tmp--)
				{
					scanf("%d%d",&v,&w);
					add(u,v,w),add(v,u,w);
				}
			}
			for(int i=n-m+1;i<=n;i++)
			{
				scanf("%d",&dp[i][1]);
				leaf[i]=1;
			}
			dfs(1,0);
			int ans=-inf;
			for(int i=m;i>=0;i--)
				if(dp[1][i]>=0) {ans=i;break;}
			printf("%d\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
