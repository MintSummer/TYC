//关于这个最小路径覆盖,我写过题解,参见https://www.luogu.org/problemnew/solution/P4298 祭祀
//都是0ms hungary码长短
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=310,inf=0x3f3f3f3f;
    int n,m,s,t,cnt=1,ans,Head[N],dep[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int to,next,w;
    }E[6010*2];

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
		ans=n;
		while(bfs()) ans-=dfs(s,inf);
	}

    void work()
    {
		n=read(),m=read();
		s=n*2+1,t=n*2+2;
		for(int i=1;i<=n;i++)
			insert(s,i,1),insert(i+n,t,1);
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read()+n;
			insert(u,v,1);
		}
		Dinic();
		for(int i=Head[s];i;i=E[i].next)
		{
		    if(!E[i].w) continue;
		    int x=E[i].to;
		    do
		    {
				printf("%d ",x);
				x+=n;
				for(int j=Head[x];j;j=E[j].next)
					if(E[j].w) {x=E[j].to;break;}
		    }
		    while(x<=n);
		    puts("");
		}
		printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
