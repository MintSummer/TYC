#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const double eps=1e-5;
    const int N=2510,inf=0x3f3f3f3f;
    int k,n,cnt,a[N],b[N],Head[N],size[N];
	double dp[N][N],tmp[N],val[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=ch-'0',ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v]};
        Head[v]=cnt;
    }

    void dfs(int u,int fa)
    {
        size[u]=1;
        dp[u][0]=0,dp[u][1]=val[u];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa) continue;
            dfs(v,u);
			for(int j=1;j<=size[u]+size[v];j++) tmp[j]=-inf;
            for(int j=1;j<=size[u];j++)
                for(int s=0;s<=size[v];s++)
					tmp[j+s]=max(tmp[j+s],dp[u][j]+dp[v][s]);
            size[u]+=size[v];
			for(int j=1;j<=size[u];j++) dp[u][j]=tmp[j];
        }
    }

    inline bool check(double mid)
    {
        for(int i=1;i<=n;i++) 
            val[i]=(double)b[i]-mid*a[i];
        memset(dp,0xc2,sizeof(dp));
        dfs(0,-1);
        return dp[0][k+1]>0;
    }

    void work()
    {
        k=read(),n=read();
        for(int i=1;i<=n;i++) 
        {
            a[i]=read(),b[i]=read();
            add(read(),i);
        }
        double l=0,r=10000,mid,ans;
        while(r-l>=eps)
        {
            mid=(l+r)/2.0;
            if(check(mid)) ans=mid,l=mid+eps;
            else r=mid-eps;
        }
        printf("%.3lf\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
