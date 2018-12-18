#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000*1000+10;
int n,m,cnt,s,t,Head[MAXN],dep[MAXN];

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
}E[MAXN*6];

void add(int u,int v,int w)
{
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt++;
}

void insert(int u,int v,int w)
{
    add(u,v,w),add(v,u,w);
}

bool bfs()
{
    queue<int> q; 
    memset(dep,-1,sizeof(dep));
    dep[s]=0;
    q.push(s);
    while(!q.empty())
    {
	int u=q.front();q.pop();
	for(int i=Head[u];~i;i=E[i].next)
	{
	    int v=E[i].to;
	    if(dep[v]==-1&&E[i].w)
		dep[v]=dep[u]+1,q.push(v);
	}
    }
    return dep[t]!=-1;
}

int dfs(int u,int mn)
{
    if(u==t) return mn;
    int v,w,used=0;
    for(int i=Head[u];~i;i=E[i].next)
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

int Dinic()
{
    int ans=0;
    while(bfs()) ans+=dfs(s,0x3f3f3f3f);
    return ans;
}

inline int num(int x,int y)
{
    return (x-1)*m+y;
}

int main()
{
    memset(Head,-1,sizeof(Head));
    n=read(),m=read();
    int w;
    s=1,t=num(n,m);
    for(int i=1;i<=n;i++)
	for(int j=1;j<m;j++)
	    w=read(),insert(num(i,j),num(i,j+1),w);
    for(int i=1;i<n;i++)
	for(int j=1;j<=m;j++)
	    w=read(),insert(num(i,j),num(i+1,j),w);
    for(int i=1;i<n;i++)
	for(int j=1;j<m;j++)
	    w=read(),insert(num(i,j),num(i+1,j+1),w);
    printf("%d",Dinic());
    return 0;
}
