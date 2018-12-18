#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const double EPS=1e-7;
int n,p,cnt=0,flag,Head[1010],vis[1010];
double f[1010],fun[1010],c[5010],ans=-1;

struct edge
{
    int to,next;
    double len;
}E[5010];

void add(int u,int v,double w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].len=w;
    Head[u]=cnt;
}

void spfa(int x)
{
    vis[x]=1;
    for(int i=Head[x];i;i=E[i].next)
      {
      	int t=E[i].to;
      	if(f[t]>f[x]+c[i])
        {
        	f[t]=f[x]+c[i];
        	if(vis[t]) 
        	  {
        	  	flag=1;
        	  	return;
        	  }
        	spfa(t);
        }
      }
    vis[x]=0;
}

bool panduan()
{
    memset(f,0,sizeof(f));
    memset(vis,0,sizeof(vis));
    flag=0;
    for(int i=1;i<=n;i++)
      {
      	spfa(i);
      	if(flag) return true;
      }
    return false;
}

int main()
{
    scanf("%d%d",&n,&p);
    int sum=0;
    for(int i=1;i<=n;i++)
      scanf("%lf",&fun[i]),sum+=fun[i];
    int x,y;
    double le;
    for(int i=1;i<=p;i++)
      {
      	scanf("%d%d%lf",&x,&y,&le);
      	add(x,y,le);
      }
    double l=0,r=sum*1.0,mid;
    int t;
    while(r-l>EPS)
      {
      	mid=(l+r)/2;
      	for(int i=1;i<=cnt;i++)
      	  {
      	  	t=E[i].to;
      	  	c[i]=E[i].len*mid-fun[t];
      	  }
      	if(panduan()) 
      	  {
      	  	ans=mid;
      	  	l=mid;
      	  }
      	else r=mid;
      }
    printf("%.2lf",ans);
    return 0;
}
