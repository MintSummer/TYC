#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
int n,T,G[1010][1010],f[1010],vis[1010];
int q[1010*5];

void spfa(int s)
{
	int a,h=0,t=0;
	q[++t]=s;
	vis[s]=1;
	f[s]=0;
	while(h<t)
	  {
	  	a=q[++h];
	  	vis[a]=0;
	  	for(int i=1;i<=n;i++)
	  	  if(G[a][i]!=0&&f[i]>f[a]+G[a][i])
	  	    {
	  	    	f[i]=f[a]+G[a][i];
	  	    	if(vis[i]==0)
	  	    	  {
	  	    	  	vis[i]=1;
	  	    	  	q[++t]=i;
	  	    	  }
	  	    }
	  }
	return;
}

int main()
{
	memset(G,0,sizeof(G));
	memset(f,0x3f3f3f3f,sizeof(f));
	memset(vis,0,sizeof(vis));
	scanf("%d%d",&T,&n);
	int e,F,l;
	for(int i=1;i<=T;i++)
	  {
	  	scanf("%d%d%d",&F,&e,&l);
	  	if(G[F][e]==0) G[F][e]=l;
	  	else G[F][e]=min(G[F][e],l);
	  	G[e][F]=G[F][e];
	  }
	spfa(1);
	printf("%d",f[n]);
	return 0;
}