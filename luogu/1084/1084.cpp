#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=50010;
    int n,cnt,m,tot,Head[N],station[N],leaf[N],fa[N][20],top[N],list[N];
    ll dis[N][20];
    bool fl,control[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next,w;
    }E[N<<1];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u,int f,int ance)
    {
        top[u]=ance;
        fa[u][0]=f;
        for(int i=1;fa[u][i-1]&&i<=18;i++)
        {
            fa[u][i]=fa[fa[u][i-1]][i-1];
            dis[u][i]=dis[fa[u][i-1]][i-1]+dis[u][i-1];
        }
        int son=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            son++;
            dis[v][0]=E[i].w;
            dfs(v,u,ance);
        }
        if(!son) leaf[u]=1;
    }

    struct node
    {
        int top;
        ll res;
    }a[N],b[N];

    bool cmp_min(const node &x,const node &y)
    {
        return x.res<y.res;
    }

    bool cmp_max(const node &x,const node &y)
    {
        return x.res>y.res;
    }

    void dfs(int u)
    {
        if(leaf[u]) {fl=1;return;}
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u][0]||control[v]) continue;
            dfs(v);
            if(fl) return; 
        }
    }

    bool have_leaf(int u)
    {
        fl=0;
        dfs(u);
        return fl;
    }

    bool check(ll mid)
    {
        memset(control,false,sizeof(int[n+1]));
        int tot=0,num=0;
        for(int i=1;i<=m;i++)
        {
            int x=station[i];
            ll res=mid;
            for(int j=18;j>=0;j--)
                if(fa[x][j]&&dis[x][j]<=res)
                    res-=dis[x][j],x=fa[x][j];
            if(x==1) a[++tot]=(node){top[station[i]],res};
            else control[x]=1;
        }
        sort(a+1,a+1+tot,cmp_min);
        for(int i=1;i<=tot;i++)
            if(a[i].res<dis[a[i].top][0])
                if(!control[a[i].top]&&have_leaf(a[i].top))
                    control[a[i].top]=1,a[i].res=-1;
        for(int i=Head[1];i;i=E[i].next)
        {
            int v=E[i].to;
            if(!control[v]&&have_leaf(v))
                b[++num]=(node){v,E[i].w};
        } 
        sort(b+1,b+1+num,cmp_max);
        sort(a+1,a+1+tot,cmp_max);
        for(int i=1;i<=num;i++)
            if(i>tot) return false;
            else if(a[i].res<b[i].res) return false;
        return true;
    }

    void work()
    {
        n=read();
        ll l=0,r=0,mid,ans=-1;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w),add(v,u,w);
            r+=w;
        }
        m=read();
        for(int i=1;i<=m;i++) station[i]=read();
        int num=0;
        for(int i=Head[1];i;i=E[i].next) 
        {
            num++;
            dis[E[i].to][0]=E[i].w;
            dfs(E[i].to,1,E[i].to);
        }
        if(num>m) {puts("-1");return;}
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid)) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    freopen("a.in","r",stdin);
    TYC::work();
    return 0;
}