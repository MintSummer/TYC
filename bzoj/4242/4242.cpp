#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int W=2010;
	const int N=2e5+10;
	const int M=N<<1;
	const int dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};

	int mp[W][W],id[W][W],dis[W*W],belong[W*W];
	int f[M],val[M],dep[M],Head[M],fa[M],top[M],son[M],size[M];
	pa pos[W*W];
	vector<pa> edge[W*W];
	queue<int> q;

	struct Edge
	{
		int to,next;
	}E[M];

	inline void add(const int u,const int v)
	{
		static int cnt=0;
		E[++cnt]=(Edge){v,Head[u]};
		Head[u]=cnt;
	}

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	void bfs(const int h,const int w)
	{
		while(!q.empty())
		{
			int u=q.front();q.pop();
			int x=pos[u].first,y=pos[u].second;
			for(int i=1;i<=4;i++)
			{
				int nx=x+dx[i],ny=y+dy[i];
				if(nx<1||nx>h||ny<1||ny>w||!mp[nx][ny]) continue;
				int v=id[nx][ny];
				if(!belong[v])
				{
					belong[v]=belong[u];
					dis[v]=dis[u]+1;
					q.push(v);
				}
				else edge[dis[u]+dis[v]].push_back(pa(belong[u],belong[v]));
			}
		}
	}

	int find(const int x)
	{
		return x==f[x]?x:f[x]=find(f[x]);
	}

	inline int kruskal(const int h,const int w,const int n)
	{
		for(int i=1;i<=n;i++) f[i]=i;
		int node=n;
		for(int i=0,t=h*w;i<=t;i++)
			for(int j=0,sz=edge[i].size();j<sz;j++)
			{
				int u=edge[i][j].first,v=edge[i][j].second;
				int fu=find(u),fv=find(v);
				if(fu!=fv)
				{
					val[++node]=i;
					f[node]=f[fu]=f[fv]=node;
					add(node,fu),add(node,fv);
				}
			}
		return node;
	}

	void dfs(const int u)
	{
		size[u]=1;
		int hs=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			fa[v]=u;
			dep[v]=dep[u]+1;
			dfs(v);
			size[u]+=size[v];
			if(size[v]>size[hs]) hs=v;
		}
		son[u]=hs;
	}

	void dfs(const int u,const int ance)
	{
		top[u]=ance;
		if(son[u]) dfs(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==son[u]) continue;
			dfs(v,v);
		}
	}

	inline int LCA(int u,int v)
	{
		while(top[u]!=top[v]) 
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}

	void work()
	{
		int h=read(),w=read(),n=read(),m=read(),tot=0;
		char ch;
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)
			{
				do ch=getchar(); while(ch!='.'&&ch!='#');
				mp[i][j]=(ch=='.');
				id[i][j]=++tot;
				pos[tot]=pa(i,j);
			}
		for(int i=1;i<=n;i++)
		{
			int x=read(),y=read();
			belong[id[x][y]]=i;
			q.push(id[x][y]);
		}
		bfs(h,w);
		int node=kruskal(h,w,n);
		static int num,vis[M],root[M];
		for(int i=1;i<=node;i++)
		{
			int f=find(i);
			if(!vis[f]) vis[f]=1,root[++num]=f;
		}
		for(int i=1;i<=num;i++) 
			dfs(root[i]),dfs(root[i],root[i]);
		while(m--)
		{
			int u=read(),v=read();
			if(find(u)!=find(v)) puts("-1");	
			else write(val[LCA(u,v)]);
		}
	}
}

int main()
{
	freopen("4242.in","r",stdin);
	freopen("4242.out","w",stdout);
	TYC::work();
	return 0;
}
