#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+5;
	const int inf=0x3f3f3f3f;

	int n,m,rot,Size,top[N],son[N],pre[N],val[N],size[N],mxsize[N],vis[N],Head[N],dep[N],id[N][2],fa[N];

	inline char gc(void) 
	{
		static char buf[1000000],*p1=buf,*p2=buf;
		if(p1==p2)
		{
		    p2=(p1=buf)+fread(buf,1,1000000,stdin);
		    if(p1==p2) return EOF;
		}
		return *p1++;
	}
	inline int read() 
	{
		int x=0;static char c;bool f=false;
		for(;!isdigit(c);c=gc()) if (c=='-') f=true;
		for(;isdigit(c);x=x*10+c-'0',c=gc()); 
		return f?-x:x;
	}
	inline void write(int x) 
	{
		if(!x) return (void)puts("0");
		if(x<0) putchar('-'),x=-x;
		static short s[12],t;
		while(x) s[++t]=x%10,x/=10;
		while(t) putchar('0'+s[t--]);
		putchar('\n');
	}
	struct edge
	{
		int to,next;
	}E[N<<1];

	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void dfs(int u)
	{
		size[u]=1;
		int hs=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==pre[u]) continue; 
			pre[v]=u;
			dep[v]=dep[u]+1;
			dfs(v);
			size[u]+=size[v];
			if(size[v]>size[hs]) hs=v;
		}
		son[u]=hs;
	}

	void dfs(int u,int ance)
	{
		top[u]=ance;
		if(son[u]) dfs(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==pre[u]||v==son[u]) continue;
			dfs(v,v);			
		}
	}
	
	inline int LCA(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=pre[top[u]];			
		}
		return dep[u]<dep[v]?u:v;
	}

	inline int distance(int u,int v)
	{
		return dep[u]+dep[v]-dep[LCA(u,v)]*2;
	}

	namespace Tree
	{
		const int M=1e7+5;

		int cnt,sum[M],ls[M],rs[M];

		void insert(int &root,int l,int r,int pos,int val)
		{
			if(!root) root=++cnt;
			sum[root]+=val;
			if(l==r) return;
			int mid=(l+r)>>1;
			if(pos<=mid) insert(ls[root],l,mid,pos,val);
			else insert(rs[root],mid+1,r,pos,val);
		}

		int query(int root,int l,int r,int s,int e)
		{
			if(!root) return 0;
			if(s<=l&&r<=e) return sum[root];
			int mid=(l+r)>>1,ans=0;
			if(s<=mid) ans+=query(ls[root],l,mid,s,e);
			if(e>mid) ans+=query(rs[root],mid+1,r,s,e);
			return ans;
		}
	}

	void get_root(int u,int f)
	{
		size[u]=1,mxsize[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f||vis[v]) continue;
			get_root(v,u);
			size[u]+=size[v];
			mxsize[u]=max(mxsize[u],size[v]);
		}
		mxsize[u]=max(mxsize[u],Size-size[u]);
		if(mxsize[u]<mxsize[rot]) rot=u;
	}

	void search(int root,int type,int dis,int u,int f)
	{
		Tree::insert(id[root][type],0,n,dis,val[u]);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f||vis[v]) continue;
			search(root,type,dis+1,v,u);
		}
	}

	void solve(int u)
	{
		vis[u]=1;
		search(u,0,0,u,0);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			if(mxsize[u]==mxsize[v])
				size[v]=(dep[u]<dep[v]?size[v]:size[v]-size[u]);
			rot=0,Size=size[v];
			get_root(v,0);
			fa[rot]=u;
			search(rot,1,1,v,u);
			solve(rot);
		}
	}
	
	void init()
	{
		dfs(1);
		dfs(1,1);
		Size=n,mxsize[0]=inf;
		get_root(1,0);
		solve(rot);
	}

	int query(int x,int k)
	{
		int ans=Tree::query(id[x][0],0,n,0,k);
		for(int i=x;i;i=fa[i])
		{
			int dis=distance(x,fa[i]);
			ans+=Tree::query(id[fa[i]][0],0,n,0,k-dis);
			ans-=Tree::query(id[i][1],0,n,0,k-dis);
		}
		return ans;
	}

	void modify(int x,int k)
	{
		int res=k-val[x];
		val[x]=k;
		Tree::insert(id[x][0],0,n,0,res);
		for(int i=x;i;i=fa[i])
		{
			int dis=distance(x,fa[i]);
			Tree::insert(id[fa[i]][0],0,n,dis,res);
			Tree::insert(id[i][1],0,n,dis,res);
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) val[i]=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		init();	
		int ans=0;
		while(m--)
		{
			int opt=read(),x=read(),y=read();
			x^=ans,y^=ans;
			if(opt==0) write(ans=query(x,y));
			else modify(x,y);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
