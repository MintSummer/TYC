#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

namespace TYC
{
    const int N=200010,M=400010,inf=0x3f3f3f3f;
    typedef long long ll;
    typedef pair<int,int> pa;
    int T,n,m,ccnt,tot,cnt,Head[N],dis[N<<1],vis[N],fa[N<<1],head[N<<1],val[N<<1],dep[N<<1],f[N<<1][20];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct k_edge
    {
		int u,v,l,a;
		bool operator < (const k_edge &d) const
		{
			return a>d.a;
		}
    }ee[M];

    struct d_edge
    {
		int to,next,w;
    }E[M*2];

    struct edge
    {
		int to,next;
    }e[N*5];

    void insert(int u,int v,int w)
    {
		E[++ccnt]=(d_edge){v,Head[u],w};
		Head[u]=ccnt;
		E[++ccnt]=(d_edge){u,Head[v],w};
		Head[v]=ccnt;
    }

    void add(int u,int v)
    {
		e[++cnt]=(edge){v,head[u]};
		head[u]=cnt;
    }

    void dijkstra()
    {
		priority_queue<pa,vector<pa>,greater<pa> > q;
		dis[1]=0;
		q.push(make_pair(dis[1],1));
		while(!q.empty())
		{
			int u=q.top().second;
			q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(vis[v]) continue;
				if(dis[v]>dis[u]+E[i].w)
				{
					dis[v]=dis[u]+E[i].w;
					q.push(make_pair(dis[v],v));
				}
			}
		}
    }

    int find(int a)
    {
		return a==fa[a]?a:fa[a]=find(fa[a]);
    }

    void kruskal()
    {
		sort(ee+1,ee+1+m);
		for(int i=1;i<=n;i++) fa[i]=i;
		tot=n;
		for(int i=1;i<=m;i++)
		{
			int fu=find(ee[i].u),fv=find(ee[i].v);
			if(fu==fv) continue;
			++tot;
			fa[tot]=fa[fu]=fa[fv]=tot;
			add(tot,fu),add(fu,tot);
			add(tot,fv),add(fv,tot);
			val[tot]=ee[i].a;
			if(tot-n==n-1) break;
		}
    }

    void dfs(int u,int ff)
    {
		dep[u]=dep[ff]+1;
		f[u][0]=ff;
		for(int i=1;i<=19;i++) 
			f[u][i]=f[f[u][i-1]][i-1];
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==ff) continue;
			dfs(v,u);
			dis[u]=min(dis[u],dis[v]);
		}
    }

    int query(int u,int level)
    {
		for(int i=19;i>=0;i--)
			if(dep[u]-(1<<i)>0 && val[f[u][i]]>level) 
				u=f[u][i];
		return dis[u];
    }

    void init()
    {
		ccnt=cnt=0;
		memset(ee,0,sizeof(ee));
		memset(Head,0,sizeof(Head));
		memset(dis,inf,sizeof(dis));
		memset(head,0,sizeof(head));
		memset(f,0,sizeof(f));
		memset(vis,0,sizeof(vis));
    }

    void work()
    {
    	T=read();
		while(T--)
		{
			init();
			n=read(),m=read();
			for(int i=1;i<=m;i++)
			{
				int u=read(),v=read(),l=read(),a=read();
				ee[i]=(k_edge){u,v,l,a};
				insert(u,v,l);
			}
			dijkstra();
			kruskal();
			dfs(tot,0);
			int q=read(),k=read(),s=read(),lastans=0;
			while(q--)
			{
				int v=read(),p=read();
				v=(k*lastans+v-1)%n+1;
				p=(k*lastans+p)%(s+1);
				printf("%d\n",lastans=query(v,p));
			}
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
