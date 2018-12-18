//线段树优化建边
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=5e5+10;
    const int inf=1e9;

    int n,node,rot,ls[N],rs[N],Head[N],arr[N],f[N],deg[N],id[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    inline void write(int x)
    {
        if(!x) putchar('0');
        else
        {
            int len=0;
            static int bask[50];
            while(x) bask[++len]=x%10,x/=10;
            for(;len;len--) putchar('0'+bask[len]);
        }
        putchar(' ');
    }

    struct edge
    {
        int to,next,w;
    }E[N*10];

    inline void add(const int &u,const int &v,const int &w)
    {
        static int cnt=0;
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        deg[v]++;
    }

    void build(int &root,int l,int r,int fa=0)
    {
        root=++node;
        if(fa) add(fa,root,0);
        if(l==r) {id[l]=root;return;}
        int mid=(l+r)>>1;
        build(ls[root],l,mid,root);
        build(rs[root],mid+1,r,root);
    }

    void query(int root,int l,int r,int s,int e,int now)
    {
        if(s<=l&&r<=e) {add(now,root,0);return;}
        int mid=(l+r)>>1;
        if(s<=mid) query(ls[root],l,mid,s,e,now);
        if(e>mid) query(rs[root],mid+1,r,s,e,now);
    }

    bool toposort()
    {
        static int h=1,t=0,q[N],vis[N];
        for(int i=1;i<=node;i++) f[i]=inf;
        for(int i=1;i<=node;i++)
            if(!deg[i]) q[++t]=i;
        while(h<=t)
        {
            int u=q[h++];
            vis[u]=1;
            if(f[u]<=0) return false;
            if(arr[u])
            {
                if(f[u]<arr[u]) return false;
                f[u]=arr[u];
            }
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                f[v]=min(f[v],f[u]-E[i].w);
                if(!(--deg[v])) q[++t]=v;
            }
        }
        for(int i=1;i<=n;i++)
            if(!vis[id[i]]) return false;
        return true;
    }
        
    void work()
    {
        n=read();
        build(rot,1,n);
        int s=read(),m=read();
        while(s--) 
        {
            int pos=read();
            arr[id[pos]]=read();
        }
        while(m--)
        {
            int l=read(),r=read(),k=read(),last=l-1,x;
            node++;
            for(int i=1;i<=k;i++) 
            {
                x=read();
                add(id[x],node,1);
                if(x>last+1) query(rot,1,n,last+1,x-1,node);
                last=x;
            }
            if(x<r) query(1,1,n,x+1,r,node);
        }
        if(!toposort()) puts("NIE");
        else
        {
            puts("TAK");
            for(int i=1;i<=n;i++) write(f[id[i]]);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
