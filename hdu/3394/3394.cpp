#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int MAXN=10010,inf=0x3f3f3f3f;
    int n,m,cnt,top,tim,bridge,num,conflict;
    int Head[MAXN],dfn[MAXN],st[MAXN],low[MAXN],in[MAXN],vis[MAXN];

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f=(ch=='-'?1:0),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int to,next;
    }E[100010*2];

    void add(int u,int v)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		Head[u]=cnt;
    }
    
    void init()
    {
    	cnt=tim=top=bridge=num=conflict=0;
    	memset(Head,0,sizeof(Head));
	memset(dfn,0,sizeof(dfn));
    }

    void count()
    {
		int line=0;
		for(int k=1;k<=num;k++)
		{
			int u=in[k];
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(vis[v]) line++;
			}
		}
		line/=2;
		if(line>num) conflict+=line;
    }

    void Tarjan(int u,int fa)
    {
		dfn[u]=low[u]=++tim;
		st[++top]=u;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			if(!dfn[v]) 
			{
				Tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u]) bridge++;
				if(low[v]>=dfn[u]) 
				{
					num=0;
					memset(vis,0,sizeof(vis));
					int x;
					do
					{
						x=st[top--];
						vis[x]=1;
						in[++num]=x;
					}
					while(x!=v);
					in[++num]=u;
					vis[u]=1;
					count();
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
    }

    void work()
    {
		while(1)
		{
			n=read(),m=read();
			if(n==0&&m==0) return;
			init();
			int u,v;
			for(int i=1;i<=m;i++)
			{
				u=read(),v=read();
				u++,v++;
				add(u,v),add(v,u);
			}
			for(int i=1;i<=n;i++)
				if(!dfn[i]) Tarjan(i,0);
			printf("%d %d\n",bridge,conflict);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
