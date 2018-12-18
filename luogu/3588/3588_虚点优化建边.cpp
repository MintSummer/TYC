//虚点优化建边->luogu 90pts
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=4e5+10;
	const int inf=1e9;

	int Head[N],arr[N],f[N],deg[N];

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
		putchar(' ');
	}

	struct edge
	{
		int to,next,w;
	}E[N*10];

	inline void add(const int &u,const int &v,const int &w)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		deg[v]++;
	}

	bool toposort(const int &n)
	{
		static int h=1,t=0,q[N];
		for(int i=1;i<=n;i++) f[i]=inf;
		for(int i=1;i<=n;i++)
			if(!deg[i]) q[++t]=i;
		while(h<=t)
		{
			int u=q[h++];
			if(arr[u])
			{
				if(f[u]<arr[u]) return false;
				f[u]=arr[u];
			}
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				f[v]=min(f[v],f[u]-E[i].w);
				if(!(--deg[v])) q[++t]=v;
			}
		}
		return true;
	}
		
	void work()
	{
		int n=read(),s=read(),m=read();
		while(s--) 
		{
			int pos=read();
			arr[pos]=read();
		}
		memset(f,inf,sizeof(f));
		static bool mark[N];
		int node=n;
		while(m--)
		{
			int l=read(),r=read(),k=read();
			memset(mark,false,sizeof(bool[n+1]));
			node++;
			for(int i=1;i<=k;i++) 
			{
				int x=read();
				mark[x]=true;
				add(x,node,1);
			}
			for(int i=l;i<=r;i++)
				if(!mark[i]) add(node,i,0);
		}
		if(!toposort(node)) puts("NIE");
		else
		{
			puts("TAK");
			for(int i=1;i<=n;i++) write(f[i]);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
