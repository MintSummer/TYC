#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,t;
int G[310][310];

void floyd()
{
	for(int k=1;k<=n;k++)
	  for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	      if(G[i][j]>max(G[i][k],G[k][j]))
	        G[i][j]=max(G[i][k],G[k][j]);
}

int main()
{
	memset(G,0x3f3f3f3f,sizeof(G));
	scanf("%d%d%d",&n,&m,&t);
	int s,e,h;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d%d",&s,&e,&h);
	  	G[s][e]=h;
	  }
	floyd();
	int a,b;
	for(int i=1;i<=t;i++)
	  {
	  	scanf("%d%d",&a,&b);
	  	if(G[a][b]>1000000) printf("-1\n");
	  	else printf("%d\n",G[a][b]);
      }
    return 0;
}