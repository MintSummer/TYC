#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P=18;
const int MAXN=100010; 
int n,m,cnt,Head[MAXN],ffa[MAXN],maxx,les;
int fa[MAXN][20],dep[MAXN],mx[MAXN][20],lsmx[MAXN][20]; 
ll mn=0;

struct edge1
{
	int f,t,w;
	bool flag;
	bool operator < (const edge1 &a) const {return w<a.w;}
}q[300010];

struct edge2
{
	int to,next,w;
}E[300010*2];

void add(int u,int v,int w)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
}

int find(int a)
{
	return ffa[a]==a?a:ffa[a]=find(ffa[a]);
}

void kruskal()
{
	int u,v,fu,fv,tim=0;
	for(int i=1;i<=m;i++)
	{
		u=q[i].f,v=q[i].t;
		fu=find(u),fv=find(v);
		if(fu==fv) continue;
		ffa[fu]=fv;
		mn+=q[i].w;
		q[i].flag=true;
		add(u,v,q[i].w),add(v,u,q[i].w);
		if(++tim==n-1) return;
	}
}

void dfs(int u,int f)
{
	dep[u]=dep[f]+1;
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==f) continue;
		fa[v][0]=u;
		mx[v][0]=E[i].w,lsmx[v][0]=0;
		dfs(v,u);
	}
}

void init()
{
	for(int j=1;j<=18;j++)
	{
		for(int i=1;i<=n;i++)
		{
			int f=fa[i][j-1];
			fa[i][j]=fa[f][j-1];
			if(mx[i][j-1]>mx[f][j-1]) 
				mx[i][j]=mx[i][j-1],lsmx[i][j]=max(mx[f][j-1],lsmx[i][j-1]);
			else if(mx[i][j-1]<mx[f][j-1]) 
				mx[i][j]=mx[f][j-1],lsmx[i][j]=max(lsmx[f][j-1],mx[i][j-1]);
			else mx[i][j]=mx[i][j-1],lsmx[i][j]=max(lsmx[i][j-1],lsmx[f][j-1]);
		}
	}
}

void lca(int u,int v)
{
	les=maxx=0;
	if(dep[u]<dep[v]) swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<=18;i++,d>>=1) 
		if(d&1)
		{
			les=max(les,lsmx[u][i]);
			if(maxx<mx[u][i]) les=max(maxx,les),maxx=mx[u][i];
			else if(maxx>mx[u][i]) les=max(les,mx[u][i]);
			u=fa[u][i];
		}  
	if(u==v) return;
	int a,b;
	for(int i=18;i>=0;i--)
		if(fa[u][i]!=fa[v][i])	
		{
			les=max(les,max(lsmx[u][i],lsmx[v][i]));
			if(mx[u][i]>mx[v][i]) a=mx[u][i],b=mx[v][i];
			else a=mx[v][i],b=mx[u][i];
			if(a==b) b=0;
			if(a>maxx) les=max(maxx,b),maxx=a;
			else if(a<maxx) les=max(les,a);
			else les=max(les,b);
			u=fa[u][i],v=fa[v][i];
		}
	les=max(les,max(lsmx[u][0],lsmx[v][0]));
	if(mx[u][0]>mx[v][0]) a=mx[u][0],b=mx[v][0];
	else a=mx[v][0],b=mx[u][0];
	if(a==b) b=0;
	if(a>maxx) les=max(maxx,b),maxx=a;
	else if(a<maxx) les=max(les,a);
	else les=max(les,b);
	return;
}

int change(int u,int v,int w)
{
	lca(u,v);
	if(maxx==w) return w-les;
	else return w-maxx;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) ffa[i]=i;
	int u,v,w;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		q[i]=(edge1){u,v,w,false};
	}
	sort(q+1,q+1+m);
	kruskal();

	dfs(1,0),init();
	int more=0x3f3f3f3f;
	for(int i=1;i<=m;i++)
	{
		if(q[i].flag) continue;
		u=q[i].f,v=q[i].t;
		more=min(more,change(u,v,q[i].w));
	}
	printf("%lld",mn+more);
	return 0;
}
