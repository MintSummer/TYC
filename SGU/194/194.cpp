#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=210;
int n,m,cnt=1,s,e;
int Head[MAXN],du[MAXN],down[MAXN*MAXN],dep[MAXN],cur[MAXN],q[MAXN*2];

struct edge
{
    int to,next,w;
}E[210*210];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].w=w;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

bool bfs()
{
    memset(dep,-1,sizeof(dep));
    memcpy(cur,Head,sizeof(cur));
    int h=0,t=0;
    dep[s]=0,q[++t]=s;
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
    return dep[e]!=-1;
}

int dfs(int u,int mn)
{
    if(u==e) return mn;
    int v,w,used=0;
    for(int &i=cur[u];i;i=E[i].next)
    {
	v=E[i].to;
	if(dep[v]==dep[u]+1&&E[i].w>0)
	{
	    w=dfs(v,min(mn-used,E[i].w));
	    used+=w;
	    E[i].w-=w,E[i^1].w+=w;
	    if(used==mn) break;
	}
    }
    if(!used) dep[u]=-1;
    return used;
}

int Dinic()
{
    int ans=0;
    while(bfs()) 
	ans+=dfs(s,0x3f3f3f3f);
    return ans;
}

int main()
{
    scanf("%d%d",&n,&m);
    int u,v,up,dow;
    for(int i=1;i<=m;i++)
    {
	scanf("%d%d%d%d",&u,&v,&dow,&up);
	add(u,v,up-dow),add(v,u,0);
	du[u]-=dow,du[v]+=dow;
	down[i]=dow;
    }

    s=0,e=n+1;
    int sum=0,ans;
    for(int i=1;i<=n;i++)
    {
	if(du[i]>0) add(s,i,du[i]),add(i,s,0),sum+=du[i];
	else add(i,e,-du[i]),add(e,i,0);
    }
    ans=Dinic();

    if(ans!=sum) {printf("NO");return 0;}
    printf("YES\n");
    for(int i=1;i<=m;i++)
	printf("%d\n",E[i*2+1].w+down[i]);
    return 0;
}
