#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	const int inf=0x3f3f3f3f;

	namespace DualGraph
	{
		const int N=1010;

		int n,m,in[N],belong[N],vis[N],pre[N];

		struct edge
		{
			int u,v,w;
		}E[N*N];

		inline void add(const int u,const int v,const int w)
		{
			E[++m]=(edge){u,v,w};
		}
			
		int solve()
		{
		    for(int i=1;i<=n;i++) add(0,i,inf);
			int ans=0,root=0,tot;
			while(1)
			{
				memset(in,inf,sizeof(int[n+5]));
				for(int i=1;i<=m;i++)
				{
					int u=E[i].u,v=E[i].v,w=E[i].w;
					if(u!=v&&in[v]>E[i].w) in[v]=w,pre[v]=u;
				}
				in[root]=0,tot=-1;
				memset(vis,-1,sizeof(int[n+5]));
				memset(belong,-1,sizeof(int[n+5]));
				for(int i=0;i<=n;i++)
				{
					ans+=in[i];
					int now=i;
					while(now!=root&&belong[now]==-1&&vis[now]!=i) 
						vis[now]=i,now=pre[now];
					if(now!=root&&belong[now]==-1)
					{
						belong[now]=++tot;
						for(int x=pre[now];x!=now;x=pre[x]) 
							belong[x]=tot;
					}
				}
				if(tot==-1) break;
				for(int i=0;i<=n;i++)
					if(belong[i]==-1) belong[i]=++tot;
				for(int i=1;i<=m;i++)
				{
					int u=belong[E[i].u],v=belong[E[i].v];
					if(u!=v) E[i].w-=in[E[i].v];
					E[i].u=u,E[i].v=v;
				}
				root=belong[root],n=tot;
			}
			return ans;
		}
	}

	namespace FloorPlan
	{
		const int N=3010;
		const int M=30010;
	
		struct node
		{
			int x,y;
		}pos[N];

		struct Edge
		{
			int u,v,w,type,id;
		};

		typedef pair<double,Edge> pde;
		pde edge[M<<1];

		bool operator < (const pde &a,const pde &b)
		{
			return a.first<b.first;
		}

		int vis[N],polygon[M][2],val[N][2];

		struct TemporaryEdge
		{
			int to,type,id;
		};

		vector<TemporaryEdge> G[N];

		inline void add(const Edge &e)
		{
			G[e.u].push_back((TemporaryEdge){e.v,e.type,e.id});
			val[e.id][e.type]=e.w;
		}

		#define Mod(x,p) (x)==(p)?0:(x)

		int dfs(const int u,const int f)
		{
			if(vis[u]) return ++DualGraph::n;
			for(int i=0,sz=G[u].size();i<sz;i++)
				if(G[u][i].to==f) 
				{
					i=Mod(i+1,sz);
					return polygon[G[u][i].id][G[u][i].type]=dfs(G[u][i].to,u);
				}
			return 0;
		}

		void build(const int n,const int m)
		{
		    for(int i=1;i<=m;i++)
		    {
			    int u=edge[i].second.u,v=edge[i].second.v;
			    edge[i].first=-atan2(pos[u].y-pos[v].y,pos[u].x-pos[v].x);
		    }
			sort(edge+1,edge+1+m);
			for(int i=1;i<=m;i++) add(edge[i].second);
			for(int i=1;i<=n;i++)
			{
				vis[i]=1;
				for(int j=0,sz=G[i].size();j<sz;j++)
				{
					TemporaryEdge &now=G[i][j];
					if(!polygon[now.id][now.type])
						polygon[now.id][now.type]=dfs(now.to,i);
				}
				vis[i]=0;
			}
			for(int i=1,lim=m>>1;i<=lim;i++)
			{
				if(val[i][0]) 
					DualGraph::add(polygon[i][0],polygon[i][1],val[i][0]);
				if(val[i][1])
					DualGraph::add(polygon[i][1],polygon[i][0],val[i][1]);
			}
		}
	}

	void work()
	{
	    using namespace FloorPlan;
	    	
		int n=read(),m=read();
		for(int i=1;i<=n;i++)
			pos[i]=(node){read(),read()};
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			edge[(i<<1)-1].second=(Edge){u,v,read(),0,i};
			edge[i<<1].second=(Edge){v,u,read(),1,i};
		}
		build(n,m<<1);
		printf("%d\n",DualGraph::solve()-inf);
	}
}

int main()
{
	TYC::work();
	return 0;
}
