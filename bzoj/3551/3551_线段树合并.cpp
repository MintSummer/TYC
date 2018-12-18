//内存和时限都险险地卡过去了哇o((⊙﹏⊙))o.
#include<bits/stdc++.h>
using namespace std;

namespace Tree
{
    const int N=1e5*70+10;
    int cnt,ls[N],rs[N],val[N];

    void insert(int &root,int l,int r,int w)
    {
        root=++cnt;
        val[root]=1;
		if(l==r) return;
        int mid=(l+r)>>1;
        if(w<=mid) insert(ls[root],l,mid,w);
        else insert(rs[root],mid+1,r,w);
    }

    int merge(int x,int y,int l,int r)
    {
        if(!x||!y) return x+y;
		int tmp=++cnt;
        if(l==r) {val[tmp]=val[x]+val[y];return tmp;}
        int mid=(l+r)>>1;
        ls[tmp]=merge(ls[x],ls[y],l,mid);
        rs[tmp]=merge(rs[x],rs[y],mid+1,r);
		val[tmp]=val[ls[tmp]]+val[rs[tmp]];
        return tmp;
    }

    int query(int root,int l,int r,int k)
    {
        if(l==r) return l;
        int mid=(l+r)>>1,res=val[rs[root]];
        if(k<=res) return query(rs[root],mid+1,r,k);
        else return query(ls[root],l,mid,k-res); 
    }
}

namespace TYC
{
    typedef long long ll;
    const int N=2e5+10,M=5e5+10,inf=0x3f3f3f3f;
    int n,m,q,node,cnt,a[N],w[N],fa[N],Head[N],root[N],dep[N],ffa[N][20],tmp[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct Edge
    {
        int u,v,w;
        bool operator < (const Edge &t) const
        {
            return w<t.w;
        }
    }e[M];

    int find(int x)
    {
        return x==fa[x]?x:fa[x]=find(fa[x]);
    }

    struct edge
    {
        int to,next;
    }E[N<<1];

    void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v]};
        Head[v]=cnt;
    }

    void kruskal()
    {
        node=n;
        sort(e+1,e+1+m);
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=1;i<=m;i++) 
        {
            int u=e[i].u,v=e[i].v;
            int fu=find(u),fv=find(v);
            if(fu==fv) continue;
            a[++node]=0;
            w[node]=e[i].w;
            fa[fu]=fa[fv]=fa[node]=node;
            add(node,fu),add(node,fv);
            if(node-n==n-1) return;
        }
    }

    void dfs(int u,int f)
    {
        dep[u]=dep[f]+1;
        ffa[u][0]=f;
        for(int i=1;i<=18;i++)
            ffa[u][i]=ffa[ffa[u][i-1]][i-1];
        Tree::insert(root[u],0,n,a[u]);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
            root[u]=Tree::merge(root[u],root[v],0,n);
        }
    }

    void work()
    {
        n=read(),m=read(),q=read();
        for(int i=1;i<=n;i++) 
            a[i]=tmp[i]=read();
        sort(tmp+1,tmp+1+n);
        int tot=unique(tmp+1,tmp+1+n)-tmp-1;
        for(int i=1;i<=n;i++)
            a[i]=lower_bound(tmp+1,tmp+1+tot,a[i])-tmp;
        for(int i=1;i<=m;i++) 
            e[i]=(Edge){read(),read(),read()};
        kruskal();
        dfs(node,0);
        int ans=0;
        while(q--)
        {
            int u=read(),limit=read(),k=read();
            if(~ans) u^=ans,limit^=ans,k^=ans;
            int rt=u;
            for(int i=18;i>=0;i--)
                if(dep[rt]-(1<<i)>0&&w[ffa[rt][i]]<=limit)
                    rt=ffa[rt][i];
            ans=Tree::query(root[rt],0,n,k);
            if(!ans) ans=-1;
            else ans=tmp[ans];
            printf("%d\n",ans);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
