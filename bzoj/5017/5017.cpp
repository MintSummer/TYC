#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=500010;
	const int M=N<<2;
	const ll p=1e9+7;
	int n,tot,Head[M],id[N],vis[M],deg[M],sum[M];
	int scc,top,tim,dfn[M],low[M],st[M],in[M],belong[M],L[M],R[M];
	ll x[N],r[N];
	vector<int> node[M],G[M];
	
	struct Node
	{
		int l,r;
	}interval[M];
	
	struct edge
	{
		int to,next;
	}E[N*30];
	
	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}
		
	#define ls root<<1
	#define rs root<<1|1
	
	void build(int root,int l,int r)
	{
		tot=max(tot,root);
		L[root]=l,R[root]=r;
		if(l==r) {id[l]=root;sum[root]=1;return;}
		int mid=(l+r)>>1;
		add(root,ls),add(root,rs);
		build(ls,l,mid),build(rs,mid+1,r);
	}
	
	void query(int root,int l,int r,int s,int e,int now)
	{
		if(s<=l&&r<=e) {add(now,root);return;}
		int mid=(l+r)>>1;
		if(s<=mid) query(ls,l,mid,s,e,now);
		if(e>mid) query(rs,mid+1,r,s,e,now);
	}
	
	#undef ls
	#undef rs
	
	void Tarjan(int u)
	{
		dfn[u]=low[u]=++tim;
		in[u]=1;
		st[++top]=u;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!dfn[v])
				Tarjan(v),low[u]=min(low[u],low[v]);
			else 
				if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			int x;
			scc++;
			do
			{
				x=st[top--];
				in[x]=0;
				belong[x]=scc;
				node[scc].push_back(x);
				interval[scc].l=min(interval[scc].l,L[x]);
				interval[scc].r=max(interval[scc].r,R[x]);
			}
			while(x!=u);
		}
	}
	
	inline void rebuild()
	{	
		for(int u=1;u<=scc;u++)
			for(int i=0;i<node[u].size();i++)
			{
				int a=node[u][i];
				for(int j=Head[a];j;j=E[j].next)
				{
					int v=belong[E[j].to];
					if(u!=v&&vis[v]!=u)
					{
						G[v].push_back(u);
						deg[u]++;
						vis[v]=u;
					} 
				}
			}
	}
	
	inline void topsort()
	{
		static queue<int> q;
		for(int i=1;i<=n;i++) 
			if(!deg[i]) q.push(i);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<G[u].size();i++)
			{
				int v=G[u][i];
				interval[v].l=min(interval[u].l,interval[v].l);
				interval[v].r=max(interval[u].r,interval[v].r);
				deg[v]--;
				if(!deg[v]) q.push(v);
			}
		}
	}
	
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld%lld",&x[i],&r[i]);
		build(1,1,n);
		for(int i=1;i<=n;i++)
		{
			int nl=lower_bound(x+1,x+1+n,x[i]-r[i])-x;
			int nr=upper_bound(x+1,x+1+n,x[i]+r[i])-x-1;
			query(1,1,n,nl,nr,id[i]);
		}
		for(int i=1;i<=tot;i++) interval[i].l=0x3f3f3f3f;
		for(int i=1;i<=tot;i++)
			if(!dfn[i]) Tarjan(i);
		rebuild();
		topsort();
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			int l=interval[belong[id[i]]].l,r=interval[belong[id[i]]].r;
			ans=(ans+(ll)i*(r-l+1)%p)%p;
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
