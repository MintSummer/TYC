#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=5e5+5;

	int n,m,Color,q,top,from[N],to[N],color[N];
	pa query[N];
	queue<pa> modify[N];
	vector<pa> tree[N*4];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct Union
	{
		int col,u,v,last;
	}sta[N*4];

	struct UnionFindSet
	{
		int fa[N];
		char dis[N],dep[N];

		void init()
		{
			for(int i=1;i<=n;i++) fa[i]=i;
			memset(dis,0,sizeof(int[n+3]));
			memset(dep,0,sizeof(int[n+3]));
		}

		inline int find(int x,int &k)
		{
			while(fa[x]!=x)
				k^=dis[x],x=fa[x];
			return x;
		}

		void connect(int u,int v,int col)
		{
			int k=0,fu=find(u,k),fv=find(v,k);
			if(fu==fv) return;
			if(dep[fu]>dep[fv]) swap(fu,fv);
			sta[++top]=(Union){col,fu,fv,dep[fu]};
			fa[fu]=fv,dis[fu]=(k^1);
			if(dep[fu]==dep[fv]) dep[fv]++;
		}

		void remove(Union &now)
		{
			int u=now.u,v=now.v;
			fa[u]=u,dis[u]=0;
			dep[v]=now.last;
		}
	}UFS[50];

	void insert(int root,int l,int r,int s,int e,pa newnode)
	{
		if(s<=l&&r<=e) 
		{
			tree[root].push_back(newnode);
			return;
		}
		int mid=(l+r)>>1;
		if(s<=mid) insert(root<<1,l,mid,s,e,newnode);
		if(e>mid) insert(root<<1|1,mid+1,r,s,e,newnode);
	}

	void solve(int root,int l,int r)
	{
		int in=top,mid=(l+r)>>1;
		for(int i=0,sz=tree[root].size();i<sz;i++)
		{
			pa now=tree[root][i];
			int col=now.first,u=from[now.second],v=to[now.second];
			if(~col) UFS[col].connect(u,v,col);
		}
		if(l==r)
		{
			int fir=query[l].first,sec=query[l].second;
			int u=from[sec],v=to[query[r].second];
			UnionFindSet &now=UFS[fir];
			int k=0,fu=now.find(u,k),fv=now.find(v,k);
			if(fu!=fv||k)
				puts("YES"),color[sec]=fir;
			else 
				puts("NO");
			modify[sec].pop();
			if(l<q) 
			{
				pa newnode=pa(color[sec],sec);
				if(l+1<=modify[sec].front().second-1)
					insert(1,1,q,l+1,modify[sec].front().second-1,newnode);
			}
		}
		else solve(root<<1,l,mid),solve(root<<1|1,mid+1,r);
		while(top>in)
			UFS[sta[top].col].remove(sta[top]),top--;
	}

	void work()
	{
		n=read(),m=read(),Color=read(),q=read();
		for(int i=1;i<=m;i++)
			from[i]=read(),to[i]=read();
		for(int i=1;i<=q;i++)
		{
			int e=read(),c=read()-1;
			query[i]=pa(c,e);
			modify[e].push(pa(e,i));
		}
		for(int i=0;i<Color;i++) UFS[i].init();
		for(int i=1;i<=m;i++)
			modify[i].push(pa(0,q+1));
		memset(color,-1,sizeof(int[m+5]));
		solve(1,1,q);
	}	
}

int main()
{
	TYC::work();
	return 0;
}
