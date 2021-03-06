#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010*2;
int n,m,cnt=1,s,t=520;
int Head[MAXN],dep[MAXN],cur[MAXN];
int q[MAXN];

struct edge
{
    int to,next,w;
}E[MAXN*5];

void add(int u,int v,int w)
{
    E[++cnt].to=v,E[cnt].next=Head[u],E[cnt].w=w,Head[u]=cnt;
	E[++cnt].to=u,E[cnt].next=Head[v],E[cnt].w=0,Head[v]=cnt;
}

bool bfs()
{
    int u,v,h=0,tt=0;
	memcpy(cur,Head,sizeof(cur));
    memset(dep,-1,sizeof(dep));
    dep[s]=0,q[++tt]=s;
    while(h<tt)
      {
      	u=q[++h];
      	for(int i=Head[u];i;i=E[i].next)
      	  {
      	  	v=E[i].to;
      	  	if(dep[v]==-1&&E[i].w>0) 
      	  	  dep[v]=dep[u]+1,q[++tt]=v;
      	  }
      }
	return dep[t]!=-1;
}

int dfs(int u,int mn)
{
    if(u==t) return mn;
    int used=0,v,w=0;
    for(int &i=cur[u];i;i=E[i].next)
      {
      	v=E[i].to;
      	if(dep[v]==dep[u]+1&&E[i].w>0)
      	  {
      	  	w=dfs(v,min(E[i].w,mn));
            used+=w;
            E[i].w-=w,E[i^1].w+=w;
            if(used==mn) break;
      	  }
      }
    if(!used) dep[u]=-1;
    return used;
}

int main()
{
	scanf("%d%d",&n,&m);	
	int a,b;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(a) add(s,i,1);
		else add(i,t,1);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b,1);
		add(b,a,1);
	}
	int ans=0;
	while(bfs()) ans+=dfs(s,0x3f3f3f3f);
	printf("%d",ans);
	return 0;
}
