#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;

namespace TYC
{
    int n,s,cnt,vis[20],Head[20];
    double x[20],y[20],ans=1e9;

    struct edge
    {
		int to,next;
		double w;
    }E[20*20+10];

    void add(int u,int v,double w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    double dis(double a,double b,double c,double d)
    {
		return sqrt((a-c)*(a-c)+(b-d)*(b-d));
    }

    void dfs(int u,int num,double d)
    {
		if(d>ans) return;
		if(num==n) {ans=d;return;}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			vis[v]=1;
			dfs(v,num+1,d+E[i].w);
			vis[v]=0;
		}
    }

    void work()
    {
		scanf("%d",&n);
		x[0]=0,y[0]=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf",&x[i],&y[i]);
			for(int j=0;j<i;j++)
			{
				double d=dis(x[i],y[i],x[j],y[j]);
				add(i,j,d),add(j,i,d);
			}
		}
		vis[0]=1;
		dfs(0,0,0);
		printf("%.2lf",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
