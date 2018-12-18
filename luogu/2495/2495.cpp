#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
    const int N=250010,inf=0x3f3f3f3f;
    int n,m,cnt,tot,top,num,tim,mark[N],a[N<<1],dep[N],Head[N],dfnin[N],dfnout[N],fa[N][23],st[N];
	ll dp[N],mn[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
		ll w;
    }E[N<<1];

    inline void add(int u,int v,ll w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],w};
        Head[v]=cnt;
    }

    void dfs(int u,int f,ll minn)
    {
        dfnin[u]=++tim;
		mn[u]=minn;
        dep[u]=dep[f]+1;
        fa[u][0]=f;
        for(int i=1;fa[u][i-1]&&i<=20;i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u,min(minn,E[i].w));
        }
        dfnout[u]=++tim;
    }

    inline bool cmp(int x,int y)
    {
		int t1=(x>0?dfnin[x]:dfnout[-x]);
		int t2=(y>0?dfnin[y]:dfnout[-y]);
		return t1<t2;
    }

    int LCA(int u,int v)
    {
        if(dep[u]<dep[v]) swap(u,v);
        for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
            if(d&1) u=fa[u][t];
        if(u==v) return u;
        for(int i=19;i>=0;i--)
            if(fa[u][i]!=fa[v][i]) 
                u=fa[u][i],v=fa[v][i];
        return fa[u][0];
    }

    inline void search()
    {
        int top=0;
        for(int i=1;i<=num;i++)
        {
            if(a[i]>0) st[++top]=a[i];
            else 
            {
                int now=st[top--];
                if(now==1) printf("%lld\n",dp[1]);
                else 
                {
                    int fa=st[top];
                    dp[fa]+=min(dp[now],mn[now]);
                }
                dp[now]=0,mark[now]=0;
            }
        }
    }

    void work()
    {
        n=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w);
        }
        dfs(1,0,inf);
       	scanf("%d",&m);
		while(m--)
		{
			num=read();
			for(int i=1;i<=num;i++) 
				a[i]=read(),mark[a[i]]=1,dp[a[i]]=mn[a[i]];
            sort(a+1,a+1+num,cmp);
            for(int i=1;i<num;i++)
            {
                int lca=LCA(a[i],a[i+1]);
                if(!mark[lca])
                    mark[lca]=1,a[++num]=lca;
            }
            for(int i=1,tmp=num;i<=tmp;i++)
                a[++num]=-a[i];
            if(!mark[1]) a[++num]=1,a[++num]=-1;
            sort(a+1,a+1+num,cmp);
            search();
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
