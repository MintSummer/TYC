#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
int n,m,cnt=0,Head[3010],u[10010],v[10010],vis[3010];
double w[10010],flag,f[3010];
queue<int> q;

struct edge
{
	int to,next;
	double w;
}E[10010*2];

void init()
{
	cnt=0,flag=false;
	memset(vis,0,sizeof(vis));
	memset(Head,0,sizeof(Head));
	memset(f,0,sizeof(f));
}

void add(int u,int v,double w)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
}

void spfa(int u)
{
	vis[u]=1;
	for(int i=Head[u];i;i=E[i].next)
	{
		int v=E[i].to;
		if(f[v]-f[u]-E[i].w>eps)
		{
			f[v]=f[u]+E[i].w;
			if(vis[v]) {flag=true;return;}
			spfa(v);
		}
	}
	vis[u]=0;
}

bool panduan()
{
	for(int i=1;i<=n;i++)
	{
		spfa(i);
		if(flag==true) return true;
	}
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d%lf",&u[i],&v[i],&w[i]);
	double lt=-1e7,rt=1e7,mid,ans;
	while(lt<rt)
	{
		init();
		mid=(lt+rt)/2;
		for(int i=1;i<=m;i++) add(u[i],v[i],w[i]-mid);
		if(panduan()) ans=mid,rt=mid-eps;
		else lt=mid+eps;
	}
	printf("%.8lf",ans);
	return 0;
}
