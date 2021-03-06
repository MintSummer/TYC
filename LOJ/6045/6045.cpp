#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=610,inf=5e6;
    int n,cnt=1,Head[MAXN],s,t,dep[MAXN],q[MAXN*20];

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int to,next,w;
    }E[500010];

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
		int h=0,t=1;
		q[0]=s;
		dep[s]=0;
		while(h<t)
		{
			int u=q[h++];
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dep[v]==-1)
					dep[v]=dep[u]+1,q[t++]=E[i].to;
			}
		}
		return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
		if(u==t) return mn;
		int used=0,w;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(dep[v]==dep[u]+1)
			{
				w=dfs(v,min(mn-used,E[i].w));
				E[i].w-=w,E[i^1].w+=w;
				used+=w;
				if(used==mn) return used;
			}
		}
		if(!used) dep[u]=-1;
		return used;
    }

    int Dinic()
    {
		int ans=0;
		while(bfs()) ans+=dfs(s,inf);
		return ans;
    }

    void work()
    {
		n=read();
		s=(n<<1)+1;t=s+1;
		for(int i=1;i<=n;i++)
		{
			int t=read();
			while(t--)
			{
				int x=read();
				insert(i,x+n,inf);
			}
		}
		for(int i=1;i<=n;i++)
			insert(i+n,t,inf);
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			int x=read();
			insert(s,i,inf-x);
			sum+=inf-x;
		}
		printf("%d",Dinic()-sum);
    }
}

int main()
{
    TYC::work();
    return 0;
}
