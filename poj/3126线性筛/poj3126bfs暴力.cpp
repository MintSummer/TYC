#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int m,n,T,ans,cnt=0;
int prime[10010];
bool ok[10010],flag;
int vis[10010];
struct node
{
	int num,t;
};

void S()
{
    memset(ok,true,sizeof(ok));
    ok[1]=false;
	for(int i=2;i<=10000;i++)
	  {
	  	if(ok[i]==true) prime[++cnt]=i;
	  	for(int j=1;j<=cnt&&prime[j]*i<=10000;j++)
	  	  {
	  	  	ok[i*prime[j]]=false;
			if(i%prime[j]==0) break;
	  	  }
	  }
}

void bfs(int x)
{
    queue<node> q;
	int h,t,now;
	q.push(node{x,0});
	vis[x]=1;
	while(!q.empty())
	  {
	  	h=q.front().num,t=q.front().t;
	  	if(h==n) 
	  	  {
	  	  	flag=1;
	  	  	printf("%d\n",t);
	  	  	return;
	  	  }
	  	q.pop();
	  	for(int i=1000;i>=1;i/=10)
	  	  for(int j=0;j<=9;j++)
	  	    {
	  	    	if(i==1000&&j==0) continue;
	  	    	now=h-(h/i)%10*i+i*j;
	  	    	if(!vis[now]&&ok[now]==true)
	  	    	    q.push(node{now,t+1}),vis[now]=1;
	  	    }
	  }
}

int main()
{
	scanf("%d",&T);
	S();
	while(T--)
	  {
	  	flag=0;
	  	memset(vis,0,sizeof(vis));
	  	scanf("%d%d",&m,&n);
	  	bfs(m);
	  	if(flag==0) printf("Impossible\n");
	  }
	return 0;
}
