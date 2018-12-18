#include<bits/stdc++.h>
using namespace std;

namespace Tree
{
    const int N=5e6+10;
    int cnt;
    struct node
    {
        int lson,rson,sum,mx;
    }tree[N];
    #define ls tree[root].lson
    #define rs tree[root].rson

    inline void update(int root)
    {
        tree[root].sum=tree[ls].sum+tree[rs].sum;
        tree[root].mx=max(tree[ls].mx,tree[rs].mx);
    }

    void insert(int &root,int l,int r,int pos,int val)
    {
        if(!root) root=++cnt;
        if(l==r) {tree[root].sum+=val,tree[root].mx+=val;return;}
        int mid=(l+r)>>1;
        if(pos<=mid) insert(ls,l,mid,pos,val);
        else insert(rs,mid+1,r,pos,val);
        update(root);
    }

    int query_sum(int root,int l,int r,int s,int e)
    {
        if(s<=l&&r<=e) return tree[root].sum;
        int mid=(l+r)>>1,ans=0;
        if(s<=mid) ans+=query_sum(ls,l,mid,s,e);
        if(e>mid) ans+=query_sum(rs,mid+1,r,s,e);
        return ans;
    }

    int query_max(int root,int l,int r,int s,int e)
    {
        if(s<=l&&r<=e) return tree[root].mx;
        int mid=(l+r)>>1,ans=0;
        if(s<=mid) ans=max(ans,query_max(ls,l,mid,s,e));
        if(e>mid) ans=max(ans,query_max(rs,mid+1,r,s,e));
        return ans;
    }
}

namespace TYC
{
    const int N=1e5+10;
    int n,m,cnt,dfstim,val[N],col[N],Head[N],root[N],fa[N],dep[N],size[N],son[N],dfn[N],top[N];

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

    void dfs(int u)
    {
        int hs=0;
        size[u]=1;
        dep[u]=dep[fa[u]]+1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]) continue;
            fa[v]=u;
            dfs(v);
            if(size[v]>size[hs]) hs=v;
            size[u]+=size[v];
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        dfn[u]=++dfstim;
        top[u]=ance;
        Tree::insert(root[col[u]],1,n,dfn[u],val[u]);
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++)
            val[i]=read(),col[i]=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(1);
        dfs(1,1);
        char ch;
        while(m--)
        {
            do ch=getchar(); while(!isalpha(ch));
            if(ch=='C')
            {
                ch=getchar();
                if(ch=='C')
                {
                    int x=read();
                    Tree::insert(root[col[x]],1,n,dfn[x],-val[x]);
                    col[x]=read();
                    Tree::insert(root[col[x]],1,n,dfn[x],val[x]);
                }
                else
                {
                    int x=read(),v=read();
                    Tree::insert(root[col[x]],1,n,dfn[x],v-val[x]);
                    val[x]=v;
                }
            }
            else
            {
                ch=getchar();
                int ans=0,u=read(),v=read(),c=col[u];
                if(ch=='S')
                {
                    while(top[u]!=top[v])
                    {
                        if(dep[top[u]]<dep[top[v]]) swap(u,v);
                        ans+=Tree::query_sum(root[c],1,n,dfn[top[u]],dfn[u]);
                        u=fa[top[u]];
                    }
                    if(dep[u]>dep[v]) swap(u,v);
                    ans+=Tree::query_sum(root[c],1,n,dfn[u],dfn[v]);
                }
                else
                {
                    while(top[u]!=top[v])
                    {
                        if(dep[top[u]]<dep[top[v]]) swap(u,v);
                        ans=max(ans,Tree::query_max(root[c],1,n,dfn[top[u]],dfn[u]));
                        u=fa[top[u]];
                    }
                    if(dep[u]>dep[v]) swap(u,v);
                    ans=max(ans,Tree::query_max(root[c],1,n,dfn[u],dfn[v]));
                }
                printf("%d\n",ans);
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}