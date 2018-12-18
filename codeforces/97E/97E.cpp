#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=1e5+10;
	
	int n,m,Head[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
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

	struct edge
	{
		int to,next,belong;
	}E[N<<1];

	inline void add(const int u,const int v)
	{
		static int cnt=1;
		E[++cnt]=(edge){v,Head[u],0};
		Head[u]=cnt;
	}

	int tot,tim,StackTop,low[N],dfn[N],sta[N<<1],mark[N],col[N],val[N];
	vector<int> Edge[N];

	bool bfs(const int s,const int id)
	{
		memset(col,-1,sizeof(col));
		queue<int> q;
		q.push(s);
		col[s]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
				if(E[i].belong==id)
				{
					int v=E[i].to;
					if(col[v]!=-1)
					{
						if(col[v]==col[u]) return true;
					}
					else col[v]=col[u]^1,q.push(v);
				}
		}
		return false;
	}

	void Tarjan(const int u,const int pre)
	{
		dfn[u]=low[u]=++tim;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if((i^1)==pre) continue;
			sta[++StackTop]=i;
			if(dfn[v]) low[u]=min(low[u],dfn[v]);
			else
			{
				Tarjan(v,i);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u])
				{
					tot++;
					int e;
					do
					{
						e=sta[StackTop--];
						Edge[tot].push_back(e);
						E[e].belong=E[e^1].belong=tot;
					}
					while(e!=i&&(e^1)!=i);
					mark[tot]=bfs(u,tot);
				}
			}
		}
	}

	int vis[N],fa[N],dep[N],size[N],son[N],top[N],Emark[N<<1],f[N],w[N],clo[N],visit[N];

	int find(int x)
	{
		return f[x]==x?x:f[x]=find(f[x]);
	}

	void dfs(const int u)
	{
		vis[u]=size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			fa[v]=u;
			Emark[i]=1;
			dep[v]=dep[u]+1;
			f[find(v)]=find(u);
			val[v]=mark[E[i].belong];
			dfs(v);
			size[u]+=size[v];
			if(size[v]>size[son[u]]) son[u]=v;
		}
	}

	void dfs(const int u,const int ance)
	{
		static int dfntim=0;
		clo[u]=++dfntim;
		w[dfntim]=val[u];
		top[u]=ance;
		visit[u]=1;
		if(son[u]&&!visit[son[u]]) dfs(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
			if(Emark[i])
			{
				int v=E[i].to;
				if(visit[v]||v==fa[u]||v==son[u]) continue;
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

	namespace Tree
	{
		bool value[N<<1];
		
		#define ls root<<1
		#define rs root<<1|1

		void build(const int root,const int l,const int r)
		{
			if(l==r) {value[root]=w[l];return;}
			int mid=(l+r)>>1;
			build(ls,l,mid),build(rs,mid+1,r);
			value[root]=value[ls]|value[rs];
		}

		bool query(const int root,const int l,const int r,const int s,const int e)
		{
			if(s<=l&&r<=e) return value[root];
			int mid=(l+r)>>1;
			if(s<=mid) {if(query(ls,l,mid,s,e)) return true;}
			if(e>mid) {if(query(rs,mid+1,r,s,e)) return true;}
			return false;
		}
	}

	inline bool question(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			int t=top[u];
			if(fa[t]==v) return Tree::query(1,1,n,clo[t],clo[top[u]]);
			else if(Tree::query(1,1,n,clo[t],clo[u])) return true;
			u=fa[top[u]];
		}
		if(u==v) return false;
		if(dep[u]>dep[v]) swap(u,v);
		return Tree::query(1,1,n,clo[u]+1,clo[v]);
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		for(int i=1;i<=n;i++) f[i]=i;
		for(int i=1;i<=n;i++)
			if(!vis[i]) 
			{
				Tarjan(i,0);
				dfs(i);
				dfs(i,i);
			}
		Tree::build(1,1,n);
		int q=read();
		while(q--)
		{
			int u=read(),v=read();
			if(find(u)==find(v)&&(((dep[u]+dep[v])&1)||question(u,v))) puts("Yes");
			else puts("No");
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
