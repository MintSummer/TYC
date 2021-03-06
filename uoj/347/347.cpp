//可怜的28分LCA
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
const int P=20;
typedef long long LL;
int n,cnt[4],Head[4][MAXN],fa[4][MAXN][25],dep[4][MAXN];
LL len[4][MAXN][25];
bool vis[4][MAXN];

struct edge
{
	int to,next;
	LL w;
}E[4][MAXN*2];

void add(int i,int u,int v,LL w)
{
	cnt[i]++;
	E[i][cnt[i]].to=v;
	E[i][cnt[i]].next=Head[i][u];
	E[i][cnt[i]].w=w;
	Head[i][u]=cnt[i];
}

void dfs(int tim,int u,int f)
{
	vis[tim][u]=true;
	int v;
	for(int i=Head[tim][u];i;i=E[tim][i].next)
	{
		v=E[tim][i].to;
		if(vis[tim][v]||v==f) continue;
		fa[tim][v][0]=u;
		dep[tim][v]=dep[tim][u]+1;
		len[tim][v][0]=E[tim][i].w;
		dfs(tim,v,u);
	}
}

void beizeng(int tim)
{
	for(int i=1;i<=P;i++)
		for(int j=1;j<=n;j++)
		{
			len[tim][j][i]=len[tim][j][i-1]+len[tim][fa[tim][j][i-1]][i-1];
			fa[tim][j][i]=fa[tim][fa[tim][j][i-1]][i-1];
		}
}

LL lca(int tim,int u,int v)
{
	if(dep[tim][u]<dep[tim][v]) swap(u,v);
	int d=dep[tim][u]-dep[tim][v],t=0;
	LL ans=0; 
	while(d)
	{
		if(d&1) 
		{
			ans+=len[tim][u][t];
			u=fa[tim][u][t];
		}
		t++;
		d>>=1;
	}
	if(u==v) return ans;
	for(int i=P;i>=0;i--)
	{
		if(fa[tim][u][i]!=fa[tim][v][i])
		{
			ans+=len[tim][u][i]+len[tim][v][i];
			u=fa[tim][u][i],v=fa[tim][v][i];
		}
	}
	return ans+len[tim][u][0]+len[tim][v][0];
}

void another_solve()
{
	
}

int main()
{
	scanf("%d",&n);
	int u,v;
	LL w;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<n;j++)
		{
			scanf("%d%d%lld",&u,&v,&w);
			add(i,u,v,w),add(i,v,u,w);
		}
	}
	if(n>3000) {another_solve();return 0;}
	for(int i=1;i<=3;i++)
	{
		dfs(i,1,0);
		beizeng(i);
	}
	LL ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			ans=max(ans,lca(1,i,j)+lca(2,i,j)+lca(3,i,j));
		}
	printf("%lld",ans);
	return 0;
}
