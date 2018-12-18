#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<ll,int> pa;
	const int N=1e5+10,M=N*8;
	const ll inf=(1LL<<61);
	int n,m,s,tot,ro1,ro2,Head[M];
	ll dis[M];
	pair<int,int> id[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int to,next,w;
	}E[N*40];
	
	inline void add(int u,int v,int w)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}
	
	namespace Tree
	{
		int cnt,ls[M],rs[M];
		
		void build(int &root,int l,int r,int tag)
		{
			if(!root) root=++cnt;
			if(l==r) 
			{
				if(!tag) id[l].first=root;
				else id[l].second=root;
				return;
			}
			int mid=(l+r)>>1;
			build(ls[root],l,mid,tag);
			build(rs[root],mid+1,r,tag);
			if(!tag)
				add(root,ls[root],0),add(root,rs[root],0);
			else 
				add(ls[root],root,0),add(rs[root],root,0);
		}
		
		void query(int root,int l,int r,int s,int e,int from,int val,int tag)
		{
			if(s<=l&&r<=e) 
			{
				if(!tag) add(from,root,val);
				else add(root,from,val);
				return;
			}
			int mid=(l+r)>>1;
			if(s<=mid) query(ls[root],l,mid,s,e,from,val,tag);
			if(e>mid) query(rs[root],mid+1,r,s,e,from,val,tag);
		}
		
		#undef ls
		#undef rs 
	}
	
	void Dijkstra()
	{
		static int vis[M];
		static priority_queue<pa,vector<pa>,greater<pa> > q;
		for(int i=1;i<=Tree::cnt;i++) dis[i]=inf;
		s=id[s].second;
		dis[s]=0;
		q.push(pa(dis[s],s));
		while(!q.empty())
		{
			int u=q.top().second;q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[v]>dis[u]+E[i].w)
				{
					dis[v]=dis[u]+E[i].w;
					if(!vis[v]) q.push(pa(dis[v],v));
				}
			}
		}
	}
	
	void work()
	{
		n=read(),m=read(),s=read();
		Tree::build(ro1,1,n,0);
		Tree::build(ro2,1,n,1);
		int u,v,l,r,w;
		for(int i=1;i<=m;i++)
		{
			int opt=read();
			if(opt==1)
			{
				u=read(),v=read(),w=read();
				add(id[u].second,id[v].first,w);
			}
			else
			{
				u=read(),l=read(),r=read(),w=read();
				if(opt==2) Tree::query(ro1,1,n,l,r,id[u].second,w,0);
				else Tree::query(ro2,1,n,l,r,id[u].first,w,1);
			}
		}
		for(int i=1;i<=n;i++) add(id[i].first,id[i].second,0);
		Dijkstra();
		for(int i=1;i<=n;i++)
		{
			ll ans=min(dis[id[i].first],dis[id[i].second]);
			printf("%lld ",ans==inf?-1:ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
} 
