#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=1010,inf=0x3f3f3f3f;
    int n,k,s,t,cnt=1,Head[N],dis[N],pre[N],vis[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct interval
    {
	int l,r;
	bool operator < (const interval &a) const
	{
	    return l<a.l;
	}
    }a[510];

    struct edge
    {
		int from,to,next,w,c;
    }E[N*N*4];

    void insert(int u,int v,int w,int c)
    {
		E[++cnt]=(edge){u,v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){v,u,Head[v],0,-c};
		Head[v]=cnt;
    }

    bool spfa()
    {
		memset(vis,0,sizeof(vis));
		memset(pre,0,sizeof(pre));
		for(int i=1;i<=t;i++) dis[i]=-inf;
		queue<int> q;
		q.push(s);
		dis[s]=0;vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w>0&&dis[v]<dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[t]!=-inf;
    }

    int mcmf()
    {
		int ans=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i].from])
			mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i].from])
			E[i].w-=mn,E[i^1].w+=mn;
			ans+=mn*dis[t];
		}
		return ans;
    }

    void work()
    {
		n=read(),k=read();
		for(int i=1;i<=n;i++)
		{
			int l=read(),r=read();
			if(l>r) swap(l,r);
			a[i]=(interval){l,r};	
		}
		sort(a+1,a+1+n);
		int ss=n*2+1;
		s=ss+1,t=s+1;
		for(int i=1;i<=n;i++)
		{
			insert(ss,i,1,0);
			insert(i+n,t,1,0);
			insert(i,i+n,1,(a[i].r-a[i].l));
			for(int j=1;j<i;j++)
			    if(a[i].l>=a[j].r) insert(j+n,i,1,0);
		}
		insert(s,ss,k,0);
		printf("%d",mcmf());
    }
}

int main()
{
    TYC::work();
    return 0;
}
