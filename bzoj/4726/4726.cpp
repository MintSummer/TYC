#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const double eps=1e-8;
	const int N=500010;
	int n,k,tot,size[N];
	double f[N];
	vector<int> G[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void dfs(int u,int fa)
	{
		size[u]=1;
		int sz=G[u].size();
		if(!sz) {f[u]=1.0;return;}
		for(int i=0;i<sz;i++)
		{
			int v=G[u][i];
			if(v==fa) continue;
			dfs(v,u);
			size[u]+=size[v];
		}
		for(int i=0;i<sz;i++)
		{
			int v=G[u][i];
			f[u]=max(f[u],min(f[v],(double)size[v]/(size[u]-1)));
		}
	}

	void work()
	{
		n=read(),k=read();
		for(int i=2;i<=n;i++) 
			G[read()].push_back(i);
		dfs(1,0);
		double ans=0.0;
		for(int i=1;i<=n;i++)
			if(size[i]>k) ans=max(ans,f[i]);
		printf("%.10f",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
