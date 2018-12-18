#include<bits/stdc++.h>
using namespace std;
const int MAXN=61*10;
const int inf=0x3f3f3f3f;
int n,m,cnt,s,t;
int f[MAXN],pre[MAXN],Head[MAXN];
bool vis[MAXN];
/*
把每个工人拆成N个点。记为A[i,j]表示第i个工人修倒数第j辆车
j表示工人,i表示工人j修倒数第i个,k表示工人j倒数第i个修的是哪辆车
考虑第i个工人，他修第j辆车只对后面要修的车有影响，而前面修过的车已经对当前没有影响了,而这个影响就是后面每个将要修理的车都多等待了time的时间
*/

struct edge
{
    int from,to,next,w,c;
}E[100010];

inline void insert(int u,int v,int w,int c)
{
    E[cnt]=(edge){u,v,Head[u],w,c};
    Head[u]=cnt++;
    E[cnt]=(edge){v,u,Head[v],0,-c};
    Head[v]=cnt++;
}

bool spfa()
{
    queue<int> q;
    memset(vis,false,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    memset(f,inf,sizeof(f));
    f[s]=0,vis[s]=true;
    q.push(s);
    while(!q.empty())
    {
	int u=q.front();q.pop();
	vis[u]=false;
	for(int i=Head[u];~i;i=E[i].next)
	{
	    int v=E[i].to;
    	    if(E[i].w>0&&f[v]>f[u]+E[i].c)
	    {
		f[v]=f[u]+E[i].c;
		pre[v]=i;
		if(!vis[v]) vis[v]=true,q.push(v);
	    }
	}
    }
    return f[t]!=inf;
}

int EK()
{
    int ans=0;
    while(spfa())
    {
	int mn=inf;
	for(int i=pre[t];~i;i=pre[E[i].from])
	    mn=min(mn,E[i].w);
	for(int i=pre[t];~i;i=pre[E[i].from])
	    E[i].w-=mn,E[i^1].w+=mn;
	ans+=f[t]*mn;
    }
    return ans;
}

int main()
{
    memset(Head,-1,sizeof(Head));
    scanf("%d%d",&m,&n);
    int x;
    for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
	    scanf("%d",&x);
	    for(int k=1;k<=n;k++)
		insert(j*n+k,i,1,k*x);
	}
    s=n*m+n+1,t=n*m+n+2;
    for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++)
	    insert(s,i*n+j,1,0);
    for(int i=1;i<=n;i++) insert(i,t,1,0);

    printf("%.2lf",(double)EK()/n);
    return 0;
}
