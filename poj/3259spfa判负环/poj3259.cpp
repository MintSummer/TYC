#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100010;
int F,n,m,w;
int head[MAXN],cnt=0,vis[MAXN],c[MAXN],f[MAXN];
int h,t;
queue<int> q;
struct edge
{
	int to,next,tim;
}E[MAXN];

void add(int u,int v,int t)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=head[u];
	E[cnt].tim=t;
	head[u]=cnt;
}

void init()
{
	while(!q.empty()) q.pop();
	memset(E,0,sizeof(E));
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	memset(c,0,sizeof(c));
	for(int i=1;i<=MAXN;i++) f[i]=99999999;
}

bool spfa(int st)
{
	vis[st]=1;
	f[st]=0;
	c[st]++;
	q.push(st);
	while(!q.empty())
	  {
	  	h=q.front();
	  	q.pop();
	  	vis[h]=0;
	  	for(int i=head[h];i;i=E[i].next)
	  	  {
	  	  	t=E[i].to;
	  	  	if(f[t]>f[h]+E[i].tim)
	  	  	  {
	  	  	  	f[t]=f[h]+E[i].tim;
	  	  	  	if(vis[t]==0)
	  	  	  	  {
	  	  	  	  	q.push(t);
	  	  	  	  	vis[t]=1;
	  	  	  	  	c[t]++;
	  	  	  	  }
	  	  	  	if(c[t]>n) return true;
	  	  	  }
	  	  }
	  }
	return false;
}

int main()
{
	int s,e,ti;
	scanf("%d",&F);
	while(F)
	{
	  F--;
	  init();
	  scanf("%d%d%d",&n,&m,&w);
	  for(int i=1;i<=m;i++)
	    {
	      scanf("%d%d%d",&s,&e,&ti);
	      add(s,e,ti);
	      add(e,s,ti);
	    }
	  for(int i=1;i<=w;i++)
	    {
	       scanf("%d%d%d",&s,&e,&ti);
	       add(s,e,-ti);
	    }
	  if(spfa(1)) printf("YES\n");
	  else printf("NO\n");
	}
    return 0;
}