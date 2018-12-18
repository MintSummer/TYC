#include<bits/stdc++.h>
using namespace std;
int n,cnt=0,w[310],fa[310];

struct edge
{
	int s,t,w;
}E[100010];

void add(int u,int v,int w)
{
	cnt++;
	E[cnt].s=u;
	E[cnt].t=v;
	E[cnt].w=w;
}

bool cmp(edge a,edge b)
{
	return a.w<b.w;
}

int find(int a)
{
	return a==fa[a]?a:fa[a]=find(fa[a]);
}

int kruskal()
{
	int ans=0;
	int u,v,fu,fv;
	for(int i=1;i<=cnt;i++)
	  {
	  	u=E[i].s,v=E[i].t;
	  	fu=find(u),fv=find(v);
	  	if(fu!=fv)
	  	  {
	  	  	fa[fu]=fv;
	  	  	ans+=E[i].w;
	  	  }
	  }
	return ans;
}

int main()
{
	scanf("%d",&n);
	w[0]=0;//自定义一个起点0 
	for(int i=1;i<=n;i++)
	  {
	  	scanf("%d",&w[i]);
	  	add(0,i,w[i]);//打一个井就相当于与起点0连接 
		fa[i]=i;
	  }
	int d;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    {
	    	scanf("%d",&d);
	    	if(d>0) add(i,j,d);
	    }
	sort(E+1,E+1+cnt,cmp);
	printf("%d",kruskal());
	return 0;
} 
