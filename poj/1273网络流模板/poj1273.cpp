#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int MAXN=210;
int n,m,cnt,Head[MAXN],cur[MAXN];
//n为点，m为边数 
int dep[MAXN];
queue<int> q;

struct edge
{
	int to,next,w;
}E[MAXN*2];

void init()
{
    cnt=0;
	memset(Head,-1,sizeof(Head));
	memset(E,0,sizeof(E));
}

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
	int h,t;
	memset(dep,-1,sizeof(dep));
	memcpy(cur,Head,sizeof(cur));
	q.push(1);
	dep[1]=0;
	while(!q.empty())
	  {
	  	h=q.front();
	  	q.pop();
	  	for(int i=Head[h];i!=-1;i=E[i].next)
	  	  {
	  	  	t=E[i].to;
	  	  	if(dep[t]==-1&&E[i].w>0)
	  	  	  dep[t]=dep[h]+1,q.push(t);
	  	  }
	  }
	if(dep[n]==-1) return false;
	else return true;
}

int dfs(int u,int mn)
{
	if(u==n||mn==0) return mn;
	int v,used=0,w;
	for(int &i=cur[u];i!=-1;i=E[i].next)
	  {
	  	v=E[i].to;
	  	if(dep[v]==dep[u]+1&&E[i].w!=0)
	  	  {
	  	  	w=dfs(v,min(E[i].w,mn-used));
	  	  	E[i].w-=w;
	  	  	E[i^1].w+=w;
	  	  	used+=w;
	  	  }
	  }
	return used;
}

int Dinic()
{
	int ans=0;
	while(bfs())
	  ans+=dfs(1,0x3f3f3f3f);
	return ans;
}

int main()
{
	while(scanf("%d%d",&m,&n)!=EOF)
	  {
	  	init();
		int s,e,c;
		for(int i=1;i<=m;i++)
	  	  {
	  		scanf("%d%d%d",&s,&e,&c);
	  		add(s,e,c);
	  		add(e,s,0);
	  	  }
		printf("%d\n",Dinic());
	  }
	return 0;
}
