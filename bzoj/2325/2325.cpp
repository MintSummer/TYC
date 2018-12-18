#include<bits/stdc++.h>
using namespace std;

namespace SegmentTree
{
    const int inf=0x3f3f3f3f;
    struct node
    {
        int l0,l1,r0,r1,d0,d1,d2,d3;
    }tree[200010];

    inline int to_max(int x,int y)
    {
        int t=max(x,y);
        return t<0?-inf:t;
    }

    inline node update(node ls,node rs)
    {
        node root;
        root.d0=to_max(ls.d0+rs.d0,ls.d1+rs.d2);
        root.d1=to_max(ls.d0+rs.d1,ls.d1+rs.d3);
        root.d2=to_max(ls.d3+rs.d2,ls.d2+rs.d0);
        root.d3=to_max(ls.d3+rs.d3,ls.d2+rs.d1);
        root.l0=to_max(ls.d0+rs.l0,ls.d1+rs.l1);
        root.l1=to_max(ls.d2+rs.l0,ls.d3+rs.l1);
        root.r0=to_max(rs.d0+ls.r0,rs.d2+ls.r1);
        root.r1=to_max(rs.d1+ls.r0,rs.d3+ls.r1);
        root.l0=to_max(ls.l0,root.l0);
        root.l1=to_max(ls.l1,root.l1);
        root.r0=to_max(rs.r0,root.r0);
        root.r1=to_max(rs.r1,root.r1);
        return root;
    }

    void insert(int root,int l,int r,int pos,char *mp)
    {
        if(l==r)
        {
            node &now=tree[root];
            now.d0=now.d1=now.d2=now.d3=-inf;
            now.l0=now.l1=now.r0=now.r1=-inf;
            if(mp[0]=='.') 
                now.d0=now.l0=now.r0=1;
            if(mp[1]=='.')
                now.d3=now.l1=now.r1=1;
            if(mp[0]=='.'&&mp[1]=='.')
            {
                now.d1=now.d2=2;
                now.l0=now.l1=now.r0=now.r1=2;
            }
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) insert(root<<1,l,mid,pos,mp);
        else insert(root<<1|1,mid+1,r,pos,mp);
        tree[root]=update(tree[root<<1],tree[root<<1|1]);
    }

    node interval(int root,int l,int r,int s,int e)
    {
        if(s<=l&&r<=e) return tree[root];
        int mid=(l+r)>>1;
        if(e<=mid) 
            return interval(root<<1,l,mid,s,e);
        else if(s>mid) 
            return interval(root<<1|1,mid+1,r,s,e);
        else 
            return update(interval(root<<1,l,mid,s,mid),interval(root<<1|1,mid+1,r,mid+1,e));
    }
}   

namespace TYC
{
    using namespace SegmentTree;
    const int N=50010;
    int n,m,cnt,dfstim,Head[N],top[N],dep[N],fa[N],size[N],son[N],dfn[N];
    char mp[N][3];

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
        dep[u]=dep[fa[u]]+1;
        size[u]=1;
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
        insert(1,1,n,dfn[u],mp[u]);
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
    }

    int LCA(int u,int v)
    {
        while(top[u]!=top[v])
        {
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            u=fa[top[u]];
        }
        return dep[u]<dep[v]?u:v;
    }

    node query(int u,int goal,int flag)
    {
        node ans;
        ans.d0=ans.d1=ans.d2=ans.d3=0;
        ans.l0=ans.l1=ans.r0=ans.r1=0;
        while(top[u]!=top[goal])
        {
            ans=update(interval(1,1,n,dfn[top[u]],dfn[u]),ans);
            u=fa[top[u]];
        }
        if(flag)
        {
            if(dfn[goal]+1<=dfn[u]) 
                ans=update(interval(1,1,n,dfn[goal]+1,dfn[u]),ans);
        }
        else ans=update(interval(1,1,n,dfn[goal],dfn[u]),ans);
        return ans;
    }

    void work()
    {
        n=read(),m=read();
        int u,v;
        for(int i=1;i<n;i++)
        {
            u=read(),v=read();
            add(u,v),add(v,u);
        }
        for(int i=1;i<=n;i++) scanf("%s",mp[i]);
        dfs(1);
        dfs(1,1);
        char opt[2];
        while(m--)
        {
            scanf("%s",opt);
            u=read();
            if(opt[0]=='C')
            {
				scanf("%s",mp[u]);
                insert(1,1,n,dfn[u],mp[u]);
            }
            else 
            {
                v=read();
                if(mp[u][0]=='#'&&mp[u][1]=='#') 
                {
                    printf("0\n");
                    continue;
                }
                int lca=LCA(u,v);
                node linku=query(u,lca,1),linkv=query(v,lca,0);
                swap(linku.d1,linku.d2);
                swap(linku.l0,linku.r0);
                swap(linku.l1,linku.r1);
                node ans=update(linku,linkv);
                printf("%d\n",max(ans.l0,ans.l1));
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}