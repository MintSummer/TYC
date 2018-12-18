#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=20010;
	const int M=50010;
	const int MX=M<<4;
	const int inf=0x3f3f3f3f;

	int n,m,q,id[MX],newval[M];
	ll ans[M];
	bool must[MX],dynamic[MX];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(ll x)
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

	struct Edge
	{
		int u,v,w;
	}edge[M];
	
	struct Modify
	{
		int id,val;
	}modify[M];

	namespace DSU
	{
		int top,fa[N],rank[N];
		struct node
		{
			int u,v,rk,before;
		}sta[N];

		void init()
		{
			for(int i=1;i<=n;i++) 
				fa[i]=i,rank[i]=1;
		}

		int find(int x)
		{
			while(fa[x]!=x) x=fa[x];
			return x;
		}

		void merge(int u,int v)
		{
			if(rank[u]>rank[v]) swap(u,v);
			sta[++top]=(node){u,v,rank[v],fa[u]};
			fa[u]=v;
			if(rank[u]==rank[v]) rank[v]++;
		}

		void restore(const int &goal)
		{
			while(top>goal)
			{
				const node &now=sta[top--];
				fa[now.u]=now.before;
				rank[now.v]=now.rk;
			}
		}
	}
	using namespace DSU;

	bool cmpid(const int &x,const int &y)
	{
		return newval[id[x]]<newval[id[y]];
	}

	inline void get_must(const int &l,const int &r)
	{
		int bottom=top;
		static int list[MX];
		for(int i=l;i<=r;i++) list[i]=i;
		sort(list+l,list+r+1,cmpid);
		for(int i=l;i<=r;i++) 
		{
			int x=list[i];
			int u=edge[id[x]].u,v=edge[id[x]].v,fu=find(u),fv=find(v);
			if(fu!=fv)
			{
				merge(fu,fv);
				if(newval[id[x]]>-inf) must[x]=true;
			}
		}
		restore(bottom);
	}

	void get_dynamic(const int &l,const int &r)
	{
		int bottom=top;
		static int list[MX];
		for(int i=l;i<=r;i++) list[i]=i;
		sort(list+l,list+r+1,cmpid);
		for(int i=l;i<=r;i++)
		{
			int x=list[i];
			int u=edge[id[x]].u,v=edge[id[x]].v,fu=find(u),fv=find(v);
			if(fu!=fv) merge(fu,fv);
			else if(newval[id[x]]<inf) dynamic[x]=true;
		}
		restore(bottom);
	}

	void solve(const int &l,const int &r,const int &el,const int &er,ll now)
	{
		if(l==r) edge[modify[l].id].w=modify[l].val;
		for(int i=el;i<=er;i++) newval[id[i]]=edge[id[i]].w;
		memset(must+el,false,sizeof(bool[er-el+1]));
		memset(dynamic+el,false,sizeof(bool[er-el+1]));
		if(l==r)
		{
			get_must(el,er);
			ans[l]=now;
			for(int i=el;i<=er;i++)
				if(must[i]) ans[l]+=edge[id[i]].w;
			return;
		}
		for(int i=l;i<=r;i++) newval[modify[i].id]=-inf;
		get_must(el,er);
		for(int i=l;i<=r;i++) newval[modify[i].id]=inf;
		get_dynamic(el,er);
		int mid=(l+r)>>1,t=er,bottom=top;
		for(int i=el;i<=er;i++)
			if(must[i]) 
			{
				int u=edge[id[i]].u,v=edge[id[i]].v,fu=find(u),fv=find(v);
				if(fu!=fv) merge(fu,fv),now+=edge[id[i]].w;
			}
			else if(!dynamic[i]) id[++t]=id[i];
		solve(l,mid,er+1,t,now);
		solve(mid+1,r,er+1,t,now);
		restore(bottom);
	}

	void work()
	{
		n=read(),m=read(),q=read();
		for(int i=1;i<=m;i++)
			id[i]=i,edge[i]=(Edge){read(),read(),read()};
		for(int i=1;i<=q;i++)
			modify[i]=(Modify){read(),read()};
		init();
		solve(1,q,1,m,0);
		for(int i=1;i<=q;i++) write(ans[i]);
	}
}


int main()
{
	TYC::work();
	return 0;
}
