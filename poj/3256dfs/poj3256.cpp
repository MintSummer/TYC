#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
int k,n,m,head[1005],vis[1005],cow[1005],tim[1005];
struct edge
{
    int to,next;
}G[10050];

int cnt=0;

void add(int u,int v)
{
    cnt++;
    G[cnt].to=v;
    G[cnt].next=head[u];
    head[u]=cnt;
}

int t;
void dfs(int x)
{
    tim[x]++;
    vis[x]=1;
    for(int i=head[x];i;i=G[i].next)
      {
      	t=G[i].to;
      	if(vis[t]==0) dfs(t);
      }
}

int main()
{
    scanf("%d%d%d",&k,&n,&m);
    memset(vis,0,sizeof(vis));
    int a,b;
    for(int i=1;i<=k;i++)
      {
      	scanf("%d",&cow[i]);
      }
    for(int i=1;i<=m;i++)
      {
      	scanf("%d%d",&a,&b);
      	add(a,b);
      }
    for(int i=1;i<=k;i++)
      {
      	memset(vis,0,sizeof(vis));
      	dfs(cow[i]);
      }
    int ans=0;
    for(int i=1;i<=n;i++)
      if(tim[i]==k) ans++; 
    printf("%d",ans);
    return 0;
}