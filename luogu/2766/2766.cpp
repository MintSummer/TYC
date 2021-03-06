#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

namespace TYC
{
    const int N=10010,inf=0x3f3f3f3f;
    int n,len,s,t,cnt=1,ans=0,a[N],dep[N*2],Head[N*2],dp[N];

    struct edge
    {
		int to,next,w;
    }E[N*400];

    void insert(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0};
        Head[v]=cnt;
    }
    
    bool bfs()
    {
        memset(dep,-1,sizeof(dep));
        queue<int> q;
        q.push(s);
        dep[s]=0;
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w>0&&dep[v]==-1) 
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==t) return mn;
        int w,used=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(E[i].w>0&&dep[v]==dep[u]+1)
            {
                w=dfs(v,min(E[i].w,mn-used));
                used+=w;
                E[i].w-=w,E[i^1].w+=w;
                if(used==mn) return used;
            }
        }
        if(!used) dep[u]=-1;
        return used;
    }

    void Dinic()
    {
		while(bfs()) ans+=dfs(s,inf);
    }

    void get_len()
    {
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++)
				if(a[j]<=a[i]) dp[i]=max(dp[i],dp[j]+1);
		for(int i=1;i<=n;i++) len=max(len,dp[i]);
		printf("%d\n",len);
    }

    void work()
    {
		scanf("%d",&n);
		for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]),dp[i]=1;
		get_len();
		s=2*n+1,t=2*n+2;
		for(int i=1;i<=n;i++)
		{
			if(dp[i]==1) insert(s,i,1);
			if(dp[i]==len) insert(i+n,t,1);
		}
		for(int i=1;i<=n;i++) insert(i,i+n,1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++)
				if(a[j]<=a[i]&&dp[j]+1==dp[i]) insert(j+n,i,1);
		Dinic();
		printf("%d\n",ans);
		insert(s,1,inf),insert(1,1+n,inf);
		if(dp[n]==len) insert(n,n*2,inf),insert(n*2,t,inf);
		Dinic();
		printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
