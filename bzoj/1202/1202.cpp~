#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int sum[110],fa[110];
//sum表示前缀和 sum[x]表示从find(x)到x（即sum[x]-sum[find(x)-1]）的值

int find(int a)
{
	if(fa[a]!=a)
	{
		int f=fa[a];
		fa[a]=find(fa[a]);
		sum[a]+=sum[f];
	}
	return fa[a];
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++) fa[i]=i,sum[i]=0;
		int x,y,z,fx,fy,flag=1;
		while(m--)
		{
			scanf("%d%d%d",&x,&y,&z);
			x--;//z应该为sum[y]-sum[x-1],所以给x--
			fx=find(x),fy=find(y);
			if(fx!=fy)
			{
				fa[fy]=fx;
				sum[fy]=sum[x]+z-sum[y];
			}
			else 
				if(sum[x]+z!=sum[y]) flag=0;
		}
		if(flag) printf("true\n");
		else printf("false\n");
	}
	return 0;
}
