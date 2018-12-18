#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int MAXN=410;
int n,m,cnt=1,S,T,Head[MAXN],G[210][210],dep[MAXN],cur[MAXN],q[MAXN];

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

struct edge
{
	int to,next,w;
}E[50010];

void add(int u,int v,int w)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
}

void insert(int u,int v,int w)
{
	add(u,v,w),add(v,u,0);	
} 

void flyod()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]|=(G[i][k]&G[k][j]);
}

void build()
{
	for(int i=1;i<=n;i++)
		insert(S,i,1),insert(i+n,T,1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j]) insert(i,j+n,inf);
}

bool bfs()
{
	for(int i=S;i<=T;i++) dep[i]=-1;
	for(int i=S;i<=T;i++) cur[i]=Head[i];
	dep[S]=0;
	int h=0,t=0;
	q[++t]=S;
	while(h<t)
	{
		int u=q[++h];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(dep[v]==-1&&E[i].w>0) 
				dep[v]=dep[u]+1,q[++t]=v;
		}
	}
	return dep[T]!=-1;
}

int dfs(int u,int mn)
{
	if(u==T) return mn;
	int v,w,used=0;
	for(int &i=cur[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(dep[v]==dep[u]+1&&E[i].w>0)
		{
			w=dfs(v,min(mn-used,E[i].w));
			used+=w;
			E[i].w-=w,E[i^1].w+=w;
			if(used==mn) return used;
		}
	}
	if(!used) dep[u]=-1;
	return used;
}

void Dinic()
{
	int ans=0;
	while(bfs()) ans+=dfs(S,inf);
	printf("%d",n-ans);
}

int main()
{
	n=read(),m=read();
	S=0,T=2*n+1;
	int u,v;
	for(int i=1;i<=m;i++)
		u=read(),v=read(),G[u][v]=1;
	flyod();
	build();
	Dinic();
	return 0;
} 
