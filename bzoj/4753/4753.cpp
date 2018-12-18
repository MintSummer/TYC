#include<bits/stdc++.h>
 
using namespace std;
 
namespace Tzh{
 
    typedef double dd;
    const int maxn=2510;
    const dd eps=1e-6;
    int f[maxn],cnt,tot,n,size[maxn],s[maxn],head[maxn],k,p[maxn],fa[maxn];
    dd dp[maxn][maxn],w[maxn];
 
    struct ed{
        int next,to;
    }e[maxn];
 
    void add(int u,int v){
        e[++cnt]=(ed){head[u],v}; head[u]=cnt;
    }
 
    void dfs(int now){
        size[now]=1; dp[now][1]=w[now];
        for(int i=head[now];i;i=e[i].next){
            int tt=e[i].to; dfs(tt);
            for(int j=size[now];j;j--)
                for(int k=size[tt];k;k--)
                    dp[now][j+k]=max(dp[now][j+k],dp[now][j]+dp[tt][k]);
            size[now]+=size[tt];
        }
    }
 
    bool pan(dd x){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=k;j++)
                dp[i][j]=-1e9;
        for(int i=1;i<=n;i++) w[i]=(dd)p[i]-s[i]*x;
        dfs(1); return dp[1][k]>eps;
    }
 
    void work(){
        scanf("%d%d",&k,&n); k++; n++;
        for(int i=2;i<=n;i++){
            scanf("%d%d%d",&s[i],&p[i],&fa[i]);
            fa[i]++; add(fa[i],i);
        }
        dfs(1); dd l=0,r=1e9;
        while(l<=r){
            dd mid=(l+r)/2.0;
            if(pan(mid)) l=mid+eps;
            else r=mid-eps;
        }
        printf("%.3lf",l);
        return ;
    }
}
 
int main(){
    Tzh::work();
    return 0;
}
