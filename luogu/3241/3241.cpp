#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=150010,inf=0x3f3f3f3f;
    int n,m,Node,cnt,dfntim,Head[N],fa[N],son[N],size[N],dfn[N],top[N],w[N],root[N],year[N];
    ll dis[N],sumdis[N],val[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct Monster
    {
        int id,age;
        bool operator < (const Monster &t) const
        {
            return (age<t.age)||(age==t.age&&id<t.id);
        }
    }monster[N];

    struct edge
    {
        int to,next,w;
    }E[N<<1];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u)
    {
        int hs=0;
        size[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]) continue;
            fa[v]=u;
            dis[v]=dis[u]+E[i].w;
            w[v]=E[i].w;
            dfs(v);
            if(size[v]>size[hs]) hs=v;
            size[u]+=size[v]; 
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        dfn[u]=++dfntim;
        val[dfntim]=w[u];
        top[u]=ance;
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
    }

    namespace Tree
    {
        const int M=N*70;
        int cnt,ls[M],rs[M],tag[M];
        ll sum[M];

        void insert(int &root,int last,int l,int r,int s,int e)
        {
            root=++cnt;
            ls[root]=ls[last],rs[root]=rs[last];
            sum[root]=sum[last],tag[root]=tag[last];
            if(s<=l&&r<=e) {tag[root]++;return;}
            int mid=(l+r)>>1;
            sum[root]+=val[e]-val[s-1];
            if(e<=mid) insert(ls[root],ls[last],l,mid,s,e);
            else if(s>mid) insert(rs[root],rs[last],mid+1,r,s,e); 
            else insert(ls[root],ls[last],l,mid,s,mid),insert(rs[root],rs[last],mid+1,r,mid+1,e);
        }

        ll query(int root,int l,int r,int s,int e)
        {
            ll tmp=(val[e]-val[s-1])*tag[root];
            if(s<=l&&r<=e) return tmp+sum[root];
            int mid=(l+r)>>1;
            if(e<=mid) return tmp+query(ls[root],l,mid,s,e);
            else if(s>mid) return tmp+query(rs[root],mid+1,r,s,e);
            else return tmp+query(ls[root],l,mid,s,mid)+query(rs[root],mid+1,r,mid+1,e);
        }
    }

    void work()
    {
        n=read(),m=read(),Node=read();
        for(int i=1;i<=n;i++)
            monster[i]=(Monster){i,read()};
        sort(monster+1,monster+1+n);
        for(int i=1;i<n;i++)
       	{ 
            int u=read(),v=read(),ww=read();
            add(u,v,ww),add(v,u,ww);
        }
        dfs(1);
        dfs(1,1);
        for(int i=1;i<=n;i++)
        {
            val[i]+=val[i-1];
            sumdis[i]=sumdis[i-1]+dis[monster[i].id];
        }
        for(int i=1;i<=n;i++)
        {
            root[i]=root[i-1];
            for(int x=monster[i].id;x;x=fa[top[x]])
                Tree::insert(root[i],root[i],1,n,dfn[top[x]],dfn[x]);
        }
		for(int i=1;i<=n;i++) year[i]=monster[i].age;
		year[0]=-inf,year[n+1]=inf;
        ll ans=0;
        while(m--)
        {
            int pos=read(),l=(read()+ans)%Node,r=(read()+ans)%Node;
            if(l>r) swap(l,r);
            l=lower_bound(year+1,year+1+n,l)-year;
			r=upper_bound(year+1,year+1+n,r)-year-1;
            ans=(r-l+1)*dis[pos]+sumdis[r]-sumdis[l-1];
            for(int x=pos;x;x=fa[top[x]])
                ans-=(Tree::query(root[r],1,n,dfn[top[x]],dfn[x])-Tree::query(root[l-1],1,n,dfn[top[x]],dfn[x]))<<1;
            printf("%lld\n",ans);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
