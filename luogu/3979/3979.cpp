#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=100010;
    int n,m,cnt,dfstim,root,dfn[N],out[N],Head[N],fa[N],top[N],son[N],size[N],dep[N],val[N],w[N];

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
            size[u]+=size[v];
            if(size[v]>size[hs]) hs=v;
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        dfn[u]=++dfstim;
        top[u]=ance;
        w[dfstim]=val[u];
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
        out[u]=dfstim;
    }

    namespace Tree
    {
        struct node
        {
            int mn,tag;
        }tree[N<<2];
        #define ls root<<1
        #define rs root<<1|1

        void build(int root,int l,int r)
        {
            if(l==r) {tree[root].mn=w[l];return;}
            int mid=(l+r)>>1;
            build(ls,l,mid);
            build(rs,mid+1,r);
            tree[root].mn=min(tree[ls].mn,tree[rs].mn);
        }

        void pushdown(int root)
        {
            int tag=tree[root].tag;
            if(!tag) return;
            tree[ls].mn=tree[ls].tag=tag;
            tree[rs].mn=tree[rs].tag=tag;
            tree[root].tag=0;
        }

        void change(int root,int l,int r,int s,int e,int v)
        {
            if(s<=l&&r<=e)
                {tree[root].mn=tree[root].tag=v;return;}
            pushdown(root);
            int mid=(l+r)>>1;
            if(s<=mid) change(ls,l,mid,s,e,v);
            if(e>mid) change(rs,mid+1,r,s,e,v);
            tree[root].mn=min(tree[ls].mn,tree[rs].mn);
        }

        int query(int root,int l,int r,int s,int e)
        {
            if(s>e) return 0x3f3f3f3f;
            if(s<=l&&r<=e) return tree[root].mn;
            pushdown(root);
            int mid=(l+r)>>1;
            if(e<=mid) return query(ls,l,mid,s,e);
            else if(s>mid) return query(rs,mid+1,r,s,e);
            else return min(query(ls,l,mid,s,e),query(rs,mid+1,r,s,e)); 
        }
    }

    inline int LCA(int u,int v)
    {
        while(top[u]!=top[v])
        {
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            u=fa[top[u]];
        }
        return dep[u]<dep[v]?u:v;
    }

	inline int get_nxt(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			if(fa[top[u]]==v) return top[u];
			else u=fa[top[u]];
		}
		if(dep[u]>dep[v]) swap(u,v);
		return son[u];
	}

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        for(int i=1;i<=n;i++) val[i]=read();
        root=read();
        dfs(root);
        dfs(root,root);
        Tree::build(1,1,n);
        int opt,u,v,x,lca,ans;
        while(m--)
        {
            opt=read();
            switch(opt)
            {
                case 1: root=read();break;
                case 2: 
                    u=read(),v=read(),x=read();
                    while(top[u]!=top[v])
                    {
                        if(dep[top[u]]<dep[top[v]]) swap(u,v);
                        Tree::change(1,1,n,dfn[top[u]],dfn[u],x);
                        u=fa[top[u]];
                    }
                    if(dep[u]>dep[v]) swap(u,v);
                    Tree::change(1,1,n,dfn[u],dfn[v],x);
                    break;
                case 3:
                    u=read();
                    if(u==root) ans=Tree::tree[1].mn;
                    else 
                    {
                        lca=LCA(u,root);
                        if(lca!=u) ans=Tree::query(1,1,n,dfn[u],out[u]);
                        else
                        { 
							x=get_nxt(u,root);
                            ans=min(Tree::query(1,1,n,1,dfn[x]-1),Tree::query(1,1,n,out[x]+1,n));  
                        } 
                    }
                    printf("%d\n",ans);
                    break;
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}