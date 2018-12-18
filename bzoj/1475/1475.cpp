#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
int n,m,cnt,s,t,Head[1010]; 
int dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};
int cur[1010],dep[1010];
ll ans=0;

struct edge
{
	int to,next,w;
}E[1010*1010];

void add(int u,int v,int w)
{
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
	cnt++;
}

bool bfs()
{
	memset(dep,-1,sizeof(dep));
	memcpy(cur,Head,sizeof(cur));
	queue<int> q;
	q.push(s),dep[s]=0;
	int u,v;
	while(!q.empty())
	{
		u=q.front();q.pop();
		for(int i=Head[u];~i;i=E[i].next)
		{
			v=E[i].to;
			if(dep[v]==-1&&E[i].w>0) 
				dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[t]!=-1;
}

int dfs(int u,int mn)
{
	if(u==t||mn==0) return mn;
	int used=0,v,w;
	for(int &i=cur[u];~i;i=E[i].next)
	{
		v=E[i].to;
		if(dep[v]==dep[u]+1&&E[i].w>0)
		{
			w=dfs(v,min(E[i].w,mn-used));
			used+=w;
			E[i].w-=w,E[i^1].w+=w;
			if(used==mn) return mn;
		}
	}
	if(!used) dep[u]=-1;
	return  used;
}

void Dinic()
{
	while(bfs()) ans-=dfs(s,inf);
}

int main()
{
	memset(Head,-1,sizeof(Head));
	scanf("%d",&n);
	m=n;//谁叫这是从洛谷2774复制的代码呢…… 
	s=n*m+1,t=n*m+2;

	int a;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a);
			ans+=a;
			if((i+j)%2==1) 
				add(s,(i-1)*m+j,a),add((i-1)*m+j,s,0);
			else 
				add((i-1)*m+j,t,a),add(t,(i-1)*m+j,0);
		}
	
	int x,y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if((i+j)%2==1)
				for(int k=1;k<=4;k++)
				{
					x=i+dx[k],y=j+dy[k];
					if(x<=0||x>n||y<=0||y>m) continue;
					add((i-1)*m+j,(x-1)*m+y,inf);
					add((x-1)*m+y,(i-1)*m+j,0);
				}
	Dinic();
	printf("%lld",ans);
	return 0;
}
