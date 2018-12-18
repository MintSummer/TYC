#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n,m;
int g[110][110];

int main()
{
	memset(g,0,sizeof(g));
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d",&a,&b);
	  	g[a][b]=1;
	  }
	for(int k=1;k<=n;k++)
	  for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	      if(g[i][k]&&g[k][j])
	        g[i][j]=1;
	int ans=0,q;
	for(int i=1;i<=n;i++)
	  {
	  	q=1;
	  	for(int j=1;j<=n;j++)
	  	  {
	  	  	if(i!=j&&g[i][j]==0&&g[j][i]==0) 
	  	  	  {
	  	  	  	q=0;break;
	  	  	  }
	  	  }
	  	if(q!=0) ans++; 
	  }
	printf("%d",ans);
	return 0;
} 