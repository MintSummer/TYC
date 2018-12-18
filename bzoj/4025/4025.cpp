#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;
	const int M=200010;

	int n,m,Time,dis[N],fa[N],ans[N],dep[N];
	vector<int> tree[N*4];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int u,v,s,e;
		bool operator < (const edge &a) const
		{
			return s<a.s||(s==a.s&&e<a.e);
		}
	}Edge[M];
	
	struct opt
	{
		int u,v,dep;
	};

	inline int find(int x,int &k)
	{
		while(fa[x]!=x)
			k^=dis[x],x=fa[x];
		return x;
	}

	#define ls root<<1
	#define rs root<<1|1

	void solve(int root,int l,int r)
	{
		queue<opt> q;
		int mid=(l+r)>>1;
		for(int i=0,sz=tree[root].size();i<sz;i++)
		{
			int now=tree[root][i];
			if(Edge[now].s<=l&&Edge[now].e>=r)
			{
				int u=Edge[now].u,v=Edge[now].v,k=0;
				int fu=find(u,k),fv=find(v,k);
				if(u==v||(fu==fv&&k==0))
				{
					for(int j=l;j<=r;j++) ans[j]=1;
					while(!q.empty())
					{
						int u=q.front().u,v=q.front().v;
						fa[u]=u,dis[u]=0;
						dep[v]=q.front().dep;
						q.pop();
					}
					return;
				}
				else if(fu!=fv)
				{
					if(dep[fu]>dep[fv]) swap(fu,fv);
					q.push((opt){fu,fv,dep[fv]});
					fa[fu]=fv,dis[fu]=(k^1);
					dep[fv]=max(dep[fv],dep[fu]+1);
				}
			}
			else 
			{
				if(Edge[now].s<=mid) tree[ls].push_back(now);
				if(Edge[now].e>mid) tree[rs].push_back(now);
			}
		}
		if(l!=r) solve(ls,l,mid),solve(rs,mid+1,r);
		while(!q.empty())
		{
			int u=q.front().u,v=q.front().v;
			fa[u]=u,dis[u]=0;		
			dep[v]=q.front().dep;
			q.pop();
		}
	}

	#undef ls
	#undef rs

	void work()
	{
		n=read(),m=read(),Time=read(); 
		for(int i=1;i<=n;i++) 
			fa[i]=i,dep[i]=1;
		for(int i=1;i<=m;i++)
			Edge[i]=(edge){read(),read(),read()+1,read()};
		sort(Edge+1,Edge+1+m);
		for(int i=1;i<=m;i++)
			tree[1].push_back(i);
		solve(1,1,Time);
		for(int i=1;i<=Time;i++)
			puts(ans[i]?"No":"Yes");
	}
}

int main()
{
	TYC::work();
	return 0;
}
