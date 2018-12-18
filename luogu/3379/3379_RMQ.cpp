#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=500010;
    int n,m,root,cnt,tot,Head[N],fir[N],list[N<<1],dep[N<<1],d[N],st[N<<1][21];
    
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
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void dfs(int u,int f)
    {
        d[u]=d[f]+1;
        list[++tot]=u;
        dep[tot]=d[u];
        fir[u]=tot;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
            list[++tot]=u;
            dep[tot]=d[u];
        }
    }

    void init()
    {
        for(int i=1;i<=tot;i++) st[i][0]=i;
        for(int i=1;i<=19;i++)
            for(int j=1;j+(1<<i)-1<=tot;j++)
            {
                int x=st[j][i-1],y=st[j+(1<<(i-1))][i-1];
                st[j][i]=dep[x]<dep[y]?x:y;
            }  
    }

    int query(int u,int v)
    {
        int l=fir[u],r=fir[v];
		if(l>r) swap(l,r);
        int k=log2(r-l+1);
        int x=st[l][k],y=st[r-(1<<k)+1][k];
        return list[dep[x]<dep[y]?x:y];
    }

    void work()
    {
        n=read(),m=read(),root=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(root,0);
        init();
        while(m--)
        {
            int u=read(),v=read();
            printf("%d\n",query(u,v));
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}