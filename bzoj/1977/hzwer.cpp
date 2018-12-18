#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define N 100001
#define M 300001
#define inf 0x7fffffff
#define ll long long
using namespace std;
int n,m,tot,cnt,mn=inf;
ll ans;
int f[N],head[N],deep[N],fa[N][17],d1[N][17],d2[N][17];
struct data{int x,y,v;bool sel;}a[M];
struct edge{int to,next,v;}e[N*2];
bool cmp(data a,data b)
{return a.v<b.v;}
void ins(int u,int v,int w)
{e[++cnt].to=v;e[cnt].next=head[u];e[cnt].v=w;head[u]=cnt;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,w);}
int find(int x){return x==f[x]?x:find(f[x]);}
void dfs(int x,int f)
{
	for(int i=1;i<=16;i++)
	{
		if(deep[x]<(1<<i))break;
        fa[x][i]=fa[fa[x][i-1]][i-1];
        d1[x][i]=max(d1[x][i-1],d1[fa[x][i-1]][i-1]);
        if(d1[x][i-1]==d1[fa[x][i-1]][i-1])
		    d2[x][i]=max(d2[x][i-1],d2[fa[x][i-1]][i-1]);
        else 
		{
		    d2[x][i]=min(d1[x][i-1],d1[fa[x][i-1]][i-1]);
		    d2[x][i]=max(d2[x][i-1],d2[x][i]);
		    d2[x][i]=max(d2[x][i],d2[fa[x][i-1]][i-1]);
		}
    }
    for(int i=head[x];i;i=e[i].next)
    	if(e[i].to!=f)
    	{
    		fa[e[i].to][0]=x;
    		d1[e[i].to][0]=e[i].v;
    		deep[e[i].to]=deep[x]+1;
    		dfs(e[i].to,x);
    	}
}
int lca(int x,int y)
{
    if(deep[x]<deep[y])swap(x,y);
    int t=deep[x]-deep[y];
    for(int i=0;i<=16;i++)
        if((1<<i)&t)x=fa[x][i];
    for(int i=16;i>=0;i--)
    {
        if(fa[x][i]!=fa[y][i])
        {x=fa[x][i];y=fa[y][i];}
    }
    if(x==y)return x;
    return fa[x][0];
}
void cal(int x,int f,int v)
{
    int mx1=0,mx2=0;
    int t=deep[x]-deep[f];
    for(int i=0;i<=16;i++)
    {
        if(t&(1<<i))
        {
           if(d1[x][i]>mx1)
           {
           	   mx2=mx1;
           	   mx1=d1[x][i];
           }
           mx2=max(mx2,d2[x][i]);
           x=fa[x][i];
        }
    }
    if(mx1!=v)mn=min(mn,v-mx1);
    else mn=min(mn,v-mx2);
}
void solve(int t,int v)
{
	int x=a[t].x,y=a[t].y,f=lca(x,y);
	cal(x,f,v);cal(y,f,v);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
 	   f[i]=i;
	for(int i=1;i<=m;i++)
	    scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
    	int p=find(a[i].x),q=find(a[i].y);
    	if(p!=q)
        {
        	f[p]=q;
        	ans+=a[i].v;
			a[i].sel=1;
        	insert(a[i].x,a[i].y,a[i].v);
        	tot++;if(tot==n-1)break;
        }
    }
    dfs(1,0);
    for(int i=1;i<=m;i++)
	   if(!a[i].sel)solve(i,a[i].v);
    printf("%lld",ans+mn);
	return 0;
}
