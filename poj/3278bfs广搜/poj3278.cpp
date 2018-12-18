#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100000;
int n,k,ans=0x3f3f3f3f,tim[MAXN+10],h,vis[MAXN+10];
int q[MAXN*2+10],f,e;

void bfs()
{
	q[++e]=n;
	vis[n]=1;
	while(f<e)
	  {
	  	h=q[++f];
	    if(h==k) return;
	  	if(vis[h+1]==0&&h<MAXN)
	  	  q[++e]=h+1,vis[h+1]=1,tim[h+1]=tim[h]+1;
	  	if(vis[h-1]==0&&h>0)
	  	  q[++e]=h-1,vis[h-1]=1,tim[h-1]=tim[h]+1;
	  	if(vis[2*h]==0&&h<=50000)
	  	  q[++e]=h*2,vis[h*2]=1,tim[h*2]=tim[h]+1;
	  }
}

int main()
{
	scanf("%d%d",&n,&k);
	bfs();
	printf("%d",tim[k]);
	return 0;
}