#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;

	int Head[N];

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
	}E[N<<1];

	inline void add(const int u,const int v,const int w)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}

	}
}

int main()
{
	TYC::work();
	return 0;
}
