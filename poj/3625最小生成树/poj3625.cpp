#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int MAXN=1010;
int n,m,cnt=0,fa[MAXN];
long double x[MAXN],y[MAXN],ans=0;
struct edge
{
	int f,e;
	long double w;
	bool operator<(const edge &b)const
	{
		return w<b.w;
	}
}G[MAXN*MAXN/2];

void add(int u,int v,double w)
{
	cnt++;
	G[cnt].f=u;
	G[cnt].e=v;
	G[cnt].w=w;
}

int find(int a)
{
	return fa[a]==a?a:fa[a]=find(fa[a]);
}

bool cmp(edge a,edge b)
{
	return a.w<b.w;
}

void kruskal(void)
{
	int a,b;
	int FA,FB;
	for(int i=1;i<=cnt;i++)
	  {
	  	a=G[i].f,b=G[i].e;
	  	FA=find(a),FB=find(b);
	  	if(FA!=FB)
	  	  {
	  	  	ans+=G[i].w;
	  	  	fa[FA]=FB;
	  	  }
	  }
	printf("%.2Lf",ans);
}

int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	long double d;
	for(int i=1;i<=n;i++)
	  {
	  	cin>>x[i]>>y[i];
	  	for(int j=1;j<i;j++)
	  	  {
	  	  	d=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
	  	  	add(i,j,d);
	  	  }
	  }
	int aa,bb;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d",&aa,&bb);
	  	fa[find(aa)]=find(bb);
	  }
	sort(G+1,G+1+cnt);
	kruskal();
	return 0;
}