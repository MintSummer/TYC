#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010;
int n,k,fa[MAXN],x[MAXN],y[MAXN];
struct edge
{
	int from,to;
	double w;
}E[MAXN*MAXN*2];

bool cmp(edge a,edge b)
{
	return a.w<b.w;
}

int find(int a)
{
	return fa[a]==a?a:fa[a]=find(fa[a]);
}

double dis(int i,int j)
{
	return sqrt( (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) );
}

int main()
{
	scanf("%d%d",&n,&k);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		fa[i]=i;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			E[++cnt].from=i,E[cnt].to=j,E[cnt].w=dis(i,j);
	sort(E+1,E+1+cnt,cmp);
	int u,v,fu,fv;
	double ans;
	for(int i=1,group=n;i<=cnt;i++)
	{
		u=E[i].from,v=E[i].to;
		fu=find(u),fv=find(v);
		if(fu!=fv)
		{
			if(group>k)
			{
				fa[fu]=fv;
				group--;
			}
			else
			{
				printf("%.2lf",E[i].w);
				return 0;
			}
		}
	}
}
