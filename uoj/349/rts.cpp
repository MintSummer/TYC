#include "rts.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
int vis[300010];

void play(int n, int T, int dataType)
{
	int now=1;
	if(dataType==3)
	{
		int mx[2];//分别指两个方向的端点，两端点中间的显然均已访问过
		mx[0]=1,mx[1]=1;
		int k=0;//k所指的为从1到2的那个方向，k^1相反
		for(int i=2;i<=n;i++)
		{
			if(vis[i]) continue;
			while(!vis[i])
			{
				now=explore(now,i);
				if(vis[now]) now=mx[k^=1];//说明已经换方向了，直接从另一方向的最外端去找
				else vis[now]=1,mx[k]=now;
			}
		}
	}
	else 
	{
		for(int i=2;i<=n;i++)
		{
			if(vis[i]) continue;
			while(now!=i)
			{
				now=explore(now,i);
				vis[now]=1;
			}
		}
	}
}
