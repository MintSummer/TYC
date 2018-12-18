#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10,inf=0x3f3f3f3f;
	int n,m,tim,Head[N],fa[N],val[N],son[N],size[N],dfn[N],top[N],w[N],dep[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(ll x)
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
		int hs=0;
		size[u]=1;
		dep[u]=dep[fa[u]]+1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			dfs(v);
			size[u]+=size[v];
			if(size[v]>size[hs]) hs=v;
		}
		son[u]=hs;
	}
	
	void dfs(int u,int ance)
	{
		dfn[u]=++tim;
		top[u]=ance;
		w[tim]=val[u];
		if(son[u]) dfs(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==son[u]||v==fa[u]) continue;
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
	
	inline int get_nxt(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			if(fa[top[u]]==v) return top[u];
			u=fa[top[u]];
		}
		if(dep[u]>dep[v]) swap(u,v);
		return son[u];
	}
	
	namespace Tree
	{
		int mn[N*4];
		#define ls root<<1
		#define rs root<<1|1
		
		inline void update(int root)
		{
			mn[root]=min(mn[ls],mn[rs]);
		}
		
		void build(int root,int l,int r)
		{
			if(l==r) {mn[root]=w[l];return;}
			int mid=(l+r)>>1;
			build(ls,l,mid),build(rs,mid+1,r);
			update(root);
		}
		
		void change(int root,int l,int r,int pos,int val)
		{
			if(l==r) {mn[root]=val;return;}
			int mid=(l+r)>>1;
			if(pos<=mid) change(ls,l,mid,pos,val);
			else change(rs,mid+1,r,pos,val);
			update(root);
		}
		
		inline int query(int root,int l,int r,int s,int e)
		{
			if(s<=l&&r<=e) return mn[root];
			int mid=(l+r)>>1,ans=inf;
			if(s<=mid) ans=min(ans,query(ls,l,mid,s,e));
			if(e>mid) ans=min(ans,query(rs,mid+1,r,s,e));
			return ans;
		}
	}
	using Tree::query;
	
	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		{
			fa[i]=read(),val[i]=read();
			add(fa[i],i),add(i,fa[i]);
		}
		dfs(1);
		dfs(1,1);
		Tree::build(1,1,n);
		char ch;
		int root=1,u,v,lca,nxt,ans;
		while(m--)
		{
			do ch=getchar(); while(!isalpha(ch));
			switch(ch)
			{
				case 'V': 
					u=read(),v=read();
					Tree::change(1,1,n,dfn[u],v);
					break;
				case 'E': root=read();break;
				case 'Q':
					u=read(),lca=LCA(root,u);
					if(lca!=u) write(query(1,1,n,dfn[u],dfn[u]+size[u]-1));
					else 
					{
						nxt=get_nxt(u,root);
						ans=inf;
						if(dfn[nxt]>1) 
							ans=min(ans,query(1,1,n,1,dfn[nxt]-1));
						if(dfn[nxt]+size[nxt]-1<n) 
							ans=min(ans,query(1,1,n,dfn[nxt]+size[nxt]-1,n));
						write(ans); 
					}
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
} 
