#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,m,ned,ans,sum;
int u[MAXN],v[MAXN],w[MAXN],c[MAXN],fa[MAXN];

struct edge
{
	int f,t,w,c;
}e[100010];

bool cmp(edge a,edge b)
{
	return a.w==b.w?a.c<b.c:a.w<b.w;
}

int find(int a)
{
	return a==fa[a]?a:fa[a]=find(fa[a]);
}

bool check(int x)
{
	sum=0;
	int tim=0;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		e[i].f=u[i],e[i].t=v[i],e[i].w=w[i],e[i].c=c[i];
		if(!c[i]) e[i].w+=x;
	}
	sort(e+1,e+1+m,cmp);
	int a,b,FA,FB;
	for(int i=1;i<=m;i++)
	{
		a=e[i].f,b=e[i].t;
		FA=find(a),FB=find(b);
		if(FA!=FB)
		{
			fa[FA]=FB;
			sum+=e[i].w;
			if(!e[i].c) tim++;
		}
	}
	return tim>=ned;
}

int main()
{
	scanf("%d%d%d",&n,&m,&ned);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&u[i],&v[i],&w[i],&c[i]);
		u[i]++,v[i]++;
	}
	int l=-105,r=105,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=sum-ned*mid;
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}
