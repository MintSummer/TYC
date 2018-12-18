#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int n,fa[MAXN],vis[MAXN],ans;

int find(int a)
{
	return a==fa[a]?a:fa[a]=find(fa[a]);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) fa[i]=i;
	int x;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		fa[find(i)]=find(x);
	}
	for(int i=1;i<=n;i++)
	{
		x=find(i);
		if(!vis[x]) ans++,vis[x]=1;
	}
	printf("%d",ans);
	return 0;
}
