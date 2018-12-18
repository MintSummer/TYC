#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=130,p=45989;
    int n,m,s,t,cnt=1,Head[N];
    ll tim;

    struct edge
    {
        int to,next;
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    struct Matrix 
    {
        int n,m;
        ll G[N][N];
        Matrix()
        {
            n=0,m=0;
            memset(G,0,sizeof(G));
        }

        Matrix operator * (const Matrix &t) const
        {
            Matrix ans;
            ans.n=n,ans.m=t.m;
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                    if(G[i][j])
                        for(int k=1;k<=t.m;k++)
                            ans.G[i][k]=(ans.G[i][k]+G[i][j]*t.G[j][k])%p;
            return ans;
        }
    }fir,M;

    inline void qpow(Matrix &ans,Matrix &a,ll tim)
    {
        for(;tim;tim>>=1,a=a*a)
            if(tim&1) ans=ans*a;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin>>n>>m>>tim>>s>>t;
        s++,t++;
        int u,v;
        for(int i=1;i<=m;i++)
        {
            cin>>u>>v;
            u++,v++;
            add(u,v),add(v,u);
        }
        M.n=M.m=fir.m=cnt,fir.n=1;
        for(int i=2;i<=cnt;i++)
        {
            int u=E[i].to;
            for(int j=Head[u];j;j=E[j].next)
                if(i!=(j^1)) M.G[i][j]++;
        }
        for(int i=Head[s];i;i=E[i].next) fir.G[1][i]++;
        qpow(fir,M,tim-1);
        ll ans=0;
        for(int i=Head[t];i;i=E[i].next)
            ans=(ans+fir.G[1][i^1])%p;
        cout<<ans<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}