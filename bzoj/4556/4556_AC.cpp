#include<bits/stdc++.h>
using namespace std;

namespace Tree
{
    const int N=7000000+10;
    int cnt;
    struct node
    {
        int ls,rs,mx,num;
    }tree[N];

    inline void update(int root)
    {
        node &l=tree[tree[root].ls],&r=tree[tree[root].rs];
        tree[root].mx=max(l.mx,r.mx);
        tree[root].num=l.mx>=r.mx?l.num:r.num;
    }

    void insert(int &root,int l,int r,int pos,int val)
    {
        if(!root) root=++cnt;
        if(l==r)
        {
            tree[root].mx+=val;
            if(tree[root].mx) tree[root].num=pos;
            else tree[root].num=0;
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) insert(tree[root].ls,l,mid,pos,val);
        else insert(tree[root].rs,mid+1,r,pos,val);
        update(root);
    }

    void merge(int &x,int y,int l,int r)
    {
        if(!y) return;
        if(!x) {x=y;return;}
        if(l==r)
        {
            tree[x].mx+=tree[y].mx;
            if(tree[x].mx==tree[y].mx) tree[x].num=l;
            return;
        }
        int mid=(l+r)>>1;
        merge(tree[x].ls,tree[y].ls,l,mid);
        merge(tree[x].rs,tree[y].rs,mid+1,r);
        update(x);
    }
}

namespace TYC
{
    const int N=100010;
    int n,m,cnt,tot,Head[N],root[N],fa[N][20],dep[N],ans[N],num[N];

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

    struct ques
    {
        int u,v,val;
		bool operator < (const ques &t) const
		{
			return val<t.val;
		}
    }q[N];

    void dfs(int u,int f)
    {
        fa[u][0]=f;
        dep[u]=dep[f]+1;
        for(int i=1;fa[u][i-1]&&i<=18;i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
        }
    }

    inline int LCA(int u,int v)
    {
        if(dep[u]<dep[v]) swap(u,v);
        for(int d=dep[u]-dep[v],t=0;d;t++,d>>=1)
            if(d&1) u=fa[u][t];
        if(u==v) return u;
        for(int i=18;i>=0;i--)
            if(fa[u][i]!=fa[v][i]) 
                u=fa[u][i],v=fa[v][i];
        return fa[u][0];
    }

    void dfs(int u)
    {
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u][0]) continue;
            dfs(v);
            Tree::merge(root[u],root[v],1,m);
        }
        ans[u]=Tree::tree[root[u]].num;
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(1,0);
        for(int i=1;i<=m;i++)
            q[i].u=read(),q[i].v=read(),q[i].val=read();
		sort(q+1,q+1+m);
        for(int i=1;i<=m;i++)
        {
            if(q[i].val!=num[tot])
                num[++tot]=q[i].val;
            q[i].val=tot;
            int u=q[i].u,v=q[i].v,lca=LCA(u,v);
            Tree::insert(root[u],1,m,q[i].val,1);
            Tree::insert(root[v],1,m,q[i].val,1);
            Tree::insert(root[lca],1,m,q[i].val,-1);
            if(fa[lca][0]) 
                Tree::insert(root[fa[lca][0]],1,m,q[i].val,-1);
        }
        dfs(1);
        for(int i=1;i<=n;i++)
            printf("%d\n",num[ans[i]]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
