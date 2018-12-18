//双倍经验： 洛谷1197 星球大战 
//蛋酥，说实话，这道题数据太水了，这么做在星球大战是过不去的
//详见bzoj4579 
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m,cnt=0,Head[MAXN];
int tim[MAXN],vis[MAXN],fa[MAXN];
int ans[MAXN];

struct edge
{
	int to,next;
}E[MAXN*2];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

int find(int a)
{
	return a==fa[a]?a:fa[a]=find(fa[a]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	int u,v;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&tim[i]);
	int fu,fv,before;
	for(int j=n;j>=1;j--)
	{
		u=tim[j];
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			fu=find(u),fv=find(v);
			if(vis[v]&&fu!=fv) fa[fv]=fu; 
		}
		ans[j]=1,before=-1;
		for(int i=1;i<=n;i++) 
		{	
			if(!vis[i]) continue;
			if(before==-1) {before=i;continue;}
			fu=find(i),fv=find(before);
			if(fu!=fv) {ans[j]=0;break;}
			before=i;
		}
	}
	for(int i=1;i<=n;i++)
		if(ans[i]) printf("YES\n");
		else printf("NO\n");
	return 0;
}
