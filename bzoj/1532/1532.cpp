#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,m,s,e,cnt,cur[MAXN],Head[MAXN],dep[MAXN];
int q[MAXN];

struct chang
{
	int a,b;
}p[MAXN];

struct edge
{
	int to,next,w;
}E[MAXN*3];

void add(int u,int v,int w)
{
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
	cnt++;
}

void build(int x)
{
	for(int i=s;i<=e;i++) Head[i]=-1;
	cnt=0;
	for(int i=1;i<=m;i++)
		add(s,i,1),add(i,s,0);
	for(int i=1;i<=m;i++)
	{
		add(i,p[i].a+m,1),add(p[i].a+m,i,0);
		add(i,p[i].b+m,1),add(p[i].b+m,i,0);
	}
	for(int i=1;i<=n;i++)
		add(i+m,e,x),add(e,i+m,0);
}

bool bfs()
{
	int h=0,t=0,u,v;
	for(int i=s;i<=e;i++) dep[i]=-1;
	q[++t]=s;
	dep[s]=0;
	while(h<t)
	{
		u=q[++h];
		for(int i=Head[u];i!=-1;i=E[i].next)
		{
			v=E[i].to;
			if(dep[v]==-1&&E[i].w>0)
			{
				dep[v]=dep[u]+1;
				if(v==e) return true;
				q[++t]=v;
			}
		}
	}
	return false;
}

int dfs(int u,int mn)
{
	if(mn==0||u==e) return mn;
	int v,used=0,w;
	for(int &i=cur[u];i!=-1;i=E[i].next)
	{
		v=E[i].to;
		if(dep[v]==dep[u]+1&&E[i].w>0)
		{
			w=dfs(v,min(mn-used,E[i].w));
			used+=w;
			E[i].w-=w,E[i^1].w+=w;
		}
	}
	return used;
}

bool check(int x)
{
	int ans=0;
	while(bfs())
	{
		for(int i=s;i<=e;i++) cur[i]=Head[i];
		ans+=dfs(s,0x3f3f3f3f);
	}
	return ans==m;
}

int main()
{
	scanf("%d%d",&n,&m);
	s=0,e=n+m+1;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&p[i].a,&p[i].b);
	int lt=1,rt=m,mid,ans;
	while(lt<=rt)
	{
		mid=(lt+rt)>>1;
		build(mid);
		if(check(mid)) ans=mid,rt=mid-1;
		else lt=mid+1;
	}
	printf("%d",ans);
	return 0;
}
