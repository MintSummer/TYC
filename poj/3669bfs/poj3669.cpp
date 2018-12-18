#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
int n,ans=-1;
int G[310][310],vis[310][310];
int dx[10]={0,-1,0,1,0};
int dy[10]={0,0,-1,0,1};
int xx,yy,now;
int tim[1005*305];
queue<int> q;

void bfs()
{
    if(G[0][0]==0) return;
    if(G[0][0]==-1) {ans=0;return;}
    now=0;
    tim[now]=0;
    q.push(now);
    vis[0][0]=1;
    while(!q.empty())
      {
      	now=q.front();
      	q.pop();
      	int y=now%1000,x=now/1000;
      	for(int k=1;k<=4;k++)
      	  {
      	  	xx=x+dx[k],yy=y+dy[k];
      	  	if(xx<0||yy<0) continue;
            if(G[xx][yy]==-1)
      	      {
      	      	ans=tim[now]+1;
      	      	return;
      	      }
            if(vis[xx][yy]==1||G[xx][yy]<=tim[now]+1) continue;
      	    
      	    vis[xx][yy]=1;
      	    tim[xx*1000+yy]=tim[now]+1;
      	    q.push(xx*1000+yy);
          }
      }
}

int main()
{
    memset(G,-1,sizeof(G));
    memset(vis,0,sizeof(vis));
    scanf("%d",&n);
    int x,y,t;
    for(int i=1;i<=n;i++)
      {
      	scanf("%d%d%d",&x,&y,&t);
      	if(G[x][y]==-1) G[x][y]=t;
      	for(int q=1;q<=4;q++)
      	  {
      	  	if(x+dx[q]>=0&&y+dy[q]>=0)
      	      {
      	      	if(G[x+dx[q]][y+dy[q]]==-1)
      	      	  G[x+dx[q]][y+dy[q]]=t;
      	      	else 
      	      	  G[x+dx[q]][y+dy[q]]=min(G[x+dx[q]][y+dy[q]],t);//´æ×îÐ¡
      	      }
      	  }
      }
    bfs();
    printf("%d",ans);
    return 0;
}