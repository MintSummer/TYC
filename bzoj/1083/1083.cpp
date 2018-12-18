#include<bits/stdc++.h>
using namespace std;
int n,m,Head[310],fa[310];

struct edge
{
	int u,v,w;
	bool operator < (const edge &a) const
	{
		return w<a.w;
	}
}E[50010];

inline int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

inline int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline int kruskal()
{
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv)
			fa[fu]=fv,ans=max(ans,E[i].w);
	}
	return ans;
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
		E[i].u=read(),E[i].v=read(),E[i].w=read();
	sort(E+1,E+1+m);
	printf("%d %d",n-1,kruskal());
	return 0;
}
