/*
   关于求混合图的欧拉回路，正解应该是网络流
   但是太菜的TYC不知道，直接用的dfs跑欧拉回路
   然后GG，留下代码作证……
   但是很幸运的只WA了6个点，86pts……
*/
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1010;

	int n,m,cnt,flag,Head[N];
	bool mark[N<<2],vis[N];

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
	}E[4010];

	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	inline int another(int x) {return (x&1)?x+1:x-1;}

	void dfs(int u,int mid)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			if(mark[i]||E[i].w>mid) continue;
			int v=E[i].to;
			mark[i]=mark[another(i)]=true;
			dfs(v,mid);
		}
	}

	bool check(int mid)
	{
		memset(mark,false,sizeof(bool[cnt+2]));
		static int deg[N];
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v;
			if(e[i].a<=mid) deg[u]--,deg[v]++;
			else if(e[i].b<=mid) deg[u]++,deg[v]--;
			else return false;
		}
		for(int i=1;i<=n;i++)
			if(deg[i]&1) return false;
		dfs(1,mid);
		for(int i=1;i<=cnt;i+=2)
			if(!mark[i]) return false;
		return true;
	}

	void work()
	{
		n=read(),m=read();
		static int deg[N];
		int l=0x3f3f3f3f,r=0,ans,mid;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),a=read(),b=read();
			deg[u]++,deg[v]++;
			add(u,v,a),add(v,u,b);
			l=min(l,min(a,b));
			r=max(r,max(a,b));
		}
		for(int i=1;i<=n;i++)
			if(deg[i]&1) {puts("NIE");return;}
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	freopen("2095.in","r",stdin);
	freopen("2095.out","w",stdout);
	TYC::work();
	return 0;
}
