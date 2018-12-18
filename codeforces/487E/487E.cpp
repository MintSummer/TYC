#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=1e5+10;
	const int M=N<<1;
	const int inf=0x3f3f3f3f;

	int n,m,q,cnt,node,val[M],h[N],Head[M],size[M],son[M],top[M],dfn[M],dep[M],fa[M],w[M];
	priority_queue<int,vector<int>,greater<int> > pq[N],del[N];

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

	struct edge
	{
		int to,next;
	}E[M<<1],e[N<<1];

	inline void add(int *H,edge *ed,const int u,const int v)
	{
		ed[++cnt]=(edge){v,H[u]};
		H[u]=cnt;
		ed[++cnt]=(edge){u,H[v]};
		H[v]=cnt;
	}

	void Tarjan(const int u,const int pre)
	{
		static int tim,top,bel[N],low[N],vistim[N];
		static pa sta[M<<1];
		vistim[u]=low[u]=++tim;
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if((i^1)==pre) continue;
			if(vistim[v]) 
				low[u]=min(low[u],vistim[v]);
			else
			{
				sta[++top]=pa(u,v);
				Tarjan(v,i);
				low[u]=min(low[u],low[v]);
				if(low[v]>=vistim[u])
				{
					node++;
					int x,y;
					do 
					{
						x=sta[top].first,y=sta[top].second;
						if(bel[x]!=node) bel[x]=node,add(Head,E,node,x);
						if(bel[y]!=node) bel[y]=node,add(Head,E,node,y);
						top--;
					}
					while(x!=u&&y!=v);
				}
			}
		}
	}

	void dfs(const int u)
	{
		size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			if(u>n) pq[u-n].push(val[v]);
			fa[v]=u,dep[v]=dep[u]+1;
			dfs(v);
			size[u]+=size[v];
			if(size[v]>size[son[u]]) son[u]=v;
		}
		if(u>n) val[u]=pq[u-n].top();
	}

	void dfs(const int u,const int ance)
	{
		static int tim;
		dfn[u]=++tim;
		w[tim]=val[u];
		top[u]=ance;
		if(son[u]) dfs(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]||v==son[u]) continue;
			dfs(v,v);
		}
	}

	namespace Tree
	{
		int mn[M<<2];

		#define ls root<<1
		#define rs root<<1|1
		
		inline void update(const int root)
		{
			mn[root]=min(mn[ls],mn[rs]);
		}

		void build(const int root,const int l,const int r)
		{
			if(l==r) {mn[root]=w[l];return;}
			int mid=(l+r)>>1;
			build(ls,l,mid),build(rs,mid+1,r);
			update(root);
		}

		void modify(const int root,const int l,const int r,const int pos,const int value)
		{
			if(l==r) {mn[root]=value;return;}
			int mid=(l+r)>>1;
			if(pos<=mid) modify(ls,l,mid,pos,value);
			else modify(rs,mid+1,r,pos,value);
			update(root);
		}

		int query(const int root,const int l,const int r,const int s,const int e)
		{
			if(s<=l&&r<=e) return mn[root];
			int mid=(l+r)>>1,ans=inf;
			if(s<=mid) ans=min(ans,query(ls,l,mid,s,e));
			if(e>mid) ans=min(ans,query(rs,mid+1,r,s,e));
			return ans;
		}
	}

	inline void modify(const int pos,const int value)
	{
		Tree::modify(1,1,node,dfn[pos],value);
		int x=fa[pos]-n;
		if(!(x+n)) return;
		del[x].push(val[pos]);
		while(!del[x].empty()&&del[x].top()==pq[x].top()) 
			pq[x].pop(),del[x].pop();
		pq[x].push(value);
		val[x+n]=pq[x].top();
		Tree::modify(1,1,node,dfn[x+n],val[x+n]);
		val[pos]=value;
	}

	inline int query(int u,int v)
	{
		int ans=inf;
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			ans=min(ans,Tree::query(1,1,node,dfn[top[u]],dfn[u]));
			u=fa[top[u]];
		}
		if(dep[u]>dep[v]) swap(u,v);
		ans=min(ans,Tree::query(1,1,node,dfn[u],dfn[v]));
		if(u>n) ans=min(ans,Tree::query(1,1,node,dfn[fa[u]],dfn[fa[u]]));
		return ans;
	}

	void work()
	{
		node=n=read(),m=read(),q=read();
		for(int i=1;i<=n;i++) val[i]=read();
		cnt=1;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(h,e,u,v);
		}
		cnt=0;
		Tarjan(1,0);
		dfs(1);
		dfs(1,1);
		Tree::build(1,1,node);
		char ch;
		while(q--)
		{
			do ch=getchar(); while(!isalpha(ch));
			if(ch=='A') write(query(read(),read()));
			else 
			{
				int pos=read(),value=read();
				modify(pos,value);
			}
		}
	}
}

int main()
{
	freopen("rand.in","r",stdin);
	TYC::work();
	return 0;
}
