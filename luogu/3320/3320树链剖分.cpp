#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10;
    int n,m,cnt,dfs_clock,Head[N],size[N],son[N],top[N],dep[N],fa[N],dfn[N],mark[N];
    ll a[N],w[N];

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

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u)
    {
        int hs=0;
        dep[u]=dep[fa[u]]+1;
        size[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]) continue;
            a[v]=E[i].w;
            fa[v]=u;
            dfs(v);
            if(size[v]>size[hs]) hs=v;
            size[u]+=size[v];
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        top[u]=ance;
        dfn[u]=++dfs_clock;
        w[dfs_clock]=a[u];
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
        #define ls root<<1
        #define rs root<<1|1
        struct node
        {
            int mx,mn,tag;
            ll mxsum,mnsum;
        }tree[N<<2];

        inline void update(int root)
        {
            tree[root].mn=min(tree[ls].mn,tree[rs].mn);
            tree[root].mx=max(tree[ls].mx,tree[rs].mx);
            tree[root].mnsum=tree[ls].mnsum*(tree[ls].mn==tree[root].mn)+
                             tree[rs].mnsum*(tree[rs].mn==tree[root].mn);
            tree[root].mxsum=tree[ls].mxsum*(tree[ls].mx==tree[root].mx)+
                             tree[rs].mxsum*(tree[rs].mx==tree[root].mx);
        }

        inline void pushdown(int root)
        {
            int tag=tree[root].tag;
            if(!tag) return;
            tree[ls].mn+=tag,tree[ls].mx+=tag,tree[ls].tag+=tag;
            tree[rs].mn+=tag,tree[rs].mx+=tag,tree[rs].tag+=tag;
            tree[root].tag=0;
        }

        void build(int root,int l,int r)
        {
			if(l==r)
			{
				tree[root].mxsum=tree[root].mnsum=w[l];
				return;
			}
            int mid=(l+r)>>1;
            build(ls,l,mid),build(rs,mid+1,r);
			update(root);
        }

        void add(int root,int l,int r,int s,int e,int val)
        {
            if(s<=l&&r<=e)
            {
                tree[root].mn+=val;
                tree[root].mx+=val;
                tree[root].tag+=val;
                return;
            }
            pushdown(root);
            int mid=(l+r)>>1;
            if(s<=mid) add(ls,l,mid,s,e,val);
            if(e>mid) add(rs,mid+1,r,s,e,val);
			update(root);
        }
    }

    void work()
    {
        n=read(),m=read();
        ll total=0;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            total+=w;
            add(u,v,w),add(v,u,w);
        }
        dfs(1);
        dfs(1,1);
        Tree::build(1,1,n);
        int tot=0;
        while(m--)
        {
            int now=read();
            int val=(mark[now]?-1:1),x=now;
            tot+=val;
            while(x) 
            {
                Tree::add(1,1,n,dfn[top[x]],dfn[x],val);
                x=fa[top[x]];
            }
            ll ans=0;
            if(Tree::tree[1].mn==0) ans+=Tree::tree[1].mnsum;
            if(Tree::tree[1].mx==tot) ans+=Tree::tree[1].mxsum;
            printf("%lld\n",(total-ans)<<1);
            mark[now]=(mark[now]?0:1);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
