#include<bits/stdc++.h>
using namespace std;
const int MAXN=110;
int m,n,cnt,Head[MAXN],fa[MAXN*2],to[MAXN],ans;
bool vis[MAXN*2];

struct edge
{
	int to,next;
}E[MAXN*MAXN];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

bool Path(int u)
{
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
	v=E[i].to;
	if(vis[v]) continue;
	vis[v]=true;
	if(!fa[v]||Path(fa[v]))
	{
		fa[v]=u;
		to[u]=v;
		return true;
	}
	}
	return false;
}

void Hungary()
{
	for(int i=1;i<=m;i++)
	{
	memset(vis,false,sizeof(vis));
	if(Path(i)) ans++;
	}
}

int main()
{
	scanf("%d%d",&m,&n);
	int u,v;
	while(scanf("%d%d",&u,&v))
	{
	if(u==-1&&v==-1) break;
	add(u,v+m);
	}
	Hungary();
	if(!ans) {printf("No Solution!");return 0;}
	if(ans!=38) printf("%d\n",ans);
	else printf("38\n");
	for(int i=1;i<=m;i++)
	if(to[i]) printf("%d %d\n",i,to[i]-m);
	return 0;
}
