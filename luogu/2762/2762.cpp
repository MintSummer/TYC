#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

namespace TYC
{
    const int MAXN=110,inf=0x3f3f3f3f;
    int M,N,cnt=1,S,T,ans;
    int money[MAXN],Head[MAXN],cur[MAXN],dep[MAXN];
    char tools[10010];

    struct edge
    {
		int to,next,w;
    }E[10010];

    void add(int u,int v,int w)
    {
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
    }
    
    void insert(int u,int v,int w)
    {
		add(u,v,w),add(v,u,0);
    }

    bool bfs()
    {
		memset(dep,-1,sizeof(dep));
		memcpy(cur,Head,sizeof(cur));
		queue<int> q;
		q.push(S);
		dep[S]=0;
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
		return dep[T]!=-1;
    }

    int dfs(int u,int mn)
    {
		if(u==T||mn==0) return mn;
		int v,w,used=0;
		for(int &i=cur[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(E[i].w>0&&dep[u]+1==dep[v])
			{
				w=dfs(v,min(mn-used,E[i].w));
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
		while(bfs()) ans-=dfs(S,inf);
    }

    void work()
    {
		cin>>M>>N;
		S=0,T=M+N+1;
		int x;
		for(int i=1;i<=M;i++)
		{
			scanf("%d",&x);
			ans+=x;
			insert(S,i,x);
			memset(tools,0,sizeof tools);
			cin.getline(tools,10000);
			int ulen=0,tool;
			while (sscanf(tools+ulen,"%d",&tool)==1)
			{
				insert(i,tool+M,inf);
				if (tool==0) ulen++;
				else while (tool) 
				{
					tool/=10;
					ulen++;
				}
				ulen++;
			}
		}
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&x);
			insert(i+M,T,x);
		}
		Dinic();
		for(int i=1;i<=M;i++)
			if(dep[i]>0) printf("%d ",i);
		printf("\n");
		for(int i=1;i<=N;i++)
			if(dep[i+M]>0) printf("%d ",i);
		printf("\n%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
