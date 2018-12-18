#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=310;
    int n,m,cnt,ans,Head[N],fa[N],vis[N],to[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int to,next;
    }E[6010*2];

    void add(int u,int v)
    {
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
    }

    bool Path(int u,int tim)
    {
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]==tim) continue;
			vis[v]=tim;
			if(fa[v]==-1||Path(fa[v],tim))
			{
				fa[v]=u;
				to[u]=v;	
				return true;
			}
		}
		return false;
    }

    void Hungary()
    {
		memset(fa,-1,sizeof(fa));
		ans=n;
		for(int i=1;i<=n;i++)
			if(Path(i,i)) ans--;
    }

    void work()
    {
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read()+n;
			add(u,v);
		}
		Hungary();
		for(int i=1;i<=n;i++)
		{
			if(vis[i]==n+1||fa[i]!=-1) continue;
			int x=i;
			do
			{
				printf("%d ",x);
				vis[x]=n+1;
				x=to[x]-n;
			}
			while(x>0);
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
