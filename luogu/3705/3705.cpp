#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=110,inf=0x3f3f3f3f;
    const double eps=1e-8;//1e-7的精度炸了2个点了解一下
    int n,cnt,a[MAXN][MAXN],b[MAXN][MAXN],Head[MAXN*2],vis[MAXN*2],pre[MAXN*2],s,t;
    double f[MAXN*2];

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int from,to,next,w;
		double c;
    }E[11111*2];

    void add(int u,int v,int w,double c)
    {
		E[++cnt]=(edge){u,v,Head[u],w,c};
		Head[u]=cnt;
    }

    void insert(int u,int v,double w,double c)
    {
		add(u,v,w,c),add(v,u,0,-c);
    }

    bool spfa()
    {
		for(int i=1;i<=n;i++) f[i]=-inf;
		memset(vis,0,sizeof(vis));
		memset(pre,0,sizeof(pre));
		queue<int> q;
		q.push(s);
		f[s]=0,vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w>0&&f[v]<f[u]+E[i].c)//最大费用最大流
				{
					f[v]=f[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return f[t]!=-inf;
    }

    double EK()
    {
		double ans=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i].from])
				mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i].from])
				E[i].w-=mn,E[i^1].w+=mn;
			ans+=mn*f[t];
		}
		return ans;
    }

    bool judge(double x)
    {
		cnt=1;
		memset(Head,0,sizeof(Head));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				insert(i,j+n,1,(double)a[i][j]-x*b[i][j]);
		for(int i=1;i<=n;i++)
			insert(s,i,1,0),insert(i+n,t,1,0);
		n=n*2+2;
		double tmp=EK();
		n=(n-2)/2;
		if(tmp>=0) return true;
		else return false;
    }

    void work()
    {
		n=read();
		s=2*n+1,t=2*n+2;
		double lt=0,rt=0,ans;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				a[i][j]=read(),rt+=a[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				b[i][j]=read();
		while(rt-lt>eps)
		{
			double mid=(lt+rt)/2;
			if(judge(mid)) ans=mid,lt=mid+eps;
			else rt=mid-eps;
		}
		printf("%.6lf",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
